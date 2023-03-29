#ifndef MYCONTAINER_ALGORITHM_BASIC_H_
#define MYCONTAINER_ALGORITHM_BASIC_H_

// 基本算法 forward，move，swap

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

// forward
// 用于实现完美转发，左值引用返回左值，右值引用返回右值
template <class T>
T&& forward(typename std::remove_reference<T>::type& arg)
{
	return static_cast<T&&>(arg);
}

// move
// 强制转换为右值
template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg) 
{
	return static_cast<typename std::remove_reference<T>::type&&>(arg);
}
// std::remove_reference<T>::type 作用为移除引用

// swap 
// 通过移动语义实现交换，避免资源的释放与申请
template<class T>
void swap(T& leftele, T& rightele)
{
	auto tmp(mycontainer::move(leftele));
	leftele = mycontainer::move(rightele);
	rightele = mycontainer::move(tmp);
}

} //namespace mycontainer

#endif //MYCONTAINER_ALGORITHM_BASIC_H_
