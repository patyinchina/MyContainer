#ifndef MYCONTAINER_CONSTRUCT_H_
#define MYCONTAINER_CONSTRUCT_H_
// construct 负责构造和析构对象

#include<new>

namespace mycontainer {

	//在已分配的内存空间上构造对象
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

	//析构对象
	//未加入 std::is_trivially_destructible<Ty>{}

	//析构对象-one
	template <class Ty>
	void destroy_one(Ty* p)
	{
		if (p != nullptr)
		{
			p->~Ty();
		}
	}
	//析构对象
	template <class Ty>
	void destroy(Ty* p)
	{
		destroy_one(p);
	}

	//析构对象-cat
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