// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include <string>
using namespace std;

#include <boost/function.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/any.hpp>
using namespace boost;

#include <boost/system/error_code.hpp>
using namespace boost::system;

#include <boost/asio.hpp>
using namespace boost::asio;

#include "log.h"
