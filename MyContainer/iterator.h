#ifndef MYCONTAINER_ITERATOR_H_
#define MYCONTAINER_ITERATOR_H_

namespace mycontainer {
	template<class T>
	size_t length(T* first,T* last) {
		return static_cast<size_t> (last - first);
	} // 返回两个迭代器之间的距离

	template<class InputIterator,class OutputIterator>
	InputIterator* move(InputIterator* first, InputIterator* last, OutputIterator* result) {
		size_t n = last - first;
		if (n != 0) {
			// std::memmove(dest,src,count)函数：将src的count长度内容复制到dest
			std::memmove(result, first, n * sizeof(OutputIterator));
		}
		return result + n;
	}// 将first到last指定的序列移到result作为开始的位置，返回result+n位置



}







#endif //MYCONTAINER_ITERATOR_H_