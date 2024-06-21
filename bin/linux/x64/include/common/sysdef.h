/*
* Copyright (c) 2017-2022 the FrameX authors
* All rights reserved.
*
* The project sponsor and lead author is Xu Rendong.
* E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: xrd_ustc
* See the contributors file for names of other contributors.
*
* Commercial use of this code in source and binary forms is
* governed by a LGPL v3 license. You may get a copy from the
* root directory. Or else you should get a specific written
* permission from the project author.
*
* Individual and educational use of this code in source and
* binary forms is governed by a 3-clause BSD license. You may
* get a copy from the root directory. Certainly welcome you
* to contribute code of all sorts.
*
* Be sure to retain the above copyright notice and conditions.
*/

#ifndef FRAMEX_COMMON_SYSDEF_H
#define FRAMEX_COMMON_SYSDEF_H

namespace framex {

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    //#include <SDKDDKVer.h>
    //#define NOMINMAX // 避免 common/date.h 的 min()、max() 冲突
    #define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的信息
    #define __OS_WINDOWS__
    #if defined(_WIN64)
        #define __OS_WINDOWS_64__
    #else
        #define __OS_WINDOWS_32__
    #endif
#elif defined(__linux) || defined(__linux__) || defined(linux)
    #define __OS_LINUX__ // 代码中直接用 __GNUC__ 或 __GNUG__ 判断也可以
#elif defined(__APPLE__)
    #define __OS_APPLE__
    #include "TargetConditionals.h"
    #if defined(TARGET_IPHONE_SIMULATOR)
        #define __OS_APPLE_IOS_SIMULATOR__
    #elif defined(TARGET_OS_IPHONE)
        #define __OS_APPLE_IOS_DEVICE__
    #elif defined(TARGET_OS_MAC)
        #define __OS_APPLE_OTHER_MAC_OS__
    #else
        #error "Unknown Apple Platform"
    #endif
#elif defined(__ANDROID__)
    #define __OS_ANDROID__
#elif defined(__CYGWIN__)
    #define __OS_CYGWIN__
#elif defined(__MINGW32__)
    #define __OS_MINGW__
#elif defined(__FreeBSD__) || defined(__FreeBSD)
    #define __OS_FREE_BSD__
#elif defined(__NetBSD__) || defined(__NetBSD)
    #define __OS_NET_BSD__
#elif defined(__OpenBSD__) || defined(__OPENBSD)
    #define __OS_OPEN_BSD__
#else
    #error "Unknown Platform"
#endif

} // namespace framex

#endif // FRAMEX_COMMON_SYSDEF_H
