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

#ifndef FRAMEX_PLUGIN_PLUGIN_H
#define FRAMEX_PLUGIN_PLUGIN_H

#include <string>
#include <stdint.h> // int32_t, int64_t

#include <common/compile.h>

namespace framex {

	enum FRAMEX_PLUGIN_EXPIMP plugin_status {
		init = 0, load = 1, exec = 2, wait = 3, stop = 4, fail = 5, // 导入信息，已经加载，正常运行，等待运行，停止运行，发生异常
	};

	class FRAMEX_PLUGIN_EXPIMP Plugin_R {
	public:
		Plugin_R();
		virtual ~Plugin_R();

	public:
		virtual void ReturnData( int32_t flag, int32_t task, int32_t unit, int32_t func, int32_t form, int32_t type, uint32_t size, const char* data ) = 0;
		virtual void ReturnTask( int32_t flag, int32_t task, int32_t unit, int32_t func, int32_t form, int32_t code, std::string& info, std::string& data ) = 0;
	};

	class FRAMEX_PLUGIN_EXPIMP Plugin_X {
	private:
		Plugin_X();

	public:
		Plugin_X( std::string plugin_name );
		virtual ~Plugin_X();

	public:
		virtual void SetCallback( Plugin_R* plugin_r ) = 0;

	public:
		virtual bool Initialize() = 0;
		virtual bool InitializeExt() = 0;
		virtual bool StartPlugin() = 0;
		virtual bool SuspendPlugin() = 0;
		virtual plugin_status GetPluginStatus() = 0;
		virtual bool ContinuePlugin() = 0;
		virtual bool StopPlugin() = 0;
		virtual bool UninitializeExt() = 0;
		virtual bool Uninitialize() = 0;

	public:
		virtual std::string DirectCall( int32_t func, int32_t form, std::string& args ) = 0;
		virtual int32_t CancelTask( int32_t flag, int32_t task, int32_t unit, int32_t func ) = 0;
		virtual int32_t AssignTask( int32_t flag, int32_t task, int32_t unit, int32_t func, int32_t form, std::string& common, std::string& custom ) = 0;
	};

	class Plugin_P;

	class FRAMEX_PLUGIN_EXPIMP Plugin_S {
	public:
		Plugin_S();
		~Plugin_S();

	public:
		static Plugin_S* GetInstance();

	public:
		void StartPlugin();
		bool IsPluginStarted();

	public:
		bool LoadAll( std::string folder );
		bool UnloadAll();

		Plugin_X* GetPluginX( const std::string& plugin_name ) const;
		void SetPluginX( const std::string& plugin_name, Plugin_X* plugin_x );

		std::string GetPluginLocationByName( const std::string& plugin_name ) const;
		std::string GetPluginCfgFilePathByName( const std::string& plugin_name ) const;
		std::string GetPluginInfoFilePathByName( const std::string& plugin_name ) const;

	public:
		void ReloadPluginInfos( std::string folder ); // 目前未做互斥处理，不建议程序启动后运行过程中再被调用
		size_t GetPluginInfosNumber();
		std::string GetPluginName( size_t index ) const;
		std::string GetPluginVersion( size_t index ) const;
		std::string GetPluginCompatVersion( size_t index ) const;
		std::string GetPluginVendor( size_t index ) const;
		std::string GetPluginCopyright( size_t index ) const;
		std::string GetPluginLicense( size_t index ) const;
		std::string GetPluginCategory( size_t index ) const;
		std::string GetPluginDescription( size_t index ) const;
		std::string GetPluginUrl( size_t index ) const;
		bool CanPluginLoadByName( const std::string& plugin_name );
		bool CanPluginUnloadByName( const std::string& plugin_name );
		bool LoadPluginByName( const std::string& plugin_name, const std::string& plugin_version = "" ); // 未事先 加载 关联插件将失败
		bool UnloadPluginByName( const std::string& plugin_name ); // 未事先 卸载 关联插件将失败

	private:
		Plugin_P* m_plugin_p;
		static Plugin_S* m_instance;
	};

} // namespace framex

#endif // FRAMEX_PLUGIN_PLUGIN_H
