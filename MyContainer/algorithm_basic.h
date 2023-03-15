#ifndef MYTINYSTL_ALGORITHM_BASIC_H_
#define MYTINYSTL_ALGORITHM_BASIC_H_

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



}




#endif
