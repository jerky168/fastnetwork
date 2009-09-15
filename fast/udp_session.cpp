#include "StdAfx.h"
#include "udp_session.h"
#include "default_filter_chain.h"
#include "io_buffer.h"
using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace fastnet;
using namespace fastnet::udp;

udp_session::udp_session( udp_session_manager & manager, shared_ptr<ip::udp::socket> socket, endpoint remote, size_t timeout_sec )
: manager_(manager)
, socket_(socket)
, local_endpoint_(socket_->local_endpoint())
, remote_endpoint_(remote)
, socket_endpoint_ (remote_endpoint_.address(), remote_endpoint_.port())
, filter_chain_( new default_filter_chain() )
, connected_(false)
, idle_timeout_( seconds(timeout_sec) )
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

void fastnet::udp::udp_session::close()
{
	manager_.close_session( shared_from_this() );
	handler_->session_closed(shared_from_this());
	connected_ = false;
}