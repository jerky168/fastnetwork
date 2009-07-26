#include "StdAfx.h"
#include "udp_session.h"
#include "default_filter_chain.h"
#include "io_buffer.h"
using namespace std;
using namespace boost;
using namespace fastnet::udp;

udp_session::udp_session(shared_ptr<ip::udp::socket> socket, ip::udp::endpoint local, ip::udp::endpoint remote)
: socket_(socket)
, local_endpoint_(local)
, remote_endpoint_(remote)
, filter_chain_( new default_filter_chain() )
{
}

udp_session::~udp_session(void)
{
	LOG("udp session destroyed.");
}

void udp_session::handle_write_complete( any message, const system::error_code& /*error*/, size_t /*bytes_transferred*/ )
{
	this->handler_->message_sent( shared_from_this(), message );
}

void udp_session::write( any message ) {
	any p = filter_chain_->filter_send( shared_from_this(), message );
	try {
		shared_ptr<io_buffer> buffer = any_cast<shared_ptr<io_buffer>>( p );
		socket_->async_send_to(
			boost::asio::buffer( buffer->data(), buffer->size() ), 
			remote_endpoint_,
			boost::bind(&io_session::handle_write_complete, 
			shared_from_this(), message,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	} catch( const bad_any_cast & ) {
		throw illegal_packet();
	}
}