#pragma once
#include <iostream>

namespace fastnet {

#ifdef ENABLE_LOG
#define LOG(msg) { \
	::std::cout << msg << ::std::endl;	\
	}
#else
#define LOG(msg)
#endif

}
