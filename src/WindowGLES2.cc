/***************************************************
* WindowGLES2.cc: GLES2 window management class    *
* Copyright (C) 2021 by Zach Caldwell              *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "WindowGLES2.h"

#include <SDL2/SDL_video.h>

#include "config.h"
#include "types.h"

namespace lys3d {
struct WindowGLES2::Impl {
    /** Defaults to full-screen VSynced mode at the native screen resolution. */
    Impl() {
        window = nullptr;
        context = nullptr;
        title = "Lys3D Window";
        position = Point2Di32(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        size = Dimension2Di32(1, 1);
        fullscreenMode = SDL_WINDOW_FULLSCREEN_DESKTOP;
        wantVSync = true;
    }

    SDL_Window* window;
    SDL_GLContext context;
    String title;
    Point2Di32 position;
    Dimension2Di32 size;
    uint32_t fullscreenMode;
    bool wantVSync;
};


LYS_API WindowGLES2::WindowGLES2() {
    // Initialize with default settings
    pimpl_ = new Impl();
}


LYS_API WindowGLES2::~WindowGLES2() {
    this->close();
    delete this->pimpl_;
}


LYS_API bool WindowGLES2::isOpen() const {
    return (pimpl_->window != nullptr);
}


LYS_API bool WindowGLES2::open() {
    // Status check
    if (isOpen())
        return true;

    // Set common GL attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 0);

    // Attempt to use an ES 2.0 profile first
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    // Create and check the window and OpenGL context
    uint32_t flags = pimpl_->fullscreenMode | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                   | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    pimpl_->window = SDL_CreateWindow(pimpl_->title.c_str(), pimpl_->position.x(),
                                      pimpl_->position.y(), pimpl_->size.width(),
                                      pimpl_->size.height(), flags);
    if (pimpl_->window != nullptr) {
        pimpl_->context = SDL_GL_CreateContext(pimpl_->window);
        if (pimpl_->context == nullptr) {
            SDL_DestroyWindow(pimpl_->window);
            pimpl_->window = nullptr;
        }
    }

    if (!pimpl_->window || !pimpl_->context) {
        // Try again with a regular OpenGL 2.0 core profile
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        pimpl_->window = SDL_CreateWindow(pimpl_->title.c_str(), pimpl_->position.x(),
                                          pimpl_->position.y(), pimpl_->size.width(),
                                          pimpl_->size.height(), flags);
        if (pimpl_->window == nullptr)
            return false;

        pimpl_->context = SDL_GL_CreateContext(pimpl_->window);
        if (pimpl_->context == nullptr) {
            SDL_DestroyWindow(pimpl_->window);
            pimpl_->window = nullptr;
            return false;
        }
    }

    // Some platforms may not support enabling (or disabling) VSync, so ignore any errors.
    // The host app can call enableVSync() again itself if it wants more details.
    if (!useVSync(pimpl_->wantVSync))
        SDL_ClearError();

    return true;
}


LYS_API void WindowGLES2::close() {
    if (pimpl_->context) {
        SDL_GL_DeleteContext(pimpl_->context);
        pimpl_->context = nullptr;
    }

    if (pimpl_->window) {
        SDL_DestroyWindow(pimpl_->window);
        pimpl_->window = nullptr;
    }
}


LYS_API bool WindowGLES2::update() {
    if (pimpl_->context == nullptr)
        return false;

    // TODO: Handle SDL window events

    SDL_GL_SwapWindow(pimpl_->window);

    return true;
}


LYS_API String WindowGLES2::title() const {
    if (pimpl_->window != nullptr)
        pimpl_->title = SDL_GetWindowTitle(pimpl_->window);

    return pimpl_->title;
}


LYS_API void WindowGLES2::title(const String new_title) {
    pimpl_->title = new_title;
    if (pimpl_->window)
        SDL_SetWindowTitle(pimpl_->window, new_title.c_str());
}


LYS_API Point2Di32 WindowGLES2::position() const {
    if (pimpl_->window != nullptr) {
        int x, y;
        SDL_GetWindowPosition(pimpl_->window, &x, &y);
        pimpl_->position.x(x);
        pimpl_->position.y(y);
    }
    return pimpl_->position;
}


LYS_API void WindowGLES2::position(const Point2Di32 &new_pos) {
    pimpl_->position = new_pos;
    if (pimpl_->window != nullptr)
        SDL_SetWindowPosition(pimpl_->window, new_pos.x(), new_pos.y());
}


LYS_API void WindowGLES2::centerPosition() {
    pimpl_->position.x(SDL_WINDOWPOS_CENTERED);
    pimpl_->position.y(SDL_WINDOWPOS_CENTERED);
    if (pimpl_->window != nullptr)
        SDL_SetWindowPosition(pimpl_->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}


LYS_API Dimension2Di32 WindowGLES2::size() const {
    if (pimpl_->window != nullptr) {
        int w, h;
        SDL_GetWindowSize(pimpl_->window, &w, &h);
        pimpl_->size.width(w);
        pimpl_->size.height(h);
    }
    return pimpl_->size;
}


LYS_API Dimension2Di32 WindowGLES2::sizeInPixels() const {
    if (pimpl_->context != nullptr) {
        int w, h;
        SDL_GL_GetDrawableSize(pimpl_->window, &w, &h);
        return Dimension2Di32(w, h);
    }
    return size();
}


LYS_API bool WindowGLES2::size(const Dimension2Di32 &new_size) {
    if (new_size.width() > 0)
        pimpl_->size.width(new_size.width());

    if (new_size.height() > 0)
        pimpl_->size.height(new_size.height());

    if (pimpl_->window != nullptr) {
        SDL_SetWindowSize(pimpl_->window, pimpl_->size.width(), pimpl_->size.height());
        if (pimpl_->fullscreenMode)
            return useFullscreen(true, false);
    }

    return true;
}


LYS_API bool WindowGLES2::isFullscreen() const {
    return (pimpl_->fullscreenMode != 0);
}


LYS_API bool WindowGLES2::useFullscreen(bool fullscreen, bool use_native_resolution) {
    if (fullscreen) {
        if (use_native_resolution)
            pimpl_->fullscreenMode = SDL_WINDOW_FULLSCREEN_DESKTOP;
        else
            pimpl_->fullscreenMode = SDL_WINDOW_FULLSCREEN;
    } else {
        pimpl_->fullscreenMode = 0;
    }

    if (pimpl_->window) {
        if (SDL_SetWindowFullscreen(pimpl_->window, pimpl_->fullscreenMode) != 0)
            return false;
        if (pimpl_->fullscreenMode) {
            // Handle display mode (size) changes, since we might be called by size().
            if (SDL_SetWindowDisplayMode(pimpl_->window, nullptr) != 0)
                return false;
        }
    }

    return true;
}


LYS_API bool WindowGLES2::isVSyncEnabled() const {
    if (pimpl_->context == nullptr)
        return pimpl_->wantVSync;
    return (SDL_GL_GetSwapInterval() != 0);
}


LYS_API bool WindowGLES2::useVSync(bool enable) {
    pimpl_->wantVSync = enable;

    if (pimpl_->context != nullptr) {
        if (enable) {
            if(SDL_GL_SetSwapInterval(-1) != 0) {
                if(SDL_GL_SetSwapInterval(1) != 0)
                    return false;
            }
        } else {
            if(SDL_GL_SetSwapInterval(0) != 0)
                return false;
        }
    }

    return true;
}
}
