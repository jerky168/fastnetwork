#pragma once

namespace fastnet
{
	class io_session;
	class protocol_codec;

	class session_handler
	{
	public:
		session_handler(void);
		virtual ~session_handler(void);

	public:
		virtual void session_created( io_session & session ) = 0;
		virtual void session_open( io_session & session ) = 0;
		virtual void session_close( io_session & session ) = 0;
		virtual void message_received( io_session & session, boost::any object ) = 0;
		virtual void message_sent( io_session & session, boost::system::error_code error, boost::any object ) = 0;
		virtual void set_codec( protocol_codec * codec ) = 0;
	};


} // namespace fastnet