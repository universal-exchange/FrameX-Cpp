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

#ifndef FRAMEX_NETLIB_ASIO_CLIENT_H
#define FRAMEX_NETLIB_ASIO_CLIENT_H

#include <string>
#include <stdint.h>

#include <common/compile.h>

namespace framex {

	struct ConnectAsio;

	class AsioClient_P;

	class FRAMEX_NETLIB_EXPIMP AsioClient {
	public:
		AsioClient();
		~AsioClient();

	public:
		void StartNetwork();
		void StopNetwork();
		bool IsNetworkStarted();

		ConnectAsio* Client_AddConnect( std::string address, int32_t port, int32_t node_flag, std::string node_type, int32_t time_out_sec );

		int32_t Client_ReadData_Sy( ConnectAsio* connect_info, char* data, int32_t size );
		int32_t Client_SendData_Sy( ConnectAsio* connect_info, const char* data, int32_t size );

		void Client_CloseByUser( ConnectAsio* connect_info );

	private:
		AsioClient_P* m_asio_client_p;
	};

} // namespace framex

#endif // FRAMEX_NETLIB_ASIO_CLIENT_H
