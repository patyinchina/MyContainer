#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

// ʵ��vector��Ļ������ܣ��������졢���ơ��ƶ�����������������Ԫ�أ����������������޸�Ԫ�ع���
// ����Ԫ�أ�����[]��at��front��back��data
// ������empty��size��maxsize��capacity��reserve��shrink_to_fit
// �����򣩵�������begin��end��cbegin��cend
// �޸ģ�assign��emplace��emplace_back��push_back��pop_back��insert��erase��clear��resize��reverse��swap

// �����쳣����
// ��δ��ɷ��������

// assert����debug����

#include<assert.h> // debugʱ��������ͷ�ļ�
#include<iostream>
#include <initializer_list>
#include "algorithm_basic.h"
#include "iterator.h"
#include "myallocator.h"

namespace mycontainer {

	

	template <class T>
	class vector{
	public:

		// vector��(Ƕ��)���Ͷ���
		//typedef mycontainer::myallocator<T>              allocator_type;
		//typedef typename allocator_type::value_type      value_type; // typename ���߱�������һ�����ͣ����Ǿ�̬���ݳ�Ա���Ա����
		
		// vector���Ͷ���
		typedef T  value_type;   
		typedef T* iterator;
		typedef T& reference;
		typedef const T* const_iterator;
		typedef const T& const_reference;

		//---------------------------�ٹ��졢���ơ��ƶ�����������---------------------------
		// ��ָ��
		vector() {
			const size_t cap = initial_capacity; // Ԥ���ռ�
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// ָ����С����ʼֵĬ��Ϊ0
		explicit vector(size_t n) { //explicit�������ڵĵ��������캯��ǰ�棬��ֹ�๹�캯������ʽ�Զ�ת������Ҫ���� =
			const size_t cap = mycontainer::max<size_t>(n, initial_capacity);
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (c != end_) {
				myallocator<T>::construct(c, 0);
				c++;
			}
		}
		//ָ����С�ͳ�ʼֵ
		vector(size_t n, const_reference value) {
			const size_t cap = mycontainer::max<size_t>(n, initial_capacity);
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (c != end_) {
				myallocator<T>::construct(c, value);
				c++;
			}
		}
		//ͨ���������鹹��
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
		//ͨ������vector���� (���)
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
		// �ƶ����� (������һ����ֵ���߽���ֵ������,ֱ�Ӽ̳���Դ)
		vector(vector&& copyvector) noexcept{
			begin_ = copyvector.begin_;
			end_ = copyvector.end_;
			capa_ = copyvector.capa_;
			copyvector.begin_ = nullptr;
			copyvector.end_ = nullptr;
			copyvector.capa_ = nullptr;
		}

		//���й���
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

		//���Ƹ�ֵ���� (���)
		vector& operator=(const vector& assignvector);

		//�ƶ���ֵ
		vector& operator=(vector&& assignvector) noexcept;

		//���и�ֵ
		vector& operator=(std::initializer_list<T> inlist)
		{
			const_iterator lbegin_ = inlist.begin(), lend_ = inlist.end();
			vector tmp(lbegin_, lend_);
			swap(tmp);
			return *this;
		}

		//��������
		~vector() {
			destroy_deallocate();
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		//---------------------------�ڷ���Ԫ��---------------------------
		// []����
		reference operator [](const size_t n) { //���� []
			size_t size = end_ - begin_;
			if (n >= size) {
				std::cout << "����������Χ" << std::endl;
			} 
			assert(n < size); // ���ʽΪfalse���˳�����
			return *(begin_ + n);
		}
		// at()����
		reference at(size_t index) {
			size_t size = end_ - begin_;
			if (index >= size) {
				std::cout << "����������Χ" << std::endl;
			}
			assert(index < size);
			auto c = begin_;
			while (index > 0) {
				c++; index--;
			}
			return *c;
		}
		// front()����
		reference front() {
			if (empty()) {
				std::cout << "vectorΪ��,���ʴ���" << std::endl;
			}
			assert(!empty());
			return *begin_;
		}
		// back()����
		reference back() {
			if (empty()) {
				std::cout << "vectorΪ��,���ʴ���" << std::endl;
			}
			assert(!empty());
			return *(end_ - 1);
		}

		// data()
		iterator data() {
			if (empty()) {
				std::cout << "vectorΪ��,���ʴ���" << std::endl;
			}
			assert(!empty());
			return begin_;
		}

		//---------------------------������-----------------------------
		// empty() �п�
		bool empty() const{
			return begin_ == end_;
		}
		// size() ����vector��С
		size_t size() const{
			size_t size = end_ - begin_;
			return size;
		}
		// max_size() ����vector�����ܴ�С
		size_t max_size() const{
			return static_cast<size_t>(-1) / sizeof(T); //ǿ������ת��
		}
		// capacity() �����ܴ洢���ݵĸ���
		size_t capacity() const{
			size_t cap = capa_ - begin_;
			return cap;
		}
		// reserve(size_t n) Ԥ��һ�����ڴ�ռ䣬�ռ��㹻ʱ���·������ռ䲻��ʱ����
		void reserve(size_t n) {
			if (capacity() < n) {
				if (n > max_size()) {
					std::cout << "����������������" << std::endl;
					assert(n <= max_size());
				}// �������������
				reallocate_construct(n);
			}
		}

		// shrink_to_fit()
		void shrink_to_fit() {
			if (end_ < capa_) {
				// �ͷ�δ���Ŀռ�(error)
				/*
				myallocator<T>::destroy(end_, capa_); 
				myallocator<T>::deallocate(end_, capacity() - size()); 
				capa_ = end_;
				*/
				size_t n = size();
				reallocate_construct(n);
			}
		}

		//---------------------------�ܵ�����---------------------------
		// ���������
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

		// ���������(δ���)

		//---------------------------���޸�---------------------------
		// assign ����ʵ��
		// assign(size_t n, const_reference value) ��n��Ԫ�ص�vector��,�����vector֮ǰ������
		void assign(size_t n, const_reference value) {
			if (n > capacity()) {
				// ����һ���������󽻻�
				vector tmp(n,value); 
				swap(tmp);
				/*  // ��������·���ռ䣬�����
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
		// assign(const_iterator first_,const_iterator end_) ��������
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
				std::cout << "assign�������" << std::endl;
				assert(first_ < last_);
			}
		}
		// assign(std::initializer_list<T> ilist) ����
		void assign(std::initializer_list<T> ilist) {
			assign(ilist.begin(), ilist.end());
		}

		// emplace
		template <class... Args>
		iterator emplace(iterator position, Args&& ...args) {
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ < capa_) { //��������
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
				else { //��������
					size_t n = mycontainer::length(begin_, position);
					reallocate_construct(capacity() + 1);
					pos = emplace(begin_ + n, mycontainer::forward<Args>(args)...);
				}
				return pos;
			}
			else {
				std::cout << "emplace����" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}

		// emplace_back ��β���͵ع���Ԫ��
		template <class... Args> //�ɱ�ģ�����
		void emplace_back(Args&& ...args) {
			if (size() < capacity())
			{
				myallocator<T>::construct(end_, mycontainer::forward<Args>(args)...);
				++end_;
			}
			else {
				size_t cap = capacity();
				reallocate_construct(cap * 2 + 1); // ��������ʱ��������
				emplace_back(mycontainer::forward<Args>(args)...);
			}
		}

		// push_back ����
		void push_back(const_reference value) {
			if (size() < capacity()) {
				myallocator<T>::construct(end_, value);
				end_++;
			}
			else {
				size_t cap = capacity();
				reallocate_construct(cap * 2 + 1); // ��������ʱ��������
				insert(end_, value);
			}
		}
		void push_back(T&& value) {
			emplace_back(mycontainer::move(value));
		}

		// pop_back
		void pop_back() {
			if (empty()) {
				std::cout << "����Ϊ�գ�pop_back����" << std::endl;
				assert(!empty());
				return;
			}
			myallocator<T>::destroy(end_ - 1);
			end_--;
		}

		// insert������ʵ��
		// ��ָ��λ��ǰ����һ��Ԫ��value������ָ�����Ԫ�صĵ�����
		iterator insert(iterator position, const_reference value) {
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ < capa_) { // ��������
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
				else { // ��������
					size_t n = mycontainer::length(begin_, position);
					reallocate_construct(capacity() + 1);
					pos = insert(begin_ + n, value);
				}
				return pos;
			}
			else {
				std::cout << "����λ�ô���" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}
		// ��ָ��λ��ǰ����n��Ԫ��value
		void insert(iterator position, size_t n, const_reference value) {
			if (n == 0) {
				std::cout << "��������1��Ԫ��" << std::endl;
				return ;
			}
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ + n <= capa_) { // ��������
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
				else { // ��������
					size_t offset = mycontainer::length(begin_, position);
					size_t blank = mycontainer::length(end_, capa_);
					reallocate_construct(capacity() + n - blank);
					insert(begin_ + offset, n, value);
				}
			}
			else {
				std::cout << "����λ�ô���" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}
		// ��ָ��λ��ǰ����[first,last)������Ԫ��
		void insert(iterator position, iterator first, iterator last) {
			size_t n = mycontainer::length(first, last);
			if (n == 0) return;
			if (position >= begin_ && position <= end_) {
				iterator pos = position;
				if (end_ + n <= capa_) { // ��������
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
				else { // ��������
					size_t offset = mycontainer::length(begin_, position);
					size_t blank = mycontainer::length(end_, capa_);
					reallocate_construct(capacity() + n - blank);
					insert(begin_ + offset, first, last);
				}
			}
			else {
				std::cout << "����λ�ô���" << std::endl;
				assert(position >= begin_ && position <= end_);
			}
		}

		// erase������ʵ��
		// erase(iterator position)  ɾ���ض�λ�õ�Ԫ�أ�����Ԫ����ǰŲ���������һ��λ�ã�����ɾ��λ��
		iterator erase(iterator position) {
			if (position >= begin_ && position < end_) {
				iterator pos = position;
				mycontainer::move<T, T>(pos + 1, end_, pos); //����Ԫ��λ��
				myallocator<T>::destroy(end_ - 1);
				end_--;
				return pos;
			}
			else {
				std::cout << "ɾ��λ�ô���" << std::endl;
				assert(position >= begin_ && position < end_);
			}
		}
		// erase(iterator first,iterator last)  ɾ���ض�λ�õ�Ԫ��,����ɾ���ĳ�ʼλ��
		// ʹ��const_iterator����
		iterator erase(iterator first, iterator last) {
			if (first >= begin_ && last <= end_ && !(last < first)) {
				size_t n = first - begin();
				iterator tmp = mycontainer::move<T, T>(last, end_, first);
				myallocator<T>::destroy(tmp, end_);
				end_ = end_ - (last - first);
				return first;
			}
			else {
				std::cout << "ɾ���������" << std::endl;
				assert(first >= begin_ && last <= end_ && !(last < first));
			}
		}

		// clear() �Ƴ�����Ԫ�أ�capacity����
		void clear() {
			erase(begin_,end_);
		}

		// resize û��value����ʱĬ�����0
		void resize(size_t n, const_reference value) {
			if (n < size()) { // nС��size��erase����Ԫ�أ�capacity����
				erase(begin_ + n, end_);
			}
			else { // n���ڵ���size���ں���insert�����value
				insert(end_, n - size(), value);
			}
		}
		void resize(size_t n) {
			resize(n, 0);
		}

		// reverse ��תvector
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

		//swap() ����һ��vector���н���
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
		size_t initial_capacity = 16; // δָ��ʱ/��С����������С

	private:
		// ������������
		void destroy_deallocate(); //��ԭ�ڴ�ռ��еĶ����������ͷ�ԭ�ڴ�ռ�
		void reallocate_construct(size_t cap); // ���·���cap��С�Ŀռ䣬��ԭ�ռ��е����ݿ�����ȥ���ͷ�ԭ�ռ�
		
	};

	//--------------------------��������---------------------------
	//���Ƹ�ֵ
	template<class T>
	vector<T>& vector<T>::operator=(const vector& assignvector) {
		//�����µĿռ����
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
		//�¹���tmp�󽻻���δ��ɣ�
	}

	//�ƶ���ֵ
	template<class T>
	vector<T>& vector<T>::operator=(vector&& assignvector) noexcept{
		//�ͷ�ԭ�ռ估���������̳���Դ
		myallocator<T>::destroy(begin_, end_); //��������
		myallocator<T>::deallocate(begin_, capa_ - begin_); //�ͷſռ�
		begin_ = assignvector.begin_;
		end_ = assignvector.end_;
		capa_ = assignvector.capa_;
		//�����ÿղ�������Ҫ�У���
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
			myallocator<T>::construct(c, *i); //���¿ռ��й�������
			c++;
		}
		destroy_deallocate();
		begin_ = newbegin_;
		end_ = newbegin_ + n;
		capa_ = newbegin_ + cap;
	}

} //namespace mycontainer

#endif //MYCONTAINER_VECTOR_H_

