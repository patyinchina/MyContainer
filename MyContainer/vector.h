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

		// �ٹ��졢���ơ��ƶ�����������
		// ��ָ��
		vector() {
			begin = myallocator<T>::allocate(); //�����ڴ�
			end = begin;
		}
		// ָ����С����ʼֵĬ��Ϊ0
		explicit vector(size_t n) { //explicit�������ڵĵ��������캯��ǰ�棬��ֹ�๹�캯������ʽ�Զ�ת��
			begin = myallocator<T>::allocate(n); //�����ڴ�
			end = begin + n;
			auto c = begin;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}
		//ָ����С�ͳ�ʼֵ
		vector(size_t n, const T& value) { 
			begin = myallocator<T>::allocate(n); //�����ڴ�
			end = begin + n;
			auto c = begin;
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
			begin = myallocator<T>::allocate(len);
			end = begin + len;
			auto c = begin;
			for (auto i = first; i != last; i++) {
				*c = *i;
				c++;
			}
		}
		//ͨ������vector����
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
		//�ƶ�����(δ���)


		//���й���(δ���)


		//��ֵ����(δ���)


		//��������(δ���)


		// �ڷ���Ԫ��
		// []����
		T& operator [](const size_t n) { //���� []
			size_t size=static_cast<T>(end - begin);
			if (n >= size) {
				std::cout << "����������Χ" << std::endl;
			} 
			assert(n < size); // ���ʽΪfalse���˳�����
			return *(begin + n);
		}
		// at()����(δ���)
		T& at(size_t index) {
			
		}
		// front()����
		T& front() {
			return *begin;
		}
		// back()����(δ���)


		// data()����(δ���)



	private:
		T* begin;
		T* end;
	

	};



}


#endif //MYCONTAINER_VECTOR_H_

