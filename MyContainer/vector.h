#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include "myallocator.h"
#include "construct.h"

namespace mycontainer {

	template <class T>
	class vector{
	public:

		// ���졢���ơ��ƶ�����������
		vector() {
			begin = myallocator<T>::allocate(); //�����ڴ�
			end = begin;
		}

		explicit vector(size_t n) {
			begin = myallocator<T>::allocate(n); //�����ڴ�
			end = begin + n;
			auto c = begin;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}

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

		T& operator [](const size_t n) {
			size_t size=static_cast<T>(end - begin);
			if (n >= size) assert(n >= size); // ���о�assert���� !!
			return *(begin + n);

		}

	private:
		T* begin;
		T* end;
		






	};


	
	







}





#endif //MYCONTAINER_VECTOR_H_

