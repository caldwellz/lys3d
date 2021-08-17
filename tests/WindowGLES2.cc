/***************************************************
* Test - GLES2 window management class             *
* Copyright (C) 2021 by Zach Caldwell              *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#include "WindowGLES2.h"

#include <assert.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include "types.h"

int main(void) {
    // Initialization and basic sanity checks
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    lys3d::WindowGLES2 window;
    window.useFullscreen(false, false);
    printf("- Window: Opening\n");
    assert(window.open() && window.isOpen());
    assert(window.update());
    assert(!window.isFullscreen());

    // VSync
    printf("- Window: Turning VSync on\n");
    assert(window.useVSync(true) && window.isVSyncEnabled());
    assert(window.update());
    printf("- Window: Turning VSync off\n");
    assert(window.useVSync(false) && !window.isVSyncEnabled());
    assert(window.update());

    // Title
    lys3d::String new_title("Lys3D Window Test - New Title");
    printf("- Window: Changing title\n");
    window.title(new_title);
    assert(window.title() == new_title);

    // Position
    printf("- Window: Setting position to (1, 10)\n");
    lys3d::Point2Di32 pos(1, 10);
    window.position(pos);
    pos = window.position();
    // The window manager may adjust the position due to window decorations
    printf("Position after repositioning: (%i, %i)\n", pos.x(), pos.y());
    assert(pos.x() >= 1 && pos.y() >= 10);
    printf("- Window: Centering position\n");
    window.centerPosition();
    pos = window.position();
    printf("Position after centering: (%i, %i)\n", pos.x(), pos.y());
    assert(pos.x() && pos.y());

    // Windowed-mode size
    printf("- Window: Changing windowed-mode size to 800x600\n");
    lys3d::Dimension2Di size = window.size();
    printf("Size before change: %ix%i\n", size.width(), size.height());
    assert(size.width() && size.height()); // Dimensions should never be zero
    size.width(800);
    size.height(600);
    assert(window.size(size));
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() == 800 && size.height() == 600);
    size = window.sizeInPixels();
    // HighDPI devices will have more pixels in the same screen coordinates
    printf("PixelSize after change: %ix%i\n", size.width(), size.height());
    assert(size.width() >= 800 && size.height() >= 600);

    // Changing to fullscreen - existing resolution
    printf("- Window: Changing to fullscreen, reusing existing resolution\n");
    assert(window.useFullscreen(true, false) && window.isFullscreen());
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() == 800 && size.height() == 600);

    // Changing resolution while in an existing custom fullscreen video mode
    printf("- Window: Changing fullscreen resolution to 640x480\n");
    size.width(640);
    size.height(480);
    assert(window.size(size));
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() == 640 && size.height() == 480);

    // Changing back to windowed mode
    printf("- Window: Changing back to windowed mode\n");
    assert(window.useFullscreen(false, false));
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() == 640 && size.height() == 480);

    // Going fullscreen, native screen resolution
    printf("- Window: Changing to fullscreen, native screen resolution\n");
    assert(window.useFullscreen(true, true));
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() && size.height());

    // Changing resolution while in native fullscreen
    printf("- Window: Changing fullscreen resolution to 640x480\n");
    size.width(640);
    size.height(480);
    assert(window.size(size));
    assert(window.update());
    size = window.size();
    printf("Size after change: %ix%i\n", size.width(), size.height());
    assert(size.width() == 640 && size.height() == 480);

    // Clean up
    window.close();
    SDL_Quit();

    return 0;
}
