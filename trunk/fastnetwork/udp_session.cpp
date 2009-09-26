#include "StdAfx.h"
#include "udp_session.h"
#include "io_buffer.h"
#include "illegal_packet.h"

#include "illegal_packet.h"
using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace fastnetwork;
using namespace fastnetwork::udp;

udp_session::udp_session( session_manager & manager, shared_ptr<ip::udp::socket> socket, endpoint remote, size_t timeout_sec )
: abstract_session(manager,socket->local_endpoint(), remote, timeout_sec )
, socket_(socket)
, socket_endpoint_ (remote_endpoint_.address(), remote_endpoint_.port())
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
	if ( ! connected_ )	{
		throw std::exception("illegal state, not connected.");
	}

	any p = filter_chain_->filter_send( shared_from_this(), message );
	try {
		shared_ptr<io_buffer> buffer = any_cast<shared_ptr<io_buffer>>( p );
		socket_->async_send_to(
			boost::asio::buffer( buffer->data(), buffer->size() ), 
			socket_endpoint_,
			boost::bind(&io_session::handle_write_complete, 
			shared_from_this(), message,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	} catch( const bad_any_cast & ) {
		throw illegal_packet();
	}

	last_active_time_ = microsec_clock::local_time();
}
