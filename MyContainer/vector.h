#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include<iostream>
#include "algorithm_basic.h"
#include "myallocator.h"
//#include "construct.h" (δ���)
using std::cout;
using std::endl;

namespace mycontainer {

	template <class T>
	class vector{
	public:

		// �ٹ��졢���ơ��ƶ�����������
		// ��ָ��
		vector() {
			const size_t cap = 8; // Ԥ���ռ�
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_;
			capa_ = begin_ + cap;
		}
		// ָ����С����ʼֵĬ��Ϊ0
		explicit vector(size_t n) { //explicit�������ڵĵ��������캯��ǰ�棬��ֹ�๹�캯������ʽ�Զ�ת��
			const size_t cap = mycontainer::max<size_t>(n, 8);
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}
		//ָ����С�ͳ�ʼֵ
		vector(size_t n, const T& value) { 
			const size_t cap = mycontainer::max<size_t>(n, 8);
			begin_ = myallocator<T>::allocate(cap); //�����ڴ�
			end_ = begin_ + n;
			capa_ = begin_ + cap;
			auto c = begin_;
			while (n > 0) {
				*c = value;
				c++;
				n--;
			}
		}
		//ͨ���������鹹��
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
		//ͨ������vector����
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
		//�ƶ�����(δ���)


		//���й���(δ���)


		//��ֵ����(δ���)


		//��������
		~vector() {
			myallocator<T>::deallocate(begin_, capa_ - begin_);
			begin_ = nullptr;
			end_ = nullptr;
			capa_ = nullptr;
		}

		// �ڷ���Ԫ��
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

		// ������
		// �п�
		bool empty() {
			return begin_ == end_;
		}
		// ����vector��С
		size_t size() {
			size_t size = end_ - begin_;
			return size;
		}
		// ����vector�����ܴ�С
		size_t max_size() {
			return static_cast<size_t>(-1) / sizeof(T); //ǿ������ת��
		}
		// �����ܴ洢���ݵĸ���
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

