#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include<iostream>
#include "algorithm_basic.h"
#include "iterator.h"
#include "myallocator.h"
using std::cout;
using std::endl;

namespace mycontainer {

	template <class T>
	class vector{
	public:

		//---------------------------①构造、复制、移动、析构函数---------------------------
		// 无指定
		vector() {
			const size_t cap = initial_capacity; // 预留空间
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// 指定大小，初始值默认为0
		explicit vector(size_t n) { //explicit用于类内的单参数构造函数前面，防止类构造函数的隐式自动转换
			const size_t cap = mycontainer::max<size_t>(n, initial_capacity);
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (c != end_) {
				myallocator<T>::construct(c, 0);
				c++;
			}
		}
		//指定大小和初始值
		vector(size_t n, const T& value) { 
			const size_t cap = mycontainer::max<size_t>(n, initial_capacity);
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (c != end_) {
				myallocator<T>::construct(c, value);
				c++;
			}
		}
		//通过已有数组构造
		vector(T* first_, T* last_) {
			size_t len = mycontainer::length(first_, last_);
			const size_t cap = mycontainer::max<size_t>(len, initial_capacity);
			begin_ = myallocator<T>::allocate(cap);
			end_ = begin_ + len;
			capa_ = begin_ + cap;
			auto c = begin_;
			for (auto i = first_; i != last_; i++) {
				myallocator<T>::construct(c, *i);
				c++;
			}
		}
		//通过已有vector构造
		vector(const vector& copyvector) {
			size_t len = mycontainer::length(copyvector.begin_, copyvector.end_);
			const size_t cap = mycontainer::max<size_t>(len, initial_capacity);
			begin_ = myallocator<T>::allocate(cap);
			end_ = begin_ + len;
			capa_ = begin_ + cap;
			auto c = begin_;
			for (auto i = copyvector.begin_; i != copyvector.end_; i++) {
				myallocator<T>::construct(c, *i);
				c++;
			}
		}
		// 移动构造 (参数是一个右值或者将亡值的引用,直接继承资源)
		vector(vector&& copyvector) noexcept{
			begin_ = copyvector.begin_;
			end_ = copyvector.end_;
			capa_ = copyvector.capa_;
			copyvector.begin_ = nullptr;
			copyvector.end_ = nullptr;
			copyvector.capa_ = nullptr;
		}

		//序列构造(未完成)


		//复制赋值声明 (深拷贝)
		vector& operator=(const vector& assignvector);

		//移动赋值
		vector& operator=(vector&& assignvector) noexcept;

		//序列赋值（未完成）


		//析构函数
		~vector() {
			myallocator<T>::destroy(begin_, end_); //析构对象
			myallocator<T>::deallocate(begin_, capa_ - begin_); //释放空间
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		//---------------------------②访问元素---------------------------
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

		//---------------------------③容量-----------------------------
		// empty() 判空
		bool empty() const{
			return begin_ == end_;
		}
		// size() 返回vector大小
		size_t size() const{
			size_t size = end_ - begin_;
			return size;
		}
		// max_size() 返回vector最大可能大小
		size_t max_size() const{
			return static_cast<size_t>(-1) / sizeof(T); //强制类型转换
		}
		// capacity() 容器能存储数据的个数
		size_t capacity() const{
			size_t cap = capa_ - begin_;
			return cap;
		}
		// reserve(size_t n) 预留一定的内存空间（未完成）

		// shrink_to_fit()（未完成）


		//---------------------------④---------------------------

	private:
		T* begin_;
		T* end_;
		T* capa_;
		size_t initial_capacity = 8; // 未指定时/最小分配容量大小

	};

	//--------------------------函数定义---------------------------
	//复制赋值
	template<class T>
	vector<T>& vector<T>::operator=(const vector& assignvector) {
		//开辟新的空间后构造
		size_t cap = assignvector.capacity();
		size_t len = assignvector.size();
		begin_ = myallocator<T>::allocate(cap);
		end_ = begin_ + len;
		capa_ = begin_ + cap;
		auto c = begin_;
		for (auto i = assignvector.begin_; i != assignvector.end_; i++) {
			myallocator<T>::construct(c, *i);
			c++;
		}
		return *this;
		//新构造tmp后交换（未完成）
	}

	//移动赋值
	template<class T>
	vector<T>& vector<T>::operator=(vector&& assignvector) noexcept{
		//释放原空间及析构对象后继承资源
		myallocator<T>::destroy(begin_, end_); //析构对象
		myallocator<T>::deallocate(begin_, capa_ - begin_); //释放空间
		begin_ = assignvector.begin_;
		end_ = assignvector.end_;
		capa_ = assignvector.capa_;
		//以下置空操作必须要有！！
		assignvector.begin_ = nullptr;
		assignvector.end_ = nullptr;
		assignvector.capa_ = nullptr;
		return *this;
	}



} //namespace mycontainer


#endif //MYCONTAINER_VECTOR_H_

