#pragma once
#include "net_io_service.h"
#include "session_type.h"

namespace fastnet
{
	class session_accept_handler;

	class session_acceptor;

	typedef shared_ptr<session_acceptor> session_acceptor_ptr;

	class session_acceptor :
		public net_io_service, enable_shared_from_this<session_acceptor>
	{
	public:
		session_acceptor(void);
		virtual ~session_acceptor(void);

	public:
		virtual transport_type get_session_type() = 0;
		virtual void bind( boost::asio::ip::udp::endpoint local_address ) = 0;
		virtual void unbind( boost::asio::ip::udp::endpoint local_address ) = 0;
		virtual void set_handler( session_accept_handler * handler ) = 0;
	};

} // namespace fastnet