#include "StdAfx.h"
#include "udp_connector.h"
#include "udp_session.h"
#include "io_buffer.h"
#include "log.h"
using namespace fastnet;
using namespace fastnet::udp;
using namespace boost::asio;

void fastnet::udp::udp_connector::handle_receive( const boost::system::error_code& error, std::size_t bytes_transferred )
{
	if (!error || error == boost::asio::error::message_size)
	{
		shared_ptr<fastnet::io_session> session( new udp_session( socket_, socket_->local_endpoint(), remote_endpoint_ ) );
		shared_ptr<io_buffer> packet( new io_buffer(recv_buffer_.data(), bytes_transferred) );

		// handler_.session_created(session);
		handler_(session);
		any message = session->get_filter_chain()->filter_receive( session, packet );
		session->get_handler()->message_received( session, message );

		start_receive();
	}
	else 
	{
		LOG( error );
	}

}

static void handle_connected( const boost::system::error_code & error ) {

}

void fastnet::udp::udp_connector::connect( ip::udp::endpoint endpoint )
{
	if( ! socket_ ) {
		socket_.reset( new ip::udp::socket(io_service_) );
	}

	socket_->async_connect( endpoint,
		::boost::bind( &udp_connector::handle_connect, this, boost::asio::placeholders::error )
		);
}

void fastnet::udp::udp_connector::start_receive()
{
	LOG( "receive at local: " << socket_->local_endpoint() );
	socket_->async_receive_from(
		boost::asio::buffer(recv_buffer_), remote_endpoint_,
		boost::bind(&udp_connector::handle_receive, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void fastnet::udp::udp_connector::handle_connect( const boost::system::error_code& error )
{
	if ( ! error ) {
		shared_ptr<io_session> session( new udp_session( socket_, socket_->local_endpoint(), socket_->remote_endpoint() ) );
		start_receive();
		handler_(session);
	} else {
		handler_( shared_ptr<io_session>() );
	}
}