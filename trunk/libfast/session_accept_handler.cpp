#include "StdAfx.h"
#include "session_accept_handler.h"
#include "tcp_session.h"

void fastnetwork::session_accept_handler::handle_accept( tcp_socket_ptr so, const error_code & error )
{
	if( error ) {
		cerr << "accept error: " << error << endl;
		return ;
	}

	cout << "incoming connection: " << so->remote_endpoint() << endl;
	tcp_session_ptr session = new_session(so);
	session->set_handler( &handler );
	session->start();
}

fastnetwork::tcp_session_ptr fastnetwork::session_accept_handler::new_session( tcp_socket_ptr so )
{
	tcp_session_ptr session( new tcp_session(so) );
	sessions.insert( session );
	return session;
}