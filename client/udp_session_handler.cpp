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
	try {
		shared_ptr<io_buffer> buffer = any_cast<shared_ptr<io_buffer>>( message );

		if( buffer->size() < 2 ) {
			cout << "buffer size too small: " << buffer->size() << endl;
			return ;
		}

		unsigned short message_len = 0;
		char * buf = reinterpret_cast<char*>( buffer->data() );
		::memcpy( &message_len, buf, sizeof(message_len) );
		assert( buffer->size() >= message_len + 2 );
		string received( buf + sizeof( message_len ), message_len );
		cout << received << endl;
	} catch( const bad_any_cast & ) {
		LOG( "received message is not io_buffer object." );
	}
}
