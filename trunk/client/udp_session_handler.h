#pragma once

typedef boost::shared_ptr<fastnet::io_session> session_ptr;

typedef boost::shared_ptr<fastnet::session_handler> session_handler_ptr;

typedef boost::shared_ptr<boost::asio::ip::udp::socket> socket_ptr;

typedef boost::shared_ptr<std::string>	message_ptr;

#define LOG(msg) { \
	::std::cout << msg << ::std::endl;	\
}


class udp_session_handler : public fastnet::session_handler
{
public:
	udp_session_handler(void);
	~udp_session_handler(void);

public:
	void message_received( session_ptr session, any message );

	void message_sent( session_ptr session, any  ) {
//		read_send(session);
	}

	void session_connected( session_ptr session ) {
		cout << "local: " << session->get_local_endpoint() << " to " << session->get_remote_endpoint() << endl;
		session_ = session;
		session->connected();
//		read_send(session);
	}

	void session_closed( session_ptr session ) {
		session_.reset();
	}

	void session_timeout( session_ptr session ) {

	}

private:
	session_ptr	session_;
};
