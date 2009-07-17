#include "StdAfx.h"
#include "abstract_session.h"
using namespace fastnet;

abstract_session::abstract_session( udp::socket_ptr socket, udp::endpoint local, udp::endpoint remote )
: socket(socket)
, local_endpoint(local)
, remote_endpoint(remote)
{
}

abstract_session::~abstract_session(void)
{
}
