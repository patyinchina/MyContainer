#ifndef MYCONTAINER_ITERATOR_H_
#define MYCONTAINER_ITERATOR_H_

namespace mycontainer {
	template<class T>
	size_t length(T* first,T* last) {
		return static_cast<size_t> (last - first);
	}





}







#endif //MYCONTAINER_ITERATOR_H_