#pragma once
#include "types.h"

namespace fastnet
{
	class session_handler;

	class io_session;

	typedef shared_ptr<io_session> io_session_ptr;

	class io_session
	{
	public:
		io_session(void);
		virtual ~io_session(void);

	public:
		virtual void set_handler( session_handler * handler ) = 0;
		virtual session_handler * get_handler() = 0;

		virtual udp::endpoint get_remote_address() const = 0;
		virtual udp::endpoint get_local_address() const = 0;		
		virtual void write( boost::any object, boost::function<void()> handler ) = 0;
		virtual void close() = 0;

	};

} // namespace fastnet