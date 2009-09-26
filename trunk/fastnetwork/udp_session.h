#pragma once
#include "session_handler.h"
#include "abstract_session.h"

namespace fastnetwork {

	class session_manager;

	namespace udp {

		using namespace std;
		using namespace boost;
		using namespace boost::asio;
		using namespace boost::posix_time;

		class udp_session : public fastnetwork::abstract_session, noncopyable
		{
		public:
			udp_session( session_manager & manager, shared_ptr<ip::udp::socket> socket, endpoint remote, size_t timeout_sec );
			~udp_session(void);

		public:
			void write( any message );

			shared_ptr<ip::udp::socket> get_socket() {
				return socket_;
			}


		private:
			void handle_write_complete(any message,
				const boost::system::error_code& /*error*/,
				std::size_t /*bytes_transferred*/);


		private:
			shared_ptr<ip::udp::socket>		socket_;
			ip::udp::endpoint				socket_endpoint_;
		};
	}
}
