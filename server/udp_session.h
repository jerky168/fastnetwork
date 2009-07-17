#pragma once
#include "types.h"
#include "udp_session_handler.h"


class udp_session : public fastnet::io_session
{
public:
	udp_session(socket_ptr socket, udp::endpoint local, udp::endpoint remote);
	~udp_session(void);

public:
	void write( any message ) {
		socket_->async_send_to(boost::asio::buffer(*(any_cast<message_ptr>(message))), remote_endpoint_,
			boost::bind(&io_session::handle_write_complete, shared_from_this(), message,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void close() {
		handler_->session_closed(shared_from_this());
	}

	void set_handler( session_handler_ptr handler ) {
		this->handler_ = handler;
	}

	session_handler_ptr get_handler() {
		return handler_;
	}

	udp::endpoint get_local_endpoint() const {
		return local_endpoint_;
	}

	udp::endpoint get_remote_endpoint() const {
		return remote_endpoint_;
	}

	socket_ptr get_socket() {
		return socket_;
	}

private:
	void handle_write_complete(any message,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/);


private:
	socket_ptr					socket_;
	udp::endpoint				local_endpoint_;
	udp::endpoint				remote_endpoint_;

	session_handler_ptr			handler_;
};
