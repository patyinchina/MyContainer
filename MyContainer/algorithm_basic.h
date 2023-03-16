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


} //namespace mycontainer


#endif //MYCONTAINER_ALGORITHM_BASIC_H_
