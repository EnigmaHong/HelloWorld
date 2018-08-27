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

#define eps 1e-6;

namespace ZZH {
	

	inline namespace STD {
		template<class _ARG>
		inline constexpr _ARG _abs_(const _ARG &src) {//ZZH::_abs_(src) 求src的绝对值
			return src > 0 ? +src : -src;
		}

		template<class _ARG>
		inline constexpr _ARG _sqe_(const _ARG &src) {//ZZH::_sqe_(src) 求src的平方
			return src * src;
		}

		template<class _ARG>
		inline constexpr _ARG _pow_(const _ARG &src, const int n) {//ZZH::_pow_(src,n)求src的n次方
			_ARG result=1;
			for (int i = 0; i < n; i++) {
				result *= src;
			}
			return result;
		}

		template<class _ARG>
		inline constexpr _ARG _sqrt_(const _ARG &src) {
			if (src == 1 || src == 0) return src;
			_ARG x, y;
			x = 0.0; y = src / 2;
			while (x != y) {
				x = y;
				y = (x + src / x) / 2;
			}
			return x;
		}
	};
}