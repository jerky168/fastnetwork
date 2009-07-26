#pragma once
#include "illegal_packet.h"
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
			void write( any message );

			void close() {
				handler_->session_closed(shared_from_this());
			}

			void set_handler( shared_ptr<session_handler> handler ) {
				this->handler_ = handler;
			}

			shared_ptr<session_handler> get_handler() {
				return handler_;
			}

			boost::shared_ptr<session_filter_chain> get_filter_chain() {
				return filter_chain_;
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

			shared_ptr<session_handler>		handler_;
			shared_ptr<session_filter_chain> filter_chain_;
		};
	}
}
