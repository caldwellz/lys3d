/***************************************************
* WindowGLES2.h: GLES2 window management class     *
* Copyright (C) 2021 by Zach Caldwell              *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef LYS3D_WINDOW_H_
#define LYS3D_WINDOW_H_

#include "IWindow.h"

namespace lys3d {
/** Encapsulates an OpenGL-accelerated graphical window. */
class LYS_API WindowGLES2 : public IWindow {
  public:
    /** Basic constructor.
     * Defaults to full-screen VSync'd mode at the native screen resolution.
     * If needed, change the relevant window settings before calling open().
     */
    WindowGLES2();

    /** Basic destructor.
     * Closes the window if it is still open.
     */
    ~WindowGLES2();

    // Implementations of IWindow virtual functions
    bool isOpen() const;
    bool open();
    void close();
    bool activate();
    bool update();
    String title() const;
    void title(const String new_title);
    Point2Di32 position() const;
    void position(const Point2Di32 &new_pos);
    void centerPosition();
    Dimension2Di32 size() const;
    Dimension2Di32 sizeInPixels() const;
    bool size(const Dimension2Di32 &new_size);
    bool isFullscreen() const;
    bool useFullscreen(bool fullscreen = true, bool use_native_resolution = true);
    bool isVSyncEnabled() const;
    bool useVSync(bool enable = true);

  private:
    struct Impl;
    Impl *pimpl_;
};
}
#endif // LYS3D_WINDOW_H_
