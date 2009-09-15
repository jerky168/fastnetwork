#include "StdAfx.h"
#include "udp_session_manager.h"
#include "udp_session.h"
using namespace boost;
using namespace boost::asio;

using namespace fastnet;

shared_ptr<io_session> fastnet::udp::udp_session_manager::new_session( shared_ptr<ip::udp::socket> socket, endpoint remote )
{
	shared_ptr<io_session> session( new udp::udp_session( *this, socket, remote, 120 ) );
	sessions_.insert( make_pair(remote, session) );
	return session;
}

void fastnet::udp::udp_session_manager::check_session_idle()
{
	session_map idle_sessions;

	for ( session_map::iterator it = sessions_.begin(); it != sessions_.end(); ++it )
	{
		shared_ptr<io_session> session = it->second;
		if ( session->is_idle() )
		{
			idle_sessions.insert( *it );
		}
	}

	for ( session_map::iterator it = idle_sessions.begin(); it != idle_sessions.end(); ++it )
	{
		shared_ptr<io_session> session = it->second;
		session->get_filter_chain()->session_idle( session );
	}
}

void fastnet::udp::udp_session_manager::close_session( shared_ptr<io_session> session )
{
	sessions_.erase( session->get_remote_endpoint() );
}