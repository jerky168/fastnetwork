#pragma once
#include "abstract_session.h"

namespace fastnetwork {

	class session_manager;

	namespace tcp {
		class tcp_session : public fastnetwork::abstract_session, noncopyable
		{
		public:
			tcp_session( session_manager & manager, shared_ptr<ip::tcp::socket> socket, endpoint remote, size_t timeout_sec );
			~tcp_session(void){};

		public:
			void write( any message );

			shared_ptr<ip::tcp::socket> get_socket() {
				return socket_;
			}

		private:k
			void handle_write_complete(any message,
				const boost::system::error_code& /*error*/,
				std::size_t /*bytes_transferred*/);

		private:
			shared_ptr<ip::tcp::socket>		socket_;
			ip::tcp::endpoint				socket_endpoint_;
		};

	}
}
