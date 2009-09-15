#include "StdAfx.h"
#include "udp_acceptor.h"
#include "io_buffer.h"

void fastnet::udp::udp_acceptor::handle_receive( const boost::system::error_code& error, std::size_t bytes_transferred )
{
	if (!error || error == boost::asio::error::message_size)
	{
		shared_ptr<fastnet::io_session> session = session_manager_.new_session( socket_, remote_endpoint_ );
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