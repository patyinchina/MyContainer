#ifndef MYCONTAINER_MYALLOCATOR_H_
#define MYCONTAINER_MYALLOCATOR_H_

//myallocator 负责处理内存的分配和释放
#include "construct.h"

namespace mycontainer {
	template<class T>
	class myallocator {
	public:

		typedef T value_type;
		typedef T* pointer;

		//分配内存
		static T* allocate();  //static关键字作用：所有对象共享，无需实例化。需在类外进行初始化
		static T* allocate(size_t n); 

		//释放内存
		static void deallocate(T* p);
		static void deallocate(T* p, size_t n);
	
		//在已分配的内存空间上构造对象
		static void construct(T* p);
		static void construct(T* p, const T& value);
		//static void construct(T* p, T&& value); (未完成)



		//析构对象
		static void destroy(T* p);
		static void destroy(T* first, T* last);

	};

	//myallocator<T>::allocate()定义
	template<class T>
	T* myallocator<T>::allocate() {  //注意在类外声明时无需再加 static !!
		void* newarea = ::operator new(sizeof(T));
		return static_cast<T*>(newarea);
	}

	//myallocator<T>::allocate(size_t n)定义
	template<class T>
	T* myallocator<T>::allocate(size_t n) {  //注意在类外声明时无需再加 static !!
		if (!n) return nullptr;
		void* newarea = ::operator new(sizeof(T) * n);
		return static_cast<T*>(newarea);
	}

	//myallocator<T>::deallocate(T* p)定义
	template<class T>
	void myallocator<T>::deallocate(T* p) {  //注意在类外声明时无需再加 static !!
		if (p == nullptr) return;
		::operator delete(p); //释放指向的内存空间
	}

	//myallocator<T>::deallocate(T* p)定义
	template<class T>
	void myallocator<T>::deallocate(T* p,size_t n) {  //注意在类外声明时无需再加 static !!
		if (p == nullptr) return;
		::operator delete(p); //释放指向的内存空间
	}

	//myallocator<T>::construct(T* p)定义
	template<class T>
	void myallocator<T>::construct(T* p) {
		mycontainer::construct(p);
	}

	//myallocator<T>::construct(T* p, const T& value)定义
	template<class T>
	void myallocator<T>::construct(T* p, const T& value) {
		mycontainer::construct(p, value);
	}

	//myallocator<T>::deconstruct(T* p)定义
	template<class T>
	void myallocator<T>::destroy(T* p) {
		mycontainer::destroy(p);
	}

	//myallocator<T>::deconstruct(T* first, T* last)定义
	template<class T>
	void myallocator<T>::destroy(T* first_, T* last_) {
		mycontainer::destroy(first_, last_);
	}


}//namespace mycontainer




#endif //MYCONTAINER_MYALLOCATOR_H_