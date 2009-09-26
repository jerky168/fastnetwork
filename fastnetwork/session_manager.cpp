#include "StdAfx.h"
#include "session_manager.h"
#include "udp_session.h"
#include "tcp_session.h"
using namespace boost;
using namespace boost::asio;

using namespace fastnetwork;

shared_ptr<io_session> fastnetwork::session_manager::new_session( shared_ptr<ip::udp::socket> socket, endpoint remote )
{
	mutex::scoped_lock	lock(mutex_);

	shared_ptr<io_session> session( new udp::udp_session( *this, socket, remote, 120 ) );
	sessions_.insert( make_pair(remote, session) );
	return session;
}

shared_ptr<io_session> fastnetwork::session_manager::new_session( shared_ptr<ip::tcp::socket> socket, endpoint remote )
{
	mutex::scoped_lock	lock(mutex_);

	shared_ptr<io_session> session( new tcp::tcp_session( *this, socket, remote, 120 ) );
	sessions_.insert( make_pair(remote, session) );
	return session;
}
void fastnetwork::session_manager::check_session_idle()
{
	session_map idle_sessions;
	find_idle_sessions(idle_sessions);

	for ( session_map::iterator it = idle_sessions.begin(); it != idle_sessions.end(); ++it )
	{
		shared_ptr<io_session> session = it->second;
		session->get_filter_chain()->session_idle( session );
	}
}

void fastnetwork::session_manager::close_session( shared_ptr<io_session> session )
{
	mutex::scoped_lock	lock(mutex_);
	sessions_.erase( session->get_remote_endpoint() );
}

void fastnetwork::session_manager::find_idle_sessions( session_map &idle_sessions )
{
	mutex::scoped_lock	lock(mutex_);
	for ( session_map::iterator it = sessions_.begin(); it != sessions_.end(); ++it )
	{
		shared_ptr<io_session> session = it->second;
		if ( session->is_idle() )
		{
			idle_sessions.insert( *it );
		}
	}
}