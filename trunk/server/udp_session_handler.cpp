#include "StdAfx.h"
#include "udp_session_handler.h"

udp_session_handler::udp_session_handler(void)
{
}

udp_session_handler::~udp_session_handler(void)
{
}

void udp_session_handler::message_received( session_ptr session, any message )
{
	LOG( "message received from " << session->get_remote_endpoint() << "@" << session->get_local_endpoint() );
	LOG( "sending: " << *(any_cast<message_ptr>(message)) );

	session->write( message );
}

void udp_session_handler::message_sent( session_ptr session, any message )
{
	LOG( "message sent." );
	session->close();
}

void udp_session_handler::session_accepted( session_ptr session )
{
	sessions_.insert( make_pair(session->get_remote_endpoint(), session) );
}

void udp_session_handler::session_closed( session_ptr session )
{
	sessions_.erase( session->get_remote_endpoint() );
}