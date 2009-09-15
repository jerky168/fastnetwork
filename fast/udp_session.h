#pragma once
#include "illegal_packet.h"
#include "session_handler.h"
#include "udp_session_manager.h"

namespace fastnet {
	namespace udp {

		using namespace std;
		using namespace boost;
		using namespace boost::asio;
		using namespace boost::posix_time;

		class udp_session_manager;

		class udp_session : public fastnet::io_session, noncopyable
		{
		public:
			udp_session( udp_session_manager & manager, shared_ptr<ip::udp::socket> socket, endpoint remote, size_t timeout_sec );
			~udp_session(void);

		public:
			void write( any message );

			void close();

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

			bool is_idle() {
				return ( last_active_time_ + idle_timeout_ > microsec_clock::local_time() );
			}

		private:
			void handle_write_complete(any message,
				const boost::system::error_code& /*error*/,
				std::size_t /*bytes_transferred*/);


		private:
			udp_session_manager &			manager_;
			shared_ptr<ip::udp::socket>		socket_;
			endpoint						local_endpoint_;
			endpoint						remote_endpoint_;
			ip::udp::endpoint				socket_endpoint_;

			shared_ptr<session_handler>		handler_;
			shared_ptr<session_filter_chain> filter_chain_;

			std::map<string,any>			attributes_;

			bool							connected_;

			ptime							last_active_time_;
			time_duration					idle_timeout_;
		};
	}
}
