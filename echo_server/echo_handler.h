#pragma once

class echo_handler :
	public abstract_session_handler
{
public:
	echo_handler(void);
	~echo_handler(void);

public:
	void message_received( io_session & session, any & message )
	{
		try
		{
			io_buffer * buffer = any_cast<io_buffer*>( message );
			string msg( reinterpret_cast<char*>( buffer->data() ), buffer->size() );
			cout << "<<< message received:" << endl;
			cout << msg << endl;

			boost::function<void()> handler_fun; // = boost::bind( &echo_handler::message_sent, this, session );

			session.write( any( io_buffer( msg.c_str(), msg.length() ) ), handler_fun );
		}
		catch( const bad_any_cast & )
		{
			cerr << "not buffer object." << endl;
		}
	}

	void message_sent( io_session & session, error_code & error, boost::any object  )
	{
		if( error ) {
			cerr << "send message failed." << endl;
			session.close();
		} else {
			cout << "send message successfully. " << endl;
		}
	}
};
