#include "StdAfx.h"
#include "datagram_session.h"
using namespace fastnet::udp;

datagram_session::datagram_session( socket_ptr socket, endpoint local, endpoint remote )
: abstract_session( socket, local, remote )
{
}

datagram_session::~datagram_session(void)
{
}

void fastnet::udp::datagram_session::write( boost::any object, boost::function<void()> handler )
{
	// TODO
	try {
		asio::mutable_buffers_1 * data = any_cast<asio::mutable_buffers_1 *>( object );

		//boost::asio::async_write( *socket, data, boost::asio::transfer_all(),
		socket->async_send( *data, 
			boost::bind(&datagram_session::handle_write_complete, this, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred, data ));
	} catch( bad_cast & ) {
		LOG( "write type is not asio::mutable_buffers_1 *" );
	}
}