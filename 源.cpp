#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <windows.h>
#include <_ZZH_.hpp>

#define N 5
using namespace std;
using namespace ZZH;

void test();


	class person {
	private:
		int age;
	public:
		int aaa;
	    person(int a) {
			this->age = a;
		}
		inline bool operator ==(const person &ps) const;
	};




	inline bool person::operator==(const person & ps) const
	{
		if (this->age == ps.age)
			return true;
		return false;
	}

	void bubbleSort1(int* a, int n) {//Ã°ÅÝÅÅÐò
		int tmp;
		for (int i = n - 1; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (a[j] > a[j + 1]) {
					tmp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = tmp;
				}
			}
		}
	}
	
	template<typename T>void swapa(T &t1, T &t2) {
		T tempt;
		tempt = t1;
		t1 = t2;
		t2 = tempt;
	}
	template<class T>class Stack {
	public:
		Stack();
		~Stack();
		void push(T t);
		T pop();
		bool isEmpty();
	private:
		T * m_pt;
		int m_maxSize;
		int m_Size;
	};
	template<class T>Stack<T>::Stack()
	{
		m_maxSize = 100;
		m_Size = 0;
		m_pt = new T[m_maxSize];

	}

	template<class T>Stack<T>::~Stack()
	{
		delete [] m_pt;
	}

	template<class T>void Stack<T>::push(T t)
	{
		m_Size++;
		m_pt[m_Size - 1] = t;
	}

	template<class T>T Stack<T>::pop()
	{
		T t = m_pt[m_Size-1];
		m_Size--;
		return t;
	}

	template<class T>bool Stack<T>::isEmpty()
	{
		return m_Size==0;
	}
	
	void FastSort(int *sort_data, int start, int end) {//¿ìËÙÅÅÐò
		if (start >= end) return;
		int A = sort_data[start];
		int i = start + 1;
		int j = end;
		while (i < j) {
			while (A < sort_data[j] && i < j) {
				j--;
			}
			while (A > sort_data[i] && i < j) {
				i++;
			}
			auto temp = sort_data[j];
			sort_data[j] = sort_data[i];
			sort_data[i] = temp;
		}
		if (sort_data[start] > sort_data[i]) {
			auto temp = sort_data[j];
			sort_data[j] = sort_data[i];
			sort_data[i] = temp;
		}
		FastSort(sort_data,start,i-1);
		FastSort(sort_data, i+1, end);
	}
	

	
	int main() {
		test();
		cin.get();
		return 0;
	}





	void test() {
	
		ZZH::_Algoritm_ a;
		int arr[] = { 1,34,78,56,100,145 ,200,201,};
		auto res = a._Sort_(8, arr);
		
			cout << res<< endl;
		
		

	}
	