#pragma once
#include "session_handler.h"

namespace fastnet
{

	class abstract_session_handler :
		public fastnet::session_handler
	{
	public:
		abstract_session_handler(void);
		virtual ~abstract_session_handler(void);

	public:
		virtual void session_created( io_session & session );
		virtual void session_open( io_session & session );
		virtual void session_close( io_session & session );
		virtual void message_received( io_session & session, boost::any object );
		virtual void message_sent( io_session & session, boost::system::error_code error, boost::any object  );
		virtual void set_codec( protocol_codec * codec );

	protected:
		protocol_codec * codec;

	};

} // namespace fastnet