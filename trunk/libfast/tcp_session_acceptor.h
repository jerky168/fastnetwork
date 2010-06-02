#pragma once
#include "tcp_acceptor.h"
#include "session_accept_handler.h"

namespace fastnetwork {
	class tcp_session_acceptor
	{
	public:
		tcp_session_acceptor(io_service & service, session_handler & handler)
			: service_(service)
			, handler_(handler)
			, accept_handler_(handler_)
			, acceptor_(service_, accept_handler_)
		{

		}
		virtual ~tcp_session_acceptor(void){}

	public:
		void bind( ip::tcp::endpoint & ep ) {
			acceptor_.bind(ep);
		}

	private:
		io_service &		service_;

		session_handler &	handler_;
		session_accept_handler accept_handler_;
		tcp_acceptor		acceptor_;
	};
}
