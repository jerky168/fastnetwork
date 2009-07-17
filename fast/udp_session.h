#pragma once
//#include "types.h"
#include "session_handler.h"

namespace fastnet {
	namespace udp {
		using namespace std;
		using namespace boost;
		using namespace boost::asio;

		class udp_session : public fastnet::io_session
		{
		public:
			udp_session(shared_ptr<ip::udp::socket> socket, ip::udp::endpoint local, ip::udp::endpoint remote);
			~udp_session(void);

		public:
			void write( any message ) {
				socket_->async_send_to(
					boost::asio::buffer(*(any_cast<boost::shared_ptr<std::string>>(message))), 
					remote_endpoint_,
					boost::bind(&io_session::handle_write_complete, 
						shared_from_this(), message,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}

			void close() {
				handler_->session_closed(shared_from_this());
			}

			void set_handler( shared_ptr<fastnet::session_handler> handler ) {
				this->handler_ = handler;
			}

			shared_ptr<fastnet::session_handler> get_handler() {
				return handler_;
			}

			ip::udp::endpoint get_local_endpoint() const {
				return local_endpoint_;
			}

			ip::udp::endpoint get_remote_endpoint() const {
				return remote_endpoint_;
			}

			shared_ptr<ip::udp::socket> get_socket() {
				return socket_;
			}

		private:
			void handle_write_complete(any message,
				const boost::system::error_code& /*error*/,
				std::size_t /*bytes_transferred*/);


		private:
			shared_ptr<ip::udp::socket>		socket_;
			ip::udp::endpoint				local_endpoint_;
			ip::udp::endpoint				remote_endpoint_;

			shared_ptr<fastnet::session_handler>	handler_;
		};
	}
}
