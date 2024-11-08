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

#ifndef FRAMEX_SYSDBI_M_SYSDBI_M_H
#define FRAMEX_SYSDBI_M_SYSDBI_M_H

#include <string>
#include <stdint.h>

#include <mariadb/mysql.h>

#include <common/compile.h>

namespace framex {

	class SysDBI_M_P;

	class FRAMEX_SYSDBI_M_EXPIMP SysDBI_M {
	public:
		SysDBI_M();
		~SysDBI_M();

	public:
		static SysDBI_M* GetInstance();

	public:
		int32_t AddConnect( size_t connect_number, std::string host_name, int32_t host_port, std::string user_name, std::string user_pass, std::string database, std::string charset );
		MYSQL* CreateConnect( std::string host_name, int32_t host_port, std::string user_name, std::string user_pass, std::string database, std::string charset );
		MYSQL* GetConnect( std::string host_name, std::string database = "", std::string charset = "" );
		bool SelectDB( MYSQL*& connection, std::string host_name, std::string database );
		bool CharsetDB( MYSQL*& connection, std::string host_name, std::string charset );
		void ReturnConnect( std::string host_name, MYSQL*& connection );
		int64_t Query_E( MYSQL*& connection, std::string& sql_query, std::string& error_info );
		MYSQL_RES* Query_R( MYSQL*& connection, std::string& sql_query, std::string& error_info );
		std::string GetLastError( MYSQL*& connection );

	private:
		SysDBI_M_P* m_sysdbi_m_p;
		static SysDBI_M* m_instance;
	};

} // namespace framex

#endif // FRAMEX_SYSDBI_M_SYSDBI_M_H
