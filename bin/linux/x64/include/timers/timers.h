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

#ifndef FRAMEX_TIMERS_TIMERS_H
#define FRAMEX_TIMERS_TIMERS_H

#include <ctime>
#include <chrono>
#include <stdint.h> // int32_t, int64_t
#include <functional>

#include <common/compile.h>

namespace framex {

	class Timers_P;

	class FRAMEX_TIMERS_EXPIMP Timers_K { // kernel
	public:
		Timers_K();
		~Timers_K();

	private:
		Timers_P* m_timers_p;
	};

	class FRAMEX_TIMERS_EXPIMP Timers_D { // dynamic
	public:
		Timers_D();
		~Timers_D();

	public:
		void Start();
		void Stop();
		int32_t AddTimerSpace( std::chrono::duration<int64_t> duration, double delay_s, int32_t times, std::function<void( int32_t, int64_t )> callback );
		int32_t AddTimerPoint( std::chrono::duration<int64_t> duration, time_t datetime, int32_t times, std::function<void( int32_t, int64_t )> callback );
		void DelTimerSpace( int32_t id );
		void DelTimerPoint( int32_t id );

	public:
		void Test_TimerCallBack( int32_t timer_id, int64_t delay_ns );

	private:
		Timers_P* m_timers_p;
	};

	class FRAMEX_TIMERS_EXPIMP Timers_S { // static
	public:
		Timers_S();
		~Timers_S();

	public:
		static Timers_S* GetInstance();

	public:
		void Start();
		void Stop();
		int32_t AddTimerSpace( std::chrono::duration<int64_t> duration, double delay_s, int32_t times, std::function<void( int32_t, int64_t )> callback );
		int32_t AddTimerPoint( std::chrono::duration<int64_t> duration, time_t datetime, int32_t times, std::function<void( int32_t, int64_t )> callback );
		void DelTimerSpace( int32_t id );
		void DelTimerPoint( int32_t id );

	private:
		Timers_P* m_timers_p;
		static Timers_S* m_instance;
	};

} // namespace framex

#endif // FRAMEX_TIMERS_TIMERS_H
