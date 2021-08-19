/***************************************************
* IWindow.h: Graphical window virtual interface    *
* Copyright (C) 2021 by Zach Caldwell              *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef LYS3D_IWINDOW_H_
#define LYS3D_IWINDOW_H_

#include "types.h"
#include "Dimension2D.h"
#include "Point2D.h"

namespace lys3d {

/** Encapsulates the idea of a graphical window. */
class IWindow {
  public:
    /** Default constructor */
    IWindow() = default;

    /* TODO: Someday it may make sense to allow copying/moving Window \
     * objects, but for now, delete the functions to prevent it.
     */
    IWindow(IWindow& other) = delete;
    IWindow(const IWindow& other) = delete;
    IWindow& operator=(IWindow& other) = delete;
    IWindow& operator=(const IWindow& other) = delete;

    /** Virtual destructor. */
    virtual ~IWindow() = default;

    /** Check whether the window is currently open.
     * \returns True if the window is currently open (and hardware-accelerated), \
     * false otherwise.
     */
    virtual bool isOpen() const = 0;

    /** Open/create the window.
     * \returns True if the window was successfully opened (or was already open) \
     * with hardware acceleration, false otherwise.
     */
    virtual bool open() = 0;

    /** Close/destroy the window, but keep the settings. */
    virtual void close() = 0;

    /** Activate the window.
     * Brings it into focus and makes it the "current" window for any \
     * subsequent rendering.
     * \returns True if the window was activated successfully, false otherwise.
     */
    virtual bool activate() = 0;

    /** Update the window.
     * Swaps buffers, processes window events, etc.
     * \returns True if the update succeeded and the window was not closed \
     * (either by code or by the user); false otherwise.
     */
    virtual bool update() = 0;

    /** Get the current title of the window.
     * Can be called at any time (before or after open() or close()).
     * \returns The current (or previously-used, if now closed) window title.
     */
    virtual String title() const = 0;

    /** Set the title of the window.
     * Can be called at any time (before or after open() or close()).
     * \param title The new window title.
     */
    virtual void title(const String new_title) = 0;

    /** Get the window's current position.
     * \returns A Point2D containing the window's current position, in screen \
     * coordinates (i.e. pixels, except on HighDPI devices).
     */
    virtual Point2Di32 position() const = 0;

    /** Set the window's position.
     * Can be called at any time (before or after open() or close()).
     * Uses at least an i32 so one can pass SDL_WINDOWPOS_* flags.
     * \param new_pos Window position relative to the top-left of the display, \
     * in screen coordinates (i.e. pixels, except on HighDPI devices).
     */
    virtual void position(const Point2Di32 &new_pos) = 0;

    /** Set the window's position to be centered on the display.
     * Can be called any time (before or after open() or close()).
     */
    virtual void centerPosition() = 0;

    /** Get the window's size.
     * Uses an i32 for consistency, even though a u16 should be quite sufficient.
     * Can be called any time (before or after open() or close()), but may not be \
     * accurate before the window is opened if planning to use the native desktop \
     * resolution.
     * \returns A Dimension2D containing the window's current size, in screen \
     * coordinates (i.e. pixels, except on HighDPI devices).
     */
    virtual Dimension2Di32 size() const = 0;

    /** Get the window's size, in actual pixels.
     * Can be called any time (before or after open() or close()), but may not be \
     * accurate before the window is opened on HighDPI devices and/or if planning \
     * to use the native desktop resolution.
     * \returns A Dimension2D containing the window's current size, in pixels.
     */
    virtual Dimension2Di32 sizeInPixels() const = 0;

    /** Set the window's size.
     * Will change the video mode if the window is currently fullscreen.
     * Can be called any time (before or after open() or close()).
     * \param new_size A window size, in screen coordinates (i.e. pixels, except \
     * on HighDPI devices). A value of 0 for the width or height will be ignored.
     * \returns True on success, false on failure.
     */
    virtual bool size(const Dimension2Di32 &new_size) = 0;

    /** Get the window's fullscreen state.
     * Can be called any time (before or after open() or close()).
     * \returns True if the window is configured to be fullscreen, false otherwise.
     */
    virtual bool isFullscreen() const = 0;

    /** Attempt to enable or disable fullscreen mode.
     * Can be called any time (before or after open() or close()).
     * \param fullscreen True to make the window fullscreen, false to make it \
     * windowed.
     * \param use_native_resolution True to use the screen's native resolution, \
     * false to use the configured window width and height. The preconfigured \
     * resolution may not be respected if it is not a supported video mode.
     * \returns True on success, false on failure.
     */
    virtual bool useFullscreen(bool fullscreen, bool use_native_resolution) = 0;

    /** Get the window's VSync state.
     * \returns True if VSync is currently enabled, false otherwise.
     */
    virtual bool isVSyncEnabled() const = 0;

    /** Attempt to enable or disable VSync.
     * \param enabled True to enable VSync, false to disable.
     * \returns True if the VSync change was successful, false otherwise.
     */
    virtual bool useVSync(bool enable) = 0;
};
}
#endif //LYS3D_IWINDOW_H_
