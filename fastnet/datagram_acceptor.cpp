#include "StdAfx.h"
#include "datagram_acceptor.h"
#include "session_accept_handler.h"
using namespace fastnet;
using namespace fastnet::udp;

datagram_acceptor::datagram_acceptor(void)
{
}

datagram_acceptor::~datagram_acceptor(void)
{
}

void fastnet::udp::datagram_acceptor::handle_data( size_t bytes_transferred, ip::udp::endpoint remote_endpoint )
{
	io_buffer data( buffer_.data(), bytes_transferred );
	datagram_session session( socket_, socket_->local_endpoint(), remote_endpoint_ );
	any in = &buffer_;

	handler->session_accepted( *this, session );
	session.get_handler()->message_received( session, in );

	//if( codec ) {
	//	list<any> objects = codec->decode( session, in );
	//	BOOST_FOREACH( any object, objects ) {
	//		handler->message_received( session, object );
	//	}
	//}
}