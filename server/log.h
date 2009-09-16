#pragma once
#include <iostream>

namespace fastnetwork {

#ifdef ENABLE_LOG
#define LOG(msg) { \
	::std::cout << msg << ::std::endl;	\
	}
#else
#define LOG(msg)
#endif

}
