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

#include "csc.hpp"
//#include "__CSC__/csc_array.hpp"
//#include "__CSC__/csc_algorithm.hpp"
//#include "__CSC__/csc_stream.hpp"
//#include "__CSC__/csc_stream.hpp.default.inl"
//#include "__CSC__/csc_string.hpp"
//#include "__CSC__/csc_string.hpp.default.inl"
//#include "__CSC__/csc_math.hpp"
//#include "__CSC__/csc_math.hpp.default.inl"
//#include "__CSC__/csc_graphics.hpp"

#define _eps_ 1e-6;
#define _PI_ 3.14159265358979323846
#define IMGNUM 100000

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

char img_files[IMGNUM][1000];


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

		template<class Inputterator, class _SRC>//计算vertor元素之和ZZH::_sum_(a.begin(), a.end(), init)
		_SRC _sum_(Inputterator first, Inputterator last, _SRC init); 
		template<class Inputterator, class _SRC>
		_SRC _sum_(Inputterator first, Inputterator last, _SRC init)
		{
			while (first != last) {
				init += *first;
				first++;
			}
			return init;
		}

	


	};

	class _vector_ {
	private:
		float x, y, z;
	public :
		_vector_() {}
		_vector_(const _vector_ &src) :x(src.x), y(src.y), z(src.z) {}
		_vector_(float nx, float ny, float nz) :x(nx), y(ny), z(nz) {}
		_vector_ &operator =(const _vector_ &src) {
			x = src.x; y = src.y; z = src.z;
			return *this;
		}
		bool operator ==(const _vector_ &src)const {//d1==d2  判断两向量是否所有元素相等,返回1全相等，0不全相等
			return x == src.x && y == src.y && z == src.z ;
		}
		bool operator !=(const _vector_ &src)const {//d1!=d2 返回1全不等，0全相等
			return x != src.x || y != src.y || z != src.z ;
		}

		void _print_() {//打印一个三维向量 d1._print_()
			//std::cout <<"["<< src.x << "," << src.y << "," << src.z<<"]" << std::endl;
			std::cout << "[" << x << "," << y << "," << z << "]" << std::endl;
		}
		void _zero_() { x = y = z = 0.0f; }//d1._zero_() 将d1所有元素设置为0
		_vector_ operator -()const {//-(d1) 所有元素取负
			return _vector_(-x, -y, -z);
		}
		_vector_ operator +(const _vector_ &src)const {//d3 = d1+d2
			return _vector_(x + src.x, y + src.y, z + src.z);
		}
		_vector_ operator -(const _vector_ &src)const {//d3 = d1-d2
			return _vector_(x - src.x, y - src.y, z - src.z);
		}

		_vector_ operator *(const float a)const {//d3 = d1*a
			return _vector_(x*a, y*a, z*a);
		}
		_vector_ operator /(const float a)const {//d3 = d1/a
			//assert(a == 0.0, "Bad arguments.....leading to division by zero");//bug
		    auto temp = 1.0 / a;
			return _vector_(x*temp, y*temp, z*temp);
		}

		_vector_ operator +=(const _vector_ &src) {//d1 +=d2 
			return _vector_(x += src.x, y += src.y, z += src.z);
		}
		_vector_ operator -=(const _vector_ &src) {//d1-=d2
			x -= src.x; y -= src.y; z -= src.z;
			return *this;
		}
		_vector_ operator *=(const float &a) {//d1*=a
			return _vector_(x *= a, y *= a, z *= a);
		}
		_vector_ operator /=(const float &a) {//d1 /=a
			//assert(a == 0.0, "Bad arguments.....leading to division by zero");//bug
			auto temp = 1.0 / a;
			return _vector_(x*=temp, y*=temp, z*=temp);
		}

		void _normalize_() {//d1._normalize_(); 向量标准化
			auto temp = 1.0/_sqrt_(x*x +y*y + z*z);
			//assert(temp == 0.0, "Bad arguments.....leading to division by zero");//bug
			x *= temp; y *= temp; z *= temp;
		}

		float operator *(const _vector_ &src) const{//d = d1* d2 计算两向量的点乘，返回一个数
			return (x*src.x + y * src.y + z * src.z);
		}
	
		inline float _vectorMag_() const{//d1._vectorMag_() d1是_vector3D_的一个对象，计算向量d1的模,返回一个数
			return _sqrt_(x*x+y*y+z*z);
		}

		inline _vector_ _crossProduct_(const _vector_ &src1,const _vector_ &src2) const{//d3 = d1._crossProduct_(d1, d2);  计算两向量叉积
			return _vector_(src1.y*src2.z- src1.z*src2.y, src1.z*src2.x- src1.x*src2.z, src1.x*src2.y- src1.y*src2.x);
		}

		inline float _distance_(const _vector_ &src1, const _vector_ &src2) const{//d3 = d1._distance_(d1, d2) 计算两向量距离
			auto dx = src1.x - src2.x;
			auto dy = src1.y - src2.y;
			auto dz = src1.z - src2.z;
			return _sqrt_(dx*dx+dy*dy+dz*dz);
		}

	};

	class _matrix_ {
	private:
		int m;//矩阵行
		int n;//矩阵列
		float **arr;//保存二维数组的元素
	public:
		_matrix_() {
			//默认构造函数
		}
		_matrix_(int mm, int nn) {
			m = mm;
			n = nn;
			arr = (float **)malloc(sizeof(float *)*m);
			for (int i = 0; i < m; i++) {
				*(arr + i) = (float *)malloc(sizeof(float)*n);
			}//给矩阵分配内存
			/*std::cout << "初始化矩阵，以空格隔开，请输入数:" << std::endl;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					std::cin >> arr[i][j];
				}
			}*/
		}

		inline int _write_(int i,int j,float src) {//初始化矩阵 mat1._write_(i, j, i);
			arr[i][j] = src;
			return 0;
		}
		
		_matrix_(const _matrix_ &is) {//拷贝构造函数
			m = is.m;
			n = is.n;
			arr = new float*[m];
			for (int i = 0; i < m; i++) {
				arr[i] = new float[n];
			}
			arr = is.arr;
		}

		inline int _Madd_(const _matrix_ & is) {//矩阵加法运算 mat1._Madd_(mat2);
			if (m != is.m || n != is.n) {
				std::cout << "行列必须一致" << std::endl;
				return -1;
			}
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					arr[i][j] += is.arr[i][j];
				}
			}
			return 0;
		}

		inline _matrix_ _Mmul_(const _matrix_ & is) {//矩阵相乘mat3 = mat2._Mmul_(mat1);
			if (this->n != is.n) {
				std::cout << "不符合矩阵相乘规则." << std::endl;
			}
			_matrix_ M(this->m, is.n);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					M.arr[i][j] = 0;
					for (int k = 0; k < is.m; k++) {
						M.arr[i][j] += this->arr[i][k] * is.arr[k][j];
					}
				}
			}
			return M;
		}

		inline void _display_() {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					std::cout << arr[i][j]<<" ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		inline int _row_() {
			return m;
		}
		inline int _col_() {
			return n;
		}

		
	};

	class _Algoritm_ {
	private:

	public:
		template<typename T>
		inline T const & _Mi_mod_(T src1, T src2, T const& mod_data) {//计算src1^src2 % mod_data 使用位运算
			T res = 1 % mod_data;
			while (src2)
			{
				if (src2 & 1) {
					res = res * 1ll * src1 % mod_data;//1ll 表示转换为long long型
				}
				src1 = src1 * src1 * 1ll % mod_data;
				src2 >>= 1;
			}
			return res;
		}

		template<typename T>
		inline T const & _More_Mi_(T src1, T src2)
		{//计算src1^src2
			T res = 1;
			while (src2) {
				if (src2 & 1) {
					res = res * 1ll * src1;
				}
				src1 = src1 * src1 * 1ll;
				src2 >>= 1;
			}
			return res;
		}

		template<typename T>
		inline T const & _Fibonacci_(T const &num, T array[])
		{//斐波那契数列
			array[num];
			array[0] = 1;
			array[1] = 1;
			for (int i = 2; i < num; i++) {
				array[i] = array[i - 1] + array[i - 2];
			}
			return 0;
		}

		template<typename T>
		inline T const & _Bubble_(T const & len, T array[])
		{//冒泡排序算法
			for (int i = len - 1; i > 0; i--) {
				for (int j = 0; j < i; j++) {
					if (array[j] > array[j + 1]) {
						T temp = array[j + 1];
						array[j + 1] = array[j];
						array[j] = temp;
					}
				}
			}
			return 0;
		}
		template<typename T>
		inline T const & _Binary_(T const & len, T const & data, T array[])
		{//二分查找算法
			T start = 0;
			T end = len - 1;
			while (start <= end) {
				T temp = (start + end) / 2;
				if (array[temp] == data) {
					return temp;
				}
				if (array[temp] < data) {
					start = temp + 1;
				}
				else {
					end = temp - 1;
				}
			}
			return len;
		}

		template<typename T, size_t N>
		inline size_t const & _Count_(T const(&array)[N])
		{//函数模板参数自动返回数组长度
			return N;
		}

		template<typename T>
		inline bool const & _Sort_(T const & len, T array[])
		{//判读数组是否是有序
			T pop = array[0];
			for (int i = 0; i < len - 1; i++) {
				if (array[i] > array[i + 1]) {
					if (array[i] != pop) {
						return false;
					}
					T temp = array[i + 1];
					array[i + 1] = array[i];
					array[i] = temp;
					pop = array[i + 1];
				}
			}
			return true;
		}

		template<typename T>
		inline T const & _Factorial_(T const & src)
		{//递归计算阶乘
			if (src == 1) {
				return 1;
			}
			else {
				return src * _Factorial_(src - 1);
			}
		}

		template<typename T>
		inline T const & _Sum_(T const & len, T const array[])
		{//使用递归算法求数组元素和
			if (len == 0) {
				return 0;
			}
			else {
				T size = len - 1;
				if (size == 0) {
					return array[0];
				}
				else {
					return array[size] + _Sum_(size, array);
				}
			}
		}

		template<typename T>
		inline T const &_Maxvalue_(T const & len, T const array[])
		{//使用递归算法计算数组最大值
			if (len == 0) {
				return 0;
			}
			else {
				T size = len - 1;
				if (size == 0) {
					return array[0];
				}
				else {
					if (_Maxvalue_(size, array) < array[size]) {
						return array[size];
					}
					else {
						return _Maxvalue_(size, array);
					}
				}
			}
		}

		template<typename T>
		inline T const &_Minvalue_(T const & len, T const array[])
		{//使用递归算法计算数组最小值
			if (len == 0) {
				return 0;
			}
			else {
				T size = len - 1;
				if (size == 0) {
					return array[0];
				}
				else {
					if (_Minvalue_(size, array) < array[size]) {
						return _Minvalue_(size, array);
					}
					else {
						return array[size];
					}
				}
			}
		}

		template<typename T>
		inline T const & _FastSort_(T left, T right, T array[])
		{//使用递归实现快速排序算法
			T pivot = array[left];
			if (left > right) return -1;
			int i = left;
			int j = right;
			while (i < j) {
				while (array[j] >= pivot && i < j) {
					j--;
				}
				while (array[i] <= pivot && i < j) {
					i++;
				}
				if (i < j) {
					auto temp = array[j];
					array[j] = array[i];
					array[i] = temp;
				}
			}
			array[left] = array[i];
			array[i] = pivot;
			_FastSort_(left, i - 1, array);
			_FastSort_(i + 1, right, array);
		}

		
		
	};

	



}