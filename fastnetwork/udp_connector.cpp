#include "StdAfx.h"
#include "udp_connector.h"
#include "udp_session.h"
#include "io_buffer.h"
#include "log.h"
using namespace fastnetwork;
using namespace fastnetwork::udp;
using namespace boost::asio;

void fastnetwork::udp::udp_connector::handle_receive( const boost::system::error_code& error, std::size_t bytes_transferred )
{
	if (!error || error == boost::asio::error::message_size)
	{
		shared_ptr<fastnetwork::io_session> session = manager_.new_session( socket_, remote_socket_endpoint_ );
		shared_ptr<io_buffer> packet( new io_buffer(recv_buffer_.data(), bytes_transferred) );

		create_handler_(session);
		session->get_filter_chain()->session_connected(session);
		any message = session->get_filter_chain()->filter_receive( session, packet );
		session->get_handler()->message_received( session, message );

		start_receive();
	}
	else 
	{
		LOG( error );
	}

}

void fastnetwork::udp::udp_connector::connect( endpoint endpoint )
{
	if( ! socket_ ) {
		socket_.reset( new ip::udp::socket(io_service_) );
	}

	remote_socket_endpoint_ = ip::udp::endpoint( endpoint.address(), endpoint.port() );
	socket_->async_connect( remote_socket_endpoint_,
		::boost::bind( &udp_connector::handle_connect, this, boost::asio::placeholders::error )
		);
}

void fastnetwork::udp::udp_connector::start_receive()
{
	LOG( "receive at local: " << socket_->local_endpoint() );
	socket_->async_receive_from(
		boost::asio::buffer(recv_buffer_), remote_socket_endpoint_,
		boost::bind(&udp_connector::handle_receive, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void fastnetwork::udp::udp_connector::handle_connect( const boost::system::error_code& error )
{
	if ( ! error ) {
		local_endpoint_ = socket_->local_endpoint();
		shared_ptr<io_session> session = manager_.new_session( socket_, socket_->remote_endpoint() );
		start_receive();
		create_handler_(session);
	} else {
		create_handler_( shared_ptr<io_session>() );
	}
}