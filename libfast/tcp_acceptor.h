#pragma once
#include "types.h"

namespace fastnetwork {

class tcp_acceptor {
public:
	tcp_acceptor(io_service& ios, accept_handler & h)
		: service(ios)
		, acceptor(service)
		, max_connection(100)
		, socket()
		, handler(h)
	{}

public:
	void bind( ip::tcp::endpoint & ep );

protected:
	void start_accept();

	void handle_accept( const error_code & error );

protected:
	io_service &		service;
	ip::tcp::acceptor	acceptor;
	size_t				max_connection;
	tcp_socket_ptr		socket;
	accept_handler &	handler;
};

}