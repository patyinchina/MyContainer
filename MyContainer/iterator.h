#ifndef MYCONTAINER_ITERATOR_H_
#define MYCONTAINER_ITERATOR_H_

// ʵ�ֵ������㷨
// length����������������֮��ľ���
// move����first��lastָ���������Ƶ�result��Ϊ��ʼ��λ�ã�����result+nλ��

namespace mycontainer {
	template<class T>
	size_t length(T* first,T* last) {
		return static_cast<size_t> (last - first);
	} // ��������������֮��ľ���

	template<class T>
	size_t length(const T* first, const T* last) {
		return static_cast<size_t> (last - first);
	} // ��������const������֮��ľ���

	template<class InputIterator,class OutputIterator>
	InputIterator* move(InputIterator* first, InputIterator* last, OutputIterator* result) {
		size_t n = last - first;
		if (n != 0) {
			// std::memmove(dest,src,count)��������src��count�������ݸ��Ƶ�dest
			std::memmove(result, first, n * sizeof(OutputIterator));
		}
		return result + n;
	}// ��first��lastָ���������Ƶ�result��Ϊ��ʼ��λ�ã�����result+nλ��

}

#endif //MYCONTAINER_ITERATOR_H_