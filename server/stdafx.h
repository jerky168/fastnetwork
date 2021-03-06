// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <iostream>
#include <string>
using namespace std;

#include <boost/any.hpp>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost;

#include <boost/asio.hpp>
using namespace boost::asio;

#include <fastnetwork/fastnetwork.h>
using namespace fastnetwork;

#define ENABLE_LOG
#include "log.h"
