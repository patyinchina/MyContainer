#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include<iostream>
#include "myallocator.h"
#include "construct.h"
using std::cout;
using std::endl;

namespace mycontainer {

	template <class T>
	class vector{
	public:

		// ①构造、复制、移动、析构函数
		// 无指定
		vector() {
			begin = myallocator<T>::allocate(); //分配内存
			end = begin;
		}
		// 指定大小，初始值默认为0
		explicit vector(size_t n) { //explicit用于类内的单参数构造函数前面，防止类构造函数的隐式自动转换
			begin = myallocator<T>::allocate(n); //分配内存
			end = begin + n;
			auto c = begin;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}
		//指定大小和初始值
		vector(size_t n, const T& value) { 
			begin = myallocator<T>::allocate(n); //分配内存
			end = begin + n;
			auto c = begin;
			while (n > 0) {
				*c = value;
				c++;
				n--;
			}
		}
		//通过已有数组构造
		vector(T* first, T* last) { 
			size_t len = 0;
			auto now = first;
			while (now != last) {
				now++;
				len++;
			}
			begin = myallocator<T>::allocate(len);
			end = begin + len;
			auto c = begin;
			for (auto i = first; i != last; i++) {
				*c = *i;
				c++;
			}
		}
		//通过已有vector构造
		vector(const vector& copyvector) {
			size_t len = 0;
			auto now=copyvector.begin;
			while (now != copyvector.end) {
				now++;
				len++;
			}
			begin = myallocator<T>::allocate(len);
			end = begin + len;
			auto c = begin;
			for (auto i = copyvector.begin; i != copyvector.end; i++) {
				*c = *i;
				c++;
			}
		}
		//移动构造(未完成)


		//序列构造(未完成)


		//赋值构造(未完成)


		//析构函数(未完成)


		// ②访问元素
		// []访问
		T& operator [](const size_t n) { //重载 []
			size_t size=static_cast<T>(end - begin);
			if (n >= size) {
				std::cout << "超出索引范围" << std::endl;
			} 
			assert(n < size); // 表达式为false则退出运行
			return *(begin + n);
		}
		// at()访问(未完成)
		T& at(size_t index) {
			
		}
		// front()访问
		T& front() {
			return *begin;
		}
		// back()访问(未完成)


		// data()访问(未完成)



	private:
		T* begin;
		T* end;
	

	};



}


#endif //MYCONTAINER_VECTOR_H_

