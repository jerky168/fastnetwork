#pragma once

namespace fastnetwork {
	typedef shared_ptr<string> write_buffer_ptr;
	typedef shared_ptr<ip::tcp::socket> tcp_socket_ptr;

	class accept_handler;

	class tcp_session;
	typedef shared_ptr<tcp_session> tcp_session_ptr;

	class session_accept_handler;
	class session_handler;


}
