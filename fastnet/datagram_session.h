#pragma once
#include "abstract_session.h"
#include "session_handler.h"

namespace fastnet
{
	namespace udp
	{

	class datagram_session :
		public fastnet::abstract_session
	{
	public:
		// ( socket_, socket_->local_endpoint(), remote_endpoint_ );
		datagram_session( socket_ptr socket, endpoint local, endpoint remote );
		virtual ~datagram_session(void);

	public:
		void write( boost::any object, boost::function<void()> handler );

		void handle_write_complete( const error_code &err , size_t bytes_trans, asio::mutable_buffers_1 * data ) {
			handler->message_sent( *this, err, any( data ) );
		}

		void close() {
		}
	};

	} // namespace udp
} // namespace fastnet