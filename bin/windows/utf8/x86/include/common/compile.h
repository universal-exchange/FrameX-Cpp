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

#ifndef FRAMEX_COMMON_COMPILE_H
#define FRAMEX_COMMON_COMPILE_H

#include <common/sysdef.h>

//---------- 基础组件 ----------//

#define FRAMEX_TIMERS_EXP
//#define FRAMEX_TIMERS_IMP

#define FRAMEX_SYSLOG_EXP
//#define FRAMEX_SYSLOG_IMP

#define FRAMEX_SYSCFG_EXP
//#define FRAMEX_SYSCFG_IMP

#define FRAMEX_SYSDBI_M_EXP
//#define FRAMEX_SYSDBI_M_IMP

#define FRAMEX_SYSDBI_S_EXP
//#define FRAMEX_SYSDBI_S_IMP

#define FRAMEX_NETLIB_EXP
//#define FRAMEX_NETLIB_IMP

#define FRAMEX_SYSRTM_EXP
//#define FRAMEX_SYSRTM_IMP

#define FRAMEX_PLUGIN_EXP
//#define FRAMEX_PLUGIN_IMP

#define FRAMEX_PLUGIN_X_EXP
//#define FRAMEX_PLUGIN_X_IMP

//---------- 设置结束 ----------//

#ifdef __OS_WINDOWS__

#ifdef FRAMEX_TIMERS_EXP
    #define FRAMEX_TIMERS_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_TIMERS_IMP
    #define FRAMEX_TIMERS_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_SYSLOG_EXP
    #define FRAMEX_SYSLOG_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_SYSLOG_IMP
    #define FRAMEX_SYSLOG_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_SYSCFG_EXP
    #define FRAMEX_SYSCFG_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_SYSCFG_IMP
    #define FRAMEX_SYSCFG_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_SYSDBI_M_EXP
    #define FRAMEX_SYSDBI_M_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_SYSDBI_M_IMP
    #define FRAMEX_SYSDBI_M_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_SYSDBI_S_EXP
    #define FRAMEX_SYSDBI_S_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_SYSDBI_S_IMP
    #define FRAMEX_SYSDBI_S_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_NETLIB_EXP
    #define FRAMEX_NETLIB_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_NETLIB_IMP
    #define FRAMEX_NETLIB_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_SYSRTM_EXP
    #define FRAMEX_SYSRTM_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_SYSRTM_IMP
    #define FRAMEX_SYSRTM_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_PLUGIN_EXP
    #define FRAMEX_PLUGIN_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_PLUGIN_IMP
    #define FRAMEX_PLUGIN_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef FRAMEX_PLUGIN_X_EXP
    #define FRAMEX_PLUGIN_X_EXPIMP __declspec(dllexport)
#endif

#ifdef FRAMEX_PLUGIN_X_IMP
    #define FRAMEX_PLUGIN_X_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#endif

#ifdef __OS_LINUX__

#ifdef FRAMEX_TIMERS_EXP
    #define FRAMEX_TIMERS_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_SYSLOG_EXP
    #define FRAMEX_SYSLOG_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_SYSCFG_EXP
    #define FRAMEX_SYSCFG_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_SYSDBI_M_EXP
    #define FRAMEX_SYSDBI_M_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_SYSDBI_S_EXP
    #define FRAMEX_SYSDBI_S_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_NETLIB_EXP
    #define FRAMEX_NETLIB_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_SYSRTM_EXP
    #define FRAMEX_SYSRTM_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_PLUGIN_EXP
    #define FRAMEX_PLUGIN_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef FRAMEX_PLUGIN_X_EXP
    #define FRAMEX_PLUGIN_X_EXPIMP __attribute__((visibility("default")))
#endif

#endif

#endif // FRAMEX_COMMON_COMPILE_H
