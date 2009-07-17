#pragma once

namespace fastnet {

	class session_acceptor;
	class io_session;

	class session_accept_handler
	{
	public:
		session_accept_handler(void);
		virtual ~session_accept_handler(void);

	public:
		virtual void session_accepted( session_acceptor_ptr acceptor, io_session_ptr session ) = 0;
	};

}