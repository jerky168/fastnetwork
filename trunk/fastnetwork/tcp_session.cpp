#include "StdAfx.h"
#include "tcp_session.h"
#include "io_buffer.h"
#include "illegal_packet.h"

using namespace fastnetwork;
using namespace fastnetwork::tcp;

tcp_session::tcp_session( session_manager & manager, shared_ptr<ip::tcp::socket> socket, endpoint remote, size_t timeout_sec )
: abstract_session(manager, socket->local_endpoint(), remote, timeout_sec )
, socket_(socket)
{

}

void fastnetwork::tcp::tcp_session::write( any message )
{
	if ( ! connected_ )	{
		throw std::exception("illegal state, not connected.");
	}

	any p = filter_chain_->filter_send( shared_from_this(), message );
	try {
		shared_ptr<io_buffer> buffer = any_cast<shared_ptr<io_buffer>>( p );
		async_write( *(socket_.get()),
			boost::asio::buffer( buffer->data(), buffer->size() ), 
			boost::bind(&io_session::handle_write_complete, 
			shared_from_this(), message,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	} catch( const bad_any_cast & ) {
		throw illegal_packet();
	}

	last_active_time_ = microsec_clock::local_time();
}

void tcp_session::handle_write_complete( any message, const system::error_code& error, size_t /*bytes_transferred*/ )
{
	if ( ! error ) {
		this->handler_->message_sent( shared_from_this(), message );
	} else {
		// TODO: send error!
	}
}