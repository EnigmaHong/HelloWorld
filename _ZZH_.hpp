#pragma once
#include <cstddef>
#include <cstdint>
#include <cassert>
#include <limits>
#include <type_traits>
#include <initializer_list>
#include <new>
#include <exception>
#include <typeinfo>
#include <utility>

#include "__CSC__/csc.hpp"
//#include "__CSC__/csc_array.hpp"
//#include "__CSC__/csc_stream.hpp"
//#include "__CSC__/csc_stream.hpp.default.inl"
//#include "__CSC__/csc_string.hpp"
//#include "__CSC__/csc_string.hpp.default.inl"
//#include "__CSC__/csc_math.hpp"
//#include "__CSC__/csc_math.hpp.default.inl"
//#include "__CSC__/csc_graphics.hpp"

#define _eps_ 1e-6;
#define _PI_ 3.14159265358979323846

//常用的函数一般不使用宏定义
//#ifndef _max_  //_max_(a,b)返回最大值
//#define _max_(a,b)            (((a) > (b)) ? (a) : (b))
//#endif
//
//#ifndef  _min_ //_min_(a,b)返回最小值
//#define _min_(a,b)			   (((a)<(b)) ? (a) : (b))
//#endif // ! _min_

using VAR32 = std::int32_t;
using VAR64 = std::int64_t;

static constexpr VAR32 VAR32_MAX = VAR32(2147483647);
static constexpr VAR32 VAR32_MIN = ~VAR32_MAX;
static constexpr VAR64 VAR64_MAX = VAR64(9223372036854775807);
static constexpr VAR64 VAR64_MIN = ~VAR64_MAX;

#ifdef __CSC_CONFIG_VAR32__
using VAR = VAR32;

static constexpr VAR VAR_MAX = VAR32_MAX;
static constexpr VAR VAR_MIN = VAR32_MIN;
#elif defined __CSC_CONFIG_VAR64__
using VAR = VAR64;

static constexpr VAR VAR_MAX = VAR64_MAX;
static constexpr VAR VAR_MIN = VAR64_MIN;
#endif

using _length_ = VAR;


template <class _TYPE>
using DEF = _TYPE;
template<class _TYPE>
using PTR = _TYPE * ;


namespace ZZH {

	inline namespace STD {
		template<class _SRC>
		inline constexpr _SRC _abs_(const _SRC &src) {//ZZH::_abs_(src) 求src的绝对值
			return src > 0 ? +src : -src;
		}

		template<class _SRC>
		inline constexpr _SRC _sqe_(const _SRC &src) {//ZZH::_sqe_(src) 求src的平方
			return src * src;
		}

		template<class _SRC>
		inline constexpr _SRC _pow_(const _SRC &src, const int n) {//ZZH::_pow_(src,n)求src的n次方
			_SRC result=1;
			for (int i = 0; i < n; i++) {
				result *= src;
			}
			return result;
		}

		template<class _SRC>
		inline constexpr _SRC _sqrt_(const _SRC &src) {//ZZH::_sqrt_(src)求src的开方,有bug
			if (src == 1 || src == 0) return src;
			_SRC x, y;
			x = 0.0; y = src / 2;
			while (x != y) {
				x = y;
				y = (x + src / x) / 2;
			}
			return x;
		}

		//求最值，有bug _SRC
		template<class _SRC>
		inline constexpr _SRC _max_(const _SRC &src1, const _SRC &src2) {
			return (src1 > src2 ? src1 : src2);
		}
		template<class _SRC>
		inline constexpr _SRC _min_(const _SRC &src1, const _SRC &src2) {
			return (src1 > src2 ? src2 : src1);
		}

		template<class _SRC>
		inline  void _swap_(_SRC &src1, _SRC &src2)noexcept {//ZZH::_swap_(src1,src2)交换两个数 
			auto temp = std::move(src1);
			src1 = std::move(src2);
			src2 = std::move(temp);
		}

		template<class _SRC>
		inline constexpr _SRC _DegreeToRadian_(const _SRC &degree) {//ZZH::_DegreeToRadian_(30.0) 度转弧度 
			static_assert(std::is_floating_point<_SRC>::value,"DegreeToRadian: must be floating point.");
			return degree * _PI_ / 180;
		}

		template<class _SRC>
		inline constexpr _SRC _RadianToDegree_(const _SRC &radian) {//ZZH::_RadianToDegree_(30.0) 弧度转度 
			static_assert(std::_Is_floating_point<_SRC>::value,"RadianToDegree must be floating point.");
			return radian *180/_PI_;
		}

		template<typename _SRC>
		inline constexpr _SRC _sum_(_SRC &src) {
			auto number = src.size();
			auto sum = 0.0;
			for (int i = 0; i < number; i++) {
				sum += src[i];
			}
			return sum;
		}






	};


}