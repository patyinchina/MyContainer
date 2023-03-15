#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include<iostream>
#include "algorithm_basic.h"
#include "myallocator.h"
//#include "construct.h" (未完成)
using std::cout;
using std::endl;

namespace mycontainer {

	template <class T>
	class vector{
	public:

		// ①构造、复制、移动、析构函数
		// 无指定
		vector() {
			const size_t cap = 8; // 预留空间
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// 指定大小，初始值默认为0
		explicit vector(size_t n) { //explicit用于类内的单参数构造函数前面，防止类构造函数的隐式自动转换
			const size_t cap = mycontainer::max<size_t>(n, 8);
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}
		//指定大小和初始值
		vector(size_t n, const T& value) { 
			const size_t cap = mycontainer::max<size_t>(n, 8);
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
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
			const size_t cap = mycontainer::max<size_t>(len, 8);
			begin_ = myallocator<T>::allocate(cap);
			end_ = begin_ + len;
			capa_ = begin_ + cap;
			auto c = begin_;
			for (auto i = first; i != last; i++) {
				*c = *i;
				c++;
			}
		}
		//通过已有vector构造
		vector(const vector& copyvector) {
			size_t len = 0;
			auto now=copyvector.begin_;
			while (now != copyvector.end_) {
				now++;
				len++;
			}
			const size_t cap = mycontainer::max<size_t>(len, 8);
			begin_ = myallocator<T>::allocate(cap);
			end_ = begin_ + len;
			capa_ = begin_ + cap;
			auto c = begin_;
			for (auto i = copyvector.begin_; i != copyvector.end_; i++) {
				*c = *i;
				c++;
			}
		}
		//移动构造(未完成)


		//序列构造(未完成)


		//赋值构造(未完成)


		//析构函数
		~vector() {
			myallocator<T>::deallocate(begin_, capa_ - begin_);
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		// ②访问元素
		// []访问
		T& operator [](const size_t n) { //重载 []
			size_t size = end_ - begin_;
			if (n >= size) {
				std::cout << "超出索引范围" << std::endl;
			} 
			assert(n < size); // 表达式为false则退出运行
			return *(begin_ + n);
		}
		// at()访问
		T& at(size_t index) {
			size_t size = end_ - begin_;
			if (index >= size) {
				std::cout << "超出索引范围" << std::endl;
			}
			assert(index < size);
			auto c = begin_;
			while (index > 0) {
				c++; index--;
			}
			return *c;
		}
		// front()访问
		T& front() {
			if (empty()) {
				std::cout << "vector为空,访问错误" << std::endl;
			}
			assert(!empty());
			return *begin_;
		}
		// back()访问
		T& back() {
			if (empty()) {
				std::cout << "vector为空,访问错误" << std::endl;
			}
			assert(!empty());
			return *(end_ - 1);
		}

		// data()
		T* data() {
			if (empty()) {
				std::cout << "vector为空,访问错误" << std::endl;
			}
			assert(!empty());
			return begin_;
		}

		// ③容量
		// 判空
		bool empty() {
			return begin_ == end_;
		}
		// 返回vector大小
		size_t size() {
			size_t size = end_ - begin_;
			return size;
		}
		// 返回vector最大可能大小
		size_t max_size() {
			return static_cast<size_t>(-1) / sizeof(T); //强制类型转换
		}
		// 容器能存储数据的个数
		size_t capacity() {
			size_t cap = capa_ - begin_;
			return cap;
		}


	private:
		T* begin_;
		T* end_;
		T* capa_;
	

	};



}


#endif //MYCONTAINER_VECTOR_H_

