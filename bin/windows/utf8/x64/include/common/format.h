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

#ifndef FRAMEX_COMMON_FORMAT_H
#define FRAMEX_COMMON_FORMAT_H

#include <string>
#include <stdint.h> // int32_t, int64_t
#include <string.h>

#include "sysdef.h"

namespace framex {

    // https://stackoverflow.com/questions/4351371/c-performance-challenge-integer-to-stdstring-conversion

    inline int32_t fast_format_bin( char* result, int32_t width, uint64_t number ) { // Windows 32 位编译时只能转 unsigned long 长度
        static const char* form_let = "0123456789abcdefghijk";
        int32_t real_width = 0;
#ifdef __OS_WINDOWS__
        unsigned long win_index = 0;
#ifdef __OS_WINDOWS_32__
		_BitScanReverse( &win_index, (unsigned long)number );
#endif
#ifdef __OS_WINDOWS_64__
		_BitScanReverse64( &win_index, number );
#endif
        real_width = (int32_t)win_index + 1;
#endif
#ifdef __OS_LINUX__
        real_width = sizeof( number ) * 8 - __builtin_clzll( number );
#endif
        if( real_width < width ) {
            real_width = width;
        }
        uint64_t note_width = real_width;
        do {
            const uint64_t form_pos = number & 1;
            *(result + note_width - 1) = form_let[form_pos];
            note_width--;
			number >>= 1;
        } while ( number );
        return real_width;
    }

    inline int32_t fast_format_bin( char* result, int32_t width, int64_t number ) {
        return fast_format_bin( result, width, (uint64_t)number );
    }

    inline int32_t fast_format_dec( char* result, int32_t width, uint64_t number ) { // 速度是 snprintf 的十多倍
        static const char* dec_form = 
            "00010203040506070809"
            "10111213141516171819"
            "20212223242526272829"
            "30313233343536373839"
            "40414243444546474849"
            "50515253545556575859"
            "60616263646566676869"
            "70717273747576777879"
            "80818283848586878889"
            "90919293949596979899";
		const int32_t fix_length = 20; // uint64_t 最大 18446744073709551615
        char fix_buffer[fix_length];
        int32_t write_index = fix_length;
        do {
            const uint64_t form_pos = (uint64_t)( (number % 100) * 2 );
            *(fix_buffer + write_index - 1) = dec_form[form_pos + 1];
            *(fix_buffer + write_index - 2) = dec_form[form_pos];
            write_index -= 2;
			number /= 100;
        } while( number );
        if( '0' == fix_buffer[write_index] ) {
            write_index++;
        }
        while( fix_length - write_index < width ) {
            write_index--;
            fix_buffer[write_index] = '0';
        }
        memcpy( result, fix_buffer + write_index, fix_length - write_index );
        return fix_length - write_index;
    }

    inline int32_t fast_format_dec( char* result, int32_t width, int64_t number ) { // int64_t 最小 -9223372036854775808 最大 9223372036854775807
        if( number < 0 ) {
            *result = '-';
            number = -number;
            return 1 + fast_format_dec( result + 1, width - 1, (uint64_t)number );
        }
        return fast_format_dec( result, width, (uint64_t)number );
    }

    inline int32_t fast_format_hex( char* result, int32_t width, uint64_t number ) { // Windows 32 位编译时只能转 unsigned long 长度
        static const char* form_let = "0123456789abcdefghijk";
        static const char* form_hex = 
            "000102030405060708090A0B0C0D0E0F"
            "101112131415161718191A1B1C1D1E1F"
            "202122232425262728292A2B2C2D2E2F"
            "303132333435363738393A3B3C3D3E3F"
            "404142434445464748494A4B4C4D4E4F"
            "505152535455565758595A5B5C5D5E5F"
            "606162636465666768696A6B6C6D6E6F"
            "707172737475767778797A7B7C7D7E7F"
            "808182838485868788898A8B8C8D8E8F"
            "909192939495969798999A9B9C9D9E9F"
            "A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
            "B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
            "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
            "D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
            "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
            "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
        int32_t real_width = 0;
#ifdef __OS_WINDOWS__
        unsigned long win_index = 0;
#ifdef __OS_WINDOWS_32__
		_BitScanReverse( &win_index, (unsigned long)number );
#endif
#ifdef __OS_WINDOWS_64__
		_BitScanReverse64( &win_index, number );
#endif
        real_width = (int32_t)win_index + 1;
#endif
#ifdef __OS_LINUX__
        real_width = sizeof( number ) * 8 - __builtin_clzll( number );
#endif
        switch( real_width ) {
			case  1: case  2: case  3: case  4: real_width =  1; break;
			case  5: case  6: case  7: case  8: real_width =  2; break;
			case  9: case 10: case 11: case 12: real_width =  3; break;
			case 13: case 14: case 15: case 16: real_width =  4; break;
			case 17: case 18: case 19: case 20: real_width =  5; break;
			case 21: case 22: case 23: case 24: real_width =  6; break;
			case 25: case 26: case 27: case 28: real_width =  7; break;
			case 29: case 30: case 31: case 32: real_width =  8; break;
			case 33: case 34: case 35: case 36: real_width =  9; break;
			case 37: case 38: case 39: case 40: real_width = 10; break;
			case 41: case 42: case 43: case 44: real_width = 11; break;
			case 45: case 46: case 47: case 48: real_width = 12; break;
			case 49: case 50: case 51: case 52: real_width = 13; break;
			case 53: case 54: case 55: case 56: real_width = 14; break;
			case 57: case 58: case 59: case 60: real_width = 15; break;
			case 61: case 62: case 63: case 64: real_width = 16; break;
        }
        if( real_width < width ) {
            real_width = width;
        }
        uint64_t note_width = real_width;
        while( number && note_width >= 2 ) {
            const uint64_t form_pos = (uint64_t)( (number % 256) * 2 );
            *(result + note_width - 1) = form_hex[form_pos + 1];
            *(result + note_width - 2) = form_hex[form_pos];
            note_width -= 2;
			number /= 256;
        } 
        if( number ) {
            *result = form_let[number % 16];
            note_width --;
        }
        while( note_width-- != 0 ) {
            *(result + note_width) = '0';
        }
        return real_width;
    }

    inline int32_t fast_format_hex( char* result, int32_t width, int64_t number ) {
        return fast_format_hex( result, width, (uint64_t)number );
    }

    inline int32_t fast_format_pointer( char* result, const void* pointer ) {
        if( pointer == nullptr ) {
            memcpy( result, "null", 4 );
            return 4;
        }
        int32_t write_bytes = 2;
        memcpy( result, "0x", 2 );
        write_bytes += fast_format_hex( result + write_bytes, 0, (uint64_t)pointer );
        return write_bytes;
    }

    // YYYY-MM-DD HH:MM:SS 需保证 result 数组长度为 20
    inline int32_t fast_format_datetime( char* result, tm& now_time ) { // 速度是 strftime 的 200% 多
	    int32_t write_bytes = 0;
		write_bytes += fast_format_dec( result + write_bytes, 4, (uint64_t)( now_time.tm_year + 1900 ) );
		*(result + write_bytes++) = '-';
		write_bytes += fast_format_dec( result + write_bytes, 2, (uint64_t)( now_time.tm_mon + 1 ) );
		*(result + write_bytes++) = '-';
		write_bytes += fast_format_dec( result + write_bytes, 2, (uint64_t)now_time.tm_mday );
		*(result + write_bytes++) = ' ';
		write_bytes += fast_format_dec( result + write_bytes, 2, (uint64_t)now_time.tm_hour );
        *(result + write_bytes++) = ':';
        write_bytes += fast_format_dec( result + write_bytes, 2, (uint64_t)now_time.tm_min );
        *(result + write_bytes++) = ':';
        write_bytes += fast_format_dec( result + write_bytes, 2, (uint64_t)now_time.tm_sec );
        return write_bytes;
    }

    // YYYY-MM-DD HH:MM:SS.mmmuuunnn 需保证 result 数组长度为 24 或 27 或 30 且 mun_length 为 3 或 6 或 9
    inline int32_t fast_format_datetime( char* result, tm& now_time, int32_t mun_second, int32_t mun_length ) {
		int32_t write_bytes = fast_format_datetime( result, now_time );
		*(result + write_bytes++) = '.';
		write_bytes += fast_format_dec( result + write_bytes, mun_length, (uint64_t)mun_second );
        return write_bytes;
    }

    inline int32_t fast_format_float( char* result, float number ) { // 注意：要求 result 数组长度 >= 7
        if( std::isnan( number ) ) {
            memcpy( result, "nan", 3 );
            return 3;
        }
        else if( std::isinf( number ) ) {
            memcpy( result, "inf", 3 );
            return 3;
        }
        double fabs_temp = std::fabs( number );
        if( fabs_temp < 0.0001 || fabs_temp > 0xFFFFFFFULL ) {
#ifdef __OS_WINDOWS__
			_gcvt_s( result, 7, number, 7 ); // float 绝对能保证的精度是 6 位
#endif
#ifdef __OS_LINUX__
            gcvt( number, 7, result );
#endif
            int32_t length = (int32_t)strlen( result );
            return length;
        }
        if( number < 0.0 ) {
			*result = '-';
            double int_part = 0;
            uint64_t float_part = (uint64_t)( modf( fabs_temp, &int_part ) * 10000 );
            int32_t writed_length = 1 + fast_format_dec( result + 1, 0, (uint64_t)int_part );
            if( float_part > 0 ) {
                *(result + writed_length) = '.';
                return writed_length + 1 + fast_format_dec( result + writed_length + 1, 4, (uint64_t)float_part );
            }
            return writed_length;
        }
        double int_part = 0;
		static const char* form_let = "0123456789";
        uint64_t float_part = (uint64_t)( modf( fabs_temp, &int_part ) * 10000 );
        int32_t writed_length = fast_format_dec( result, 0, (uint64_t)int_part );
        if( float_part > 0 ) {
            *(result + writed_length) = '.';
            writed_length++;
            int32_t width = 4;
            int32_t float_temp = (int32_t)float_part;
            while( 0 == float_temp % 10 && width > 1 ) {
                width--;
                float_temp /= 10;
            }
            writed_length += width;
            float_temp = (int32_t)float_part;
            switch( width ) {
            case 1: {
                *(result + writed_length - 1) = form_let[float_temp / 1000];
                break;
			}
            case 2: {
                *(result + writed_length - 2) = form_let[float_temp / 1000];
                *(result + writed_length - 1) = form_let[float_temp / 100 % 10];
                break;
			}
            case 3: {
                *(result + writed_length - 3) = form_let[float_temp / 1000];
                *(result + writed_length - 2) = form_let[float_temp / 100 % 10];
                *(result + writed_length - 1) = form_let[float_temp / 10 % 10];
                break;
			}
            case 4: {
                *(result + writed_length - 4) = form_let[float_temp / 1000];
                *(result + writed_length - 3) = form_let[float_temp / 100 % 10];
                *(result + writed_length - 2) = form_let[float_temp / 10 % 10];
                *(result + writed_length - 1) = form_let[float_temp % 10];
                break;
			}
            default:
                break;
            }
        }
        return writed_length;
    }

    inline int32_t fast_format_double( char* result, double number ) { // 注意：要求 result 数组长度 >= 16
        int32_t fp_class = std::fpclassify( number );
        switch( fp_class ) {
        case FP_NAN:
            memcpy( result, "nan", 3 );
            return 3;
        case FP_INFINITE:
            memcpy( result, "inf", 3 );
            return 3;
        }
        double fabs_temp = std::fabs( number );
        if( fabs_temp < 0.0001 || fabs_temp > 0xFFFFFFFFFFFFFFFULL ) {
#ifdef __OS_WINDOWS__
			_gcvt_s( result, 16, number, 16 ); // double 绝对能保证的精度是 15 位
#endif
#ifdef __OS_LINUX__
			gcvt( number, 16, result );
#endif
            int32_t length = (int32_t)strlen( result );
            return length;
        }
        if( number < 0.0 ) {
			*result = '-';
            double int_part = 0;
            uint64_t float_part = (uint64_t)( modf( fabs_temp, &int_part ) * 10000 );
            int32_t writed_length = 1 + fast_format_dec( result + 1, 0, (uint64_t)int_part );
            if( float_part > 0 ) {
                *(result + writed_length) = '.';
                return writed_length + 1 + fast_format_dec( result + writed_length + 1, 4, (uint64_t)float_part );
            }
            return writed_length;
        }
        double int_part = 0;
		static const char* form_let = "0123456789";
        uint64_t float_part = (uint64_t)( modf( fabs_temp, &int_part ) * 10000 );
        int32_t writed_length = fast_format_dec( result, 0, (uint64_t)int_part );
        if( float_part > 0 ) {
            *(result + writed_length) = '.';
            writed_length++;
            int32_t width = 4;
            int32_t float_temp = (int32_t)float_part;
            while( 0 == float_temp % 10 && width > 1 ) {
                width--;
                float_temp /= 10;
            }
            writed_length += width;
            float_temp = (int32_t)float_part;
            switch( width ) {
            case 1: {
                *(result + writed_length - 1) = form_let[float_temp / 1000];
                break;
			}
            case 2: {
                *(result + writed_length - 2) = form_let[float_temp / 1000];
                *(result + writed_length - 1) = form_let[float_temp / 100 % 10];
                break;
			}
            case 3: {
                *(result + writed_length - 3) = form_let[float_temp / 1000];
                *(result + writed_length - 2) = form_let[float_temp / 100 % 10];
                *(result + writed_length - 1) = form_let[float_temp / 10 % 10];
                break;
			}
            case 4: {
                *(result + writed_length - 4) = form_let[float_temp / 1000];
                *(result + writed_length - 3) = form_let[float_temp / 100 % 10];
                *(result + writed_length - 2) = form_let[float_temp / 10 % 10];
                *(result + writed_length - 1) = form_let[float_temp % 10];
                break;
			}
            default:
                break;
            }
        }
        return writed_length;
    }

} // namespace framex

#endif // FRAMEX_COMMON_FORMAT_H
