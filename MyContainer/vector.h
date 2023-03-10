#ifndef MYCONTAINER_VECTOR_H_
#define MYCONTAINER_VECTOR_H_

#include<assert.h>
#include "myallocator.h"
#include "construct.h"

namespace mycontainer {

	template <class T>
	class vector{
	public:

		// 构造、复制、移动、析构函数
		vector() {
			begin = myallocator<T>::allocate(); //分配内存
			end = begin;
		}

		explicit vector(size_t n) {
			begin = myallocator<T>::allocate(n); //分配内存
			end = begin + n;
			auto c = begin;
			while (n > 0) {
				*c = 0;
				c++;
				n--;
			}
		}

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

		T& operator [](const size_t n) {
			size_t size=static_cast<T>(end - begin);
			if (n >= size) assert(n >= size); // 待研究assert函数 !!
			return *(begin + n);

		}

	private:
		T* begin;
		T* end;
		






	};


	
	







}





#endif //MYCONTAINER_VECTOR_H_

