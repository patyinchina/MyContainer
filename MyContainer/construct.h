#ifndef MYCONTAINER_CONSTRUCT_H_
#define MYCONTAINER_CONSTRUCT_H_

// construct ���ѷ�����ڴ�ռ��Ϲ������
// destroy ��������

#include<new>

namespace mycontainer {

	//���ѷ�����ڴ�ռ��Ϲ������
	template <class Ty>
	void construct(Ty* p)
	{
		::new ((void*)p) Ty();
	}
	
	template <class Ty1,class Ty2>
	void construct(Ty1* p,const Ty2& value)
	{
		::new ((void*)p) Ty1(value);
	}

	template <class Ty, class... Args>
	void construct(Ty* p, Args&&... args)
	{
		::new ((void*)p) Ty(mycontainer::forward<Args>(args)...);
	}

	//��������
	//δ���� std::is_trivially_destructible<Ty>{}

	//��������-one
	template <class Ty>
	void destroy_one(Ty* p)
	{
		if (p != nullptr)
		{
			p->~Ty();
		}
	}
	//��������
	template <class Ty>
	void destroy(Ty* p)
	{
		destroy_one(p);
	}

	//��������-cat
	template <class Ty>
	void destroy_cat(Ty* first, Ty* last)
	{
		while (first != last) {
			destroy(first);
			first++;
		}
	}
	template <class Ty>
	void destroy(Ty* first, Ty* last)
	{
		destroy_cat(first,last);
	}

} //namespace mycontainer

#endif //MYCONTAINER_CONSTRUCT_H_