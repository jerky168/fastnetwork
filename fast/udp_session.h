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
			udp_session(shared_ptr<ip::udp::socket> socket, endpoint local, endpoint remote);
			~udp_session(void);

		public:
			void write( any message );

			void close() {
				handler_->session_closed(shared_from_this());
				connected_ = false;
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

			endpoint get_local_endpoint() const {
				return local_endpoint_;
			}

			endpoint get_remote_endpoint() const {
				return remote_endpoint_;
			}

			shared_ptr<ip::udp::socket> get_socket() {
				return socket_;
			}

			void set_attribute( const string & key, any value ) {
				attributes_[key] = value;
			}
			any get_attribute( const string & key ) {
				if( attributes_.find( key ) == attributes_.end() ) {
					return any();
				}
				return attributes_[key];
			}
			void remove_attribute( const string & key ) {
				attributes_.erase(key);
			}

			bool is_connected() {
				return connected_;
			}

			void connected() {
				connected_ = true;
			}

		private:
			void handle_write_complete(any message,
				const boost::system::error_code& /*error*/,
				std::size_t /*bytes_transferred*/);


		private:
			shared_ptr<ip::udp::socket>		socket_;
			endpoint						local_endpoint_;
			endpoint						remote_endpoint_;
			ip::udp::endpoint				socket_endpoint_;

			shared_ptr<session_handler>		handler_;
			shared_ptr<session_filter_chain> filter_chain_;

			std::map<string,any>			attributes_;

			bool							connected_;
		};
	}
}
