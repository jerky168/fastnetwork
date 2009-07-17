#pragma once
#include "session_handler.h"

namespace fastnet {
	class session_handler;

	class io_session : public boost::enable_shared_from_this<io_session>
	{
	public:
		io_session(void) {}
		virtual ~io_session(void){}

	public:
		virtual void set_handler( boost::shared_ptr<session_handler> handler ) = 0;
		virtual boost::shared_ptr<session_handler> get_handler() = 0;

		virtual boost::asio::ip::udp::endpoint get_remote_endpoint() const = 0;
		virtual boost::asio::ip::udp::endpoint get_local_endpoint() const = 0;		
		virtual void write( boost::any object ) = 0;
		virtual void close() = 0;

		virtual void handle_write_complete(boost::any message,
			const boost::system::error_code& /*error*/,
			std::size_t /*bytes_transferred*/) = 0;
	};
}
