#ifndef MYCONTAINER_MYALLOCATOR_H_
#define MYCONTAINER_MYALLOCATOR_H_

//myallocator 负责处理内存的分配和释放

namespace mycontainer {
	template<class T>
	class myallocator {
	public:
		//分配内存
		static T* allocate();  //static关键字作用：所有对象共享，无需实例化。需在类外进行初始化
		static T* allocate(size_t n); 

		//释放内存
		static void deallocate(T* p);
		static void deallocate(T* p, size_t n);
	

	


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

}











#endif //MYCONTAINER_MYALLOCATOR_H_