#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

// 实现vector类的基本功能，包括构造、复制、移动、析构函数，访问元素，容量，迭代器，修改元素功能
// 访问元素：重载[]、at、front、back、data
// 容量：empty、size、maxsize、capacity、reserve、shrink_to_fit
// （正向）迭代器：begin、end、cbegin、cend
// 修改：assign、emplace、emplace_back、push_back、pop_back、insert、erase、clear、resize、reverse、swap

// 暂无异常处理
// 暂未完成反向迭代器

// assert报告debug错误

#include<assert.h> // debug时报告错误的头文件
#include<iostream>
#include <initializer_list>
#include "algorithm_basic.h"
#include "iterator.h"
#include "myallocator.h"

namespace mycontainer {

	

	template <class T>
	class vector{
	public:

		// vector的(嵌套)类型定义
		//typedef mycontainer::myallocator<T>              allocator_type;
		//typedef typename allocator_type::value_type      value_type; // typename 告诉编译器是一个类型，而非静态数据成员或成员函数
		
		// vector类型定义
		typedef T  value_type;   
		typedef T* iterator;
		typedef T& reference;
		typedef const T* const_iterator;
		typedef const T& const_reference;

		//---------------------------①构造、复制、移动、析构函数---------------------------
		// 无指定
		vector() {
			const size_t cap = initial_capacity; // 预留空间
			begin_ = myallocator<T>::allocate(cap); //分配内存
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// 指定大小，初始值默认为0
		explicit vector(size_t n) { //explicit用于类内的单参数构造函数前面，防止类构造函数的隐式自动转换，需要重载 =
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
		vector(size_t n, const_reference value) {
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
		vector(const_iterator first_, const_iterator last_) {
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
		//通过已有vector构造 (深拷贝)
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

		//序列构造
		vector(std::initializer_list<T> inlist){
			size_t len = mycontainer::length(inlist.begin(), inlist.end());
			const size_t cap = mycontainer::max<size_t>(len, initial_capacity);
			begin_ = myallocator<T>::allocate(cap);
			end_ = begin_ + len;
			capa_ = begin_ + cap;
			auto c = begin_;
			for (auto i = inlist.begin(); i != inlist.end(); i++) {
				myallocator<T>::construct(c, *i);
				c++;
			}
		}

		//复制赋值声明 (深拷贝)
		vector& operator=(const vector& assignvector);

		//移动赋值
		vector& operator=(vector&& assignvector) noexcept;

		//序列赋值
		vector& operator=(std::initializer_list<T> inlist)
		{
			const_iterator lbegin_ = inlist.begin(), lend_ = inlist.end();
			vector tmp(lbegin_, lend_);
			swap(tmp);
			return *this;
		}

		//析构函数
		~vector() {
			destroy_deallocate();
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		//---------------------------②访问元素---------------------------
		// []访问
		reference operator [](const size_t n) { //重载 []
			size_t size = end_ - begin_;
			if (n >= size) {
				std::cout << "超出索引范围" << std::endl;
			} 
			assert(n < size); // 表达式为false则退出运行
			return *(begin_ + n);
		}
		// at()访问
		reference at(size_t index) {
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
		reference front() {
			if (empty()) {
				std::cout << "vector为空,访问错误" << std::endl;
			}
			assert(!empty());
			return *begin_;
		}
		// back()访问
		reference back() {
			if (empty()) {
				std::cout << "vector为空,访问错误" << std::endl;
			}
			assert(!empty());
			return *(end_ - 1);
		}

		// data()
		iterator data() {
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
		// reserve(size_t n) 预留一定的内存空间，空间足够时无事发生，空间不足时扩容
		void reserve(size_t n) {
			if (capacity() < n) {
				if (n > max_size()) {
					std::cout << "请求容量超出限制" << std::endl;
					assert(n <= max_size());
				}// 若超出最大容量
				reallocate_construct(n);
			}
		}

		// shrink_to_fit()
		void shrink_to_fit() {
			if (end_ < capa_) {
				// 释放未填充的空间(error)
				/*
				myallocator<T>::destroy(end_, capa_); 
				myallocator<T>::deallocate(end_, capacity() - size()); 
				capa_ = end_;
				*/
				size_t n = size();
				reallocate_construct(n);
			}
		}

		//---------------------------④迭代器---------------------------
		// 正向迭代器
		iterator begin() {
			return begin_;
		}
		const_iterator begin() const {
			return begin_;
		}
		iterator end() {
			return end_;
		}
		const_iterator end() const {
			return end_;
		}
		const_iterator cbegin() {
			return begin_;
		}
		const_iterator cend() {
			return begin_;
		}

		// 反向迭代器(未完成)

		//---------------------------⑤修改---------------------------
		// assign 三种实现
		// assign(size_t n, const_reference value) 赋n个元素到vector中,并清除vector之前的内容
		void assign(size_t n, const_reference value) {
			if (n > capacity()) {
				// 创建一个新容器后交换
				vector tmp(n,value); 
				swap(tmp);
				/*  // 清除后重新分配空间，再填充
				clear();
				reallocate_construct(n);
				auto c = begin_;
				end_ = c + n;
				while (c != end_) {
					*c = value; c++;
				}
				*/
			}
			else if(n>size()) {
				iterator new_end_ = begin_ + n;
				for (auto i = begin_; i != end_; i++) {
					*i = value;
				}
				for (auto i = end_; i != new_end_; i++) {
					myallocator<T>::construct(i, value);
				}
				end_ = new_end_;
			}
			else {
				iterator new_end_ = begin_ + n;
				for (auto i = begin_; i != new_end_; i++) {
					*i = value;
				}
				erase(new_end_, end_);
				end_ = new_end_;
			}
		}
		// assign(const_iterator first_,const_iterator end_) 给定区间
		void assign(const_iterator first_, const_iterator last_) {
			if (first_ < last_) {
				size_t len = mycontainer::length<T>(first_, last_);
				if (len > capacity()) {
					vector tmp(first_,last_);
					swap(tmp);
				}
				else if (len > size()) {
					auto c = begin_;
					auto i = first_;
					while (c != end_) {
						*c = *i;
						c++; i++;
					}
					while (i != last_) {
						myallocator<T>::construct(c,*i);
						c++; i++;
					}
					end_ = begin_ + len;
				}
				else {
					auto c = begin_;
					for (auto i = first_; i != last_; i++) {
						*c = *i;
						c++;
					}
					end_ = erase(c, end_);
				}
			}
			else {
				std::cout << "assign区间错误" << std::endl;
				assert(first_ < last_);
			}
		}
		// assign(std::initializer_list<T> ilist) 序列
		void assign(std::initializer_list<T> ilist) {
			assign(ilist.begin(), ilist.end());
		}

		// emplace
		template <class... Args>
		iterator emplace(iterator position, Args&& ...args) {
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ < capa_) { //容量充足
					if (pos == end_) {
						myallocator<T>::construct(end_, mycontainer::forward<Args>(args)...);
						end_++;
					}
					else {
						myallocator<T>::construct(end_);
						mycontainer::move<T, T>(pos, end_, pos + 1);
						*pos = T(mycontainer::forward<Args>(args)...); //T()
						end_++;
					}
				}
				else { //容量不足
					size_t n = mycontainer::length(begin_, position);
					reallocate_construct(capacity() + 1);
					pos = emplace(begin_ + n, mycontainer::forward<Args>(args)...);
				}
				return pos;
			}
			else {
				std::cout << "emplace错误" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}

		// emplace_back 在尾部就地构造元素
		template <class... Args> //可变模板参数
		void emplace_back(Args&& ...args) {
			if (size() < capacity())
			{
				myallocator<T>::construct(end_, mycontainer::forward<Args>(args)...);
				++end_;
			}
			else {
				size_t cap = capacity();
				reallocate_construct(cap * 2 + 1); // 容量不足时扩大两倍
				emplace_back(mycontainer::forward<Args>(args)...);
			}
		}

		// push_back 两种
		void push_back(const_reference value) {
			if (size() < capacity()) {
				myallocator<T>::construct(end_, value);
				end_++;
			}
			else {
				size_t cap = capacity();
				reallocate_construct(cap * 2 + 1); // 容量不足时扩大两倍
				insert(end_, value);
			}
		}
		void push_back(T&& value) {
			emplace_back(mycontainer::move(value));
		}

		// pop_back
		void pop_back() {
			if (empty()) {
				std::cout << "容器为空，pop_back错误" << std::endl;
				assert(!empty());
				return;
			}
			myallocator<T>::destroy(end_ - 1);
			end_--;
		}

		// insert的三种实现
		// 在指定位置前插入一个元素value，返回指向这个元素的迭代器
		iterator insert(iterator position, const_reference value) {
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ < capa_) { // 容量充足
					if (position == end_) {
						myallocator<T>::construct(end_, value);
						end_++;
					}
					else {
						myallocator<T>::construct(end_);
						mycontainer::move<T, T>(pos, end_, pos + 1);
						*pos = value;
						end_++;
					}
				}
				else { // 容量不足
					size_t n = mycontainer::length(begin_, position);
					reallocate_construct(capacity() + 1);
					pos = insert(begin_ + n, value);
				}
				return pos;
			}
			else {
				std::cout << "插入位置错误" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}
		// 在指定位置前插入n个元素value
		void insert(iterator position, size_t n, const_reference value) {
			if (n == 0) {
				std::cout << "请插入大于1个元素" << std::endl;
				return ;
			}
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ + n <= capa_) { // 容量充足
					if (pos == end_) {
						auto c = end_;
						end_ = end_ + n;
						while (c != end_) {
							myallocator<T>::construct(c, value);
							c++;
						}
					}
					else {
						iterator new_end_ = end_ + n;
						auto c = end_;
						while (c != new_end_) {
							myallocator<T>::construct(c);
							c++;
						}
						mycontainer::move<T, T>(pos, end_, pos + n);
						for (auto i = pos; n > 0; i++,n--) {
							*i = value;
						}
						end_ = new_end_;
					}
				}
				else { // 容量不足
					size_t offset = mycontainer::length(begin_, position);
					size_t blank = mycontainer::length(end_, capa_);
					reallocate_construct(capacity() + n - blank);
					insert(begin_ + offset, n, value);
				}
			}
			else {
				std::cout << "插入位置错误" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}
		// 在指定位置前插入[first,last)的所有元素
		void insert(iterator position, iterator first, iterator last) {
			size_t n = mycontainer::length(first, last);
			if (n == 0) return;
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ + n <= capa_) { // 容量充足
					if (pos == end_) {
						mycontainer::move<T, T>(first, last, end_);
						end_ = end_ + n;
					}
					else {
						iterator new_end_ = end_ + n;
						mycontainer::move<T, T>(pos, end_, pos + n);
						auto c = first;
						for (auto i = pos; n > 0; i++, n--) {
							*i = *c; c++;
						}
						end_ = new_end_;
					}
				}
				else { // 容量不足
					size_t offset = mycontainer::length(begin_, position);
					size_t blank = mycontainer::length(end_, capa_);
					reallocate_construct(capacity() + n - blank);
					insert(begin_ + offset, first, last);
				}
			}
			else {
				std::cout << "插入位置错误" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}

		// erase的两种实现
		// erase(iterator position)  删除特定位置的元素，后面元素往前挪，析构最后一个位置，返回删除位置
		iterator erase(iterator position) {
			if (position >= begin_ && position < end_) {
				iterator pos = position;
				mycontainer::move<T, T>(pos + 1, end_, pos); //调整元素位置
				myallocator<T>::destroy(end_ - 1);
				end_--;
				return pos;
			}
			else {
				std::cout << "删除位置错误" << std::endl;
				assert(position >= begin_ && position < end_);
			}
		}
		// erase(iterator first,iterator last)  删除特定位置的元素,返回删除的初始位置
		// 使用const_iterator错误
		iterator erase(iterator first, iterator last) {
			if (first >= begin_ && last <= end_ && !(last < first)) {
				size_t n = first - begin();
				iterator tmp = mycontainer::move<T, T>(last, end_, first);
				myallocator<T>::destroy(tmp, end_);
				end_ = end_ - (last - first);
				return first;
			}
			else {
				std::cout << "删除区间错误" << std::endl;
				assert(first >= begin_ && last <= end_ && !(last < first));
			}
		}

		// clear() 移除所有元素，capacity不变
		void clear() {
			erase(begin_,end_);
		}

		// resize 没给value参数时默认填充0
		void resize(size_t n, const_reference value) {
			if (n < size()) { // n小于size，erase多余元素，capacity不变
				erase(begin_ + n, end_);
			}
			else { // n大于等于size，在后面insert不足的value
				insert(end_, n - size(), value);
			}
		}
		void resize(size_t n) {
			resize(n, 0);
		}

		// reverse 翻转vector
		void reverse() { 
			iterator first = begin_, last = end_ - 1;
			while (true)
			{
				if (first == last || first == last - 1)
					return;
				mycontainer::swap(*first, *last);
				first++; last--;
			}
		}

		//swap() 与另一个vector进行交换
		void swap(vector& rightvector) {
			if (this == &rightvector) return;
			mycontainer::swap(begin_, rightvector.begin_);
			mycontainer::swap(end_, rightvector.end_);
			mycontainer::swap(capa_, rightvector.capa_);
		}

	private:
		iterator begin_;
		iterator end_;
		iterator capa_;
		size_t initial_capacity = 16; // 未指定时/最小分配容量大小

	private:
		// 其它函数声明
		void destroy_deallocate(); //将原内存空间中的对象析构，释放原内存空间
		void reallocate_construct(size_t cap); // 重新分配cap大小的空间，将原空间中的内容拷贝过去，释放原空间
		
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

	
	template<class T>
	void vector<T>::destroy_deallocate() {
		myallocator<T>::destroy(begin_, end_); 
		myallocator<T>::deallocate(begin_, capacity()); 
	}

	template<class T>
	void vector<T>::reallocate_construct(size_t cap) {
		size_t n = size();
		iterator newbegin_ = myallocator<T>::allocate(cap);
		auto c = newbegin_;
		for (auto i = begin_; i != end_; i++) {
			myallocator<T>::construct(c, *i); //在新空间中构建对象
			c++;
		}
		destroy_deallocate();
		begin_ = newbegin_;
		end_ = newbegin_ + n;
		capa_ = newbegin_ + cap;
	}

} //namespace mycontainer

#endif //MYCONTAINER_VECTOR_H_

