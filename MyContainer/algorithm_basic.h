#ifndef MYCONTAINER_ALGORITHM_BASIC_H_
#define MYCONTAINER_ALGORITHM_BASIC_H_

#include <cstring>

namespace mycontainer {

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

template<class T>
const T& max(const T& leftele, const T& rightele) {
	return leftele > rightele ? leftele : rightele;
}

template<class T>
const T& min(const T& leftele, const T& rightele) {
	return leftele < rightele ? leftele : rightele;
}

// move
// ǿ��ת��Ϊ��ֵ
template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg) 
{
	return static_cast<typename std::remove_reference<T>::type&&>(arg);
}
// std::remove_reference<T>::type ����Ϊ�Ƴ�����


// swap 
// ͨ���ƶ�����ʵ�ֽ�����������Դ���ͷ�������
template<class T>
void swap(T& leftele, T& rightele)
{
	auto tmp(mycontainer::move(leftele));
	leftele = mycontainer::move(rightele);
	rightele = mycontainer::move(tmp);
}


} //namespace mycontainer


#endif //MYCONTAINER_ALGORITHM_BASIC_H_
