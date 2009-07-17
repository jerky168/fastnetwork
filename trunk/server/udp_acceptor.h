#pragma once

#include "types.h"
#include "udp_session.h"

typedef boost::function<void( session_ptr session )> session_accept_handler;

class udp_acceptor : public fastnet::io_acceptor
{
public:
	udp_acceptor( unsigned short port )
		: io_service_()
		, local_endpoint_(udp::v4(), port)
		, socket_( new udp::socket(io_service_, local_endpoint_) )
		, remote_endpoint_()
		, recv_buffer_()
	{
	}

	udp_acceptor( const string & host, unsigned short port )
		: io_service_()
		, local_endpoint_(boost::asio::ip::address::from_string(host), port)
		, socket_( new udp::socket(io_service_, local_endpoint_) )
		, remote_endpoint_()
		, recv_buffer_()
	{
	}

	udp_acceptor( const boost::asio::ip::address & addr, unsigned short port )
		: io_service_()
		, local_endpoint_(addr, port)
		, socket_( new udp::socket(io_service_, local_endpoint_) )
		, remote_endpoint_()
		, recv_buffer_()
	{
	}

public:
	void start() {
		start_receive();
		io_service_.run();
	}

	void set_handler( session_accept_handler handler ) {
		this->handler_ = handler;
	}

private:
	void start_receive()
	{
		socket_->async_receive_from(
			boost::asio::buffer(recv_buffer_), remote_endpoint_,
			boost::bind(&udp_acceptor::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(const boost::system::error_code& error,
		std::size_t bytes_transferred)
	{
		if (!error || error == boost::asio::error::message_size)
		{
			session_ptr session( new udp_session( socket_, local_endpoint_, remote_endpoint_ ) );
			any message = shared_ptr<std::string>(
				new std::string(recv_buffer_.data(), bytes_transferred));

			// handler_.session_created(session);
			handler_(session);
			session->get_handler()->message_received( session, message );

			start_receive();
		}
		else 
		{
			LOG( error );
		}
	}

private:
	boost::asio::io_service		io_service_;
	udp::endpoint				local_endpoint_;
	socket_ptr					socket_;
	udp::endpoint				remote_endpoint_;
	boost::array<char, 1500>	recv_buffer_;

	session_accept_handler		handler_;
};
