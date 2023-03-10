#ifndef MYCONTAINER_MYALLOCATOR_H_
#define MYCONTAINER_MYALLOCATOR_H_

//myallocator �������ڴ�ķ�����ͷ�

namespace mycontainer {
	template<class T>
	class myallocator {
	public:
		//�����ڴ�
		static T* allocate();  //static�ؼ������ã����ж���������ʵ����������������г�ʼ��
		static T* allocate(size_t n); 

		//�ͷ��ڴ�
		static void deallocate(T* p);
		static void deallocate(T* p, size_t n);
	

	


	};

	//myallocator<T>::allocate()����
	template<class T>
	T* myallocator<T>::allocate() {  //ע������������ʱ�����ټ� static !!
		void* newarea = ::operator new(sizeof(T));
		return static_cast<T*>(newarea);
	}

	//myallocator<T>::allocate(size_t n)����
	template<class T>
	T* myallocator<T>::allocate(size_t n) {  //ע������������ʱ�����ټ� static !!
		if (!n) return nullptr;
		void* newarea = ::operator new(sizeof(T) * n);
		return static_cast<T*>(newarea);
	}

	//myallocator<T>::deallocate(T* p)����
	template<class T>
	void myallocator<T>::deallocate(T* p) {  //ע������������ʱ�����ټ� static !!
		if (p == nullptr) return;
		::operator delete(p); //�ͷ�ָ����ڴ�ռ�
	}

	//myallocator<T>::deallocate(T* p)����
	template<class T>
	void myallocator<T>::deallocate(T* p,size_t n) {  //ע������������ʱ�����ټ� static !!
		if (p == nullptr) return;
		::operator delete(p); //�ͷ�ָ����ڴ�ռ�
	}

}











#endif //MYCONTAINER_MYALLOCATOR_H_