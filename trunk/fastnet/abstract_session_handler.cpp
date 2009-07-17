#include "StdAfx.h"
#include "abstract_session_handler.h"
#include "protocol_codec.h"
#include "io_session.h"
using namespace fastnet;

abstract_session_handler::abstract_session_handler(void)
{
}

abstract_session_handler::~abstract_session_handler(void)
{
}

void fastnet::abstract_session_handler::session_created( io_session & session )
{
	LOG( "session created. " << session.get_remote_address() );
}

void fastnet::abstract_session_handler::session_open( io_session & session )
{
	LOG( "session open. " << session.get_remote_address() );
}

void fastnet::abstract_session_handler::session_close( io_session & session )
{
	LOG( "seesion close. " << session.get_remote_address() );
}

void fastnet::abstract_session_handler::message_received( io_session & session, boost::any object )
{
	LOG( "session message received. " << session.get_remote_address() );
}

void fastnet::abstract_session_handler::message_sent( io_session & session, boost::system::error_code error, boost::any object )
{
	LOG( "seesion message sent. " << session.get_remote_address() );
}

void fastnet::abstract_session_handler::set_codec( protocol_codec * codec )
{
	this->codec = codec;
}