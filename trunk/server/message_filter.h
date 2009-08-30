#pragma once

class message_filter : public session_filter
{
public:
	message_filter(void);
	~message_filter(void);

public:
	void session_connected( shared_ptr<io_session> session ){}
	void session_closed( shared_ptr<io_session> session ){}
	void session_timeout( shared_ptr<io_session> session ){}
	any filter_receive( shared_ptr<io_session> session, any p ){
		try {
			shared_ptr<io_buffer> packet = any_cast<shared_ptr<io_buffer>>( p );
			unsigned short len = 0;
			::memcpy( &len, packet->data(), sizeof(len) );
			if( packet->size() < len + sizeof(len) ) {
				throw illegal_packet();
			}

			shared_ptr<string> message( new string( reinterpret_cast<char*>(packet->data()) + 2, len ) );
			return message;
		} catch( const bad_any_cast & ) {
			throw illegal_packet();
		}
	}
	any filter_send( shared_ptr<io_session> session, any p ){

		try {
			shared_ptr<string> message = any_cast<shared_ptr<string>>(p);

			shared_ptr<io_buffer> buffer( new io_buffer() );
			unsigned short len = message->length();
			buffer->append( &len, sizeof(len));
			buffer->append( message->c_str(), len );

			return buffer;
		} catch( const bad_any_cast & ) {
			throw illegal_packet();
		}
	}

};
