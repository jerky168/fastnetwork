#include "StdAfx.h"
#include "udp_session.h"
using namespace fastnet::udp;

udp_session::udp_session(shared_ptr<ip::udp::socket> socket, ip::udp::endpoint local, ip::udp::endpoint remote)
: socket_(socket)
, local_endpoint_(local)
, remote_endpoint_(remote)
{
}

udp_session::~udp_session(void)
{
	LOG("udp session destroyed.");
}

void udp_session::handle_write_complete( any message, const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/ )
{
	this->handler_->message_sent( shared_from_this(), message );
}