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

#include <boost/function.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/foreach.hpp>
using namespace boost;

#include <boost/system/error_code.hpp>
using namespace boost::system;

#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;


#include <fastnet/fastnet.h>
using namespace fastnet;
using namespace fastnet::udp;

#define LOG(msg)