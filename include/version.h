/***************************************************
* version.h: Project version / revision            *
* Copyright (C) 2021 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef LYS3D_VERSION_H_
#define LYS3D_VERSION_H_

#include <config.h>

#ifdef __cplusplus
namespace lys3d {
extern "C" {
#endif //__cplusplus

extern LYS_API const char* kProjectName;
extern LYS_API const char* kProjectVersion;
extern LYS_API const char* kProjectRevision;
extern LYS_API const char* kProjectCompiler;
extern LYS_API const char* kProjectCompilerVersion;

#ifdef __cplusplus
}
}
#endif // __cplusplus
#endif // LYS3D_VERSION_H_

