/***************************************************
* version.h: Project version / revision            *
* Copyright (C) 2021 Zach Caldwell                 *
****************************************************
* This Source Code Form is subject to the terms of *
* the Mozilla Public License, v. 2.0. If a copy of *
* the MPL was not distributed with this file, You  *
* can obtain one at http://mozilla.org/MPL/2.0/.   *
***************************************************/

#ifndef _VERSION_H_
#define _VERSION_H_

#include <config.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

extern LYS_API const char* PROJECT_NAME;
extern LYS_API const char* PROJECT_VERSION;
extern LYS_API const char* PROJECT_REVISION;
extern LYS_API const char* PROJECT_COMPILER;
extern LYS_API const char* PROJECT_COMPILER_VERSION;

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //_VERSION_H_

