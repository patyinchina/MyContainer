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

		//---------------------------�ٹ��졢���ơ��ƶ�����������---------------------------
		// ��ָ��
		vector() {
			const size_t cap = initial_capacity; // Ԥ���ռ�
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// ָ����С����ʼֵĬ��Ϊ0
		explicit vector(size_t n) { //explicit�������ڵĵ��������캯��ǰ�棬��ֹ�๹�캯������ʽ�Զ�ת��
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
		vector(size_t n, const T& value) { 
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
		//ͨ������vector����
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

		//���й���(δ���)


		//���Ƹ�ֵ���� (���)
		vector& operator=(const vector& assignvector);

		//�ƶ���ֵ
		vector& operator=(vector&& assignvector) noexcept;

		//���и�ֵ��δ��ɣ�


		//��������
		~vector() {
			myallocator<T>::destroy(begin_, end_); //��������
			myallocator<T>::deallocate(begin_, capa_ - begin_); //�ͷſռ�
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		//---------------------------�ڷ���Ԫ��---------------------------
		// []����
		T& operator [](const size_t n) { //���� []
			size_t size = end_ - begin_;
			if (n >= size) {
				std::cout << "����������Χ" << std::endl;
			} 
			assert(n < size); // ���ʽΪfalse���˳�����
			return *(begin_ + n);
		}
		// at()����
		T& at(size_t index) {
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
		T& front() {
			if (empty()) {
				std::cout << "vectorΪ��,���ʴ���" << std::endl;
			}
			assert(!empty());
			return *begin_;
		}
		// back()����
		T& back() {
			if (empty()) {
				std::cout << "vectorΪ��,���ʴ���" << std::endl;
			}
			assert(!empty());
			return *(end_ - 1);
		}

		// data()
		T* data() {
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
		// reserve(size_t n) Ԥ��һ�����ڴ�ռ䣨δ��ɣ�

		// shrink_to_fit()��δ��ɣ�


		//---------------------------��---------------------------

	private:
		T* begin_;
		T* end_;
		T* capa_;
		size_t initial_capacity = 8; // δָ��ʱ/��С����������С

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



} //namespace mycontainer


#endif //MYCONTAINER_VECTOR_H_

