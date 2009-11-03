#pragma once
#include "io_session.h"
#include "session_manager.h"

namespace fastnetwork {
	using namespace std;
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::posix_time;

	class abstract_session : public fastnetwork::io_session
	{
	public:
		abstract_session(session_manager & manager, endpoint local, endpoint remote, size_t timeout_sec);
		virtual ~abstract_session(void){};

	public:
		virtual void set_handler( shared_ptr<session_handler> handler ) {
			this->handler_ = handler;
		}

		virtual shared_ptr<session_handler> get_handler() {
			return handler_;
		}

		virtual shared_ptr<session_filter_chain> get_filter_chain() {
			return filter_chain_;
		}


		virtual endpoint get_local_endpoint() const {
			return local_endpoint_;
		}

		virtual endpoint get_remote_endpoint() const {
			return remote_endpoint_;
		}
	
		virtual void write( any object ) = 0;
		virtual void close()
		{
			manager_.close_session( shared_from_this() );
			handler_->session_closed(shared_from_this());
			connected_ = false;
		}

		virtual void handle_write_complete(any message,
			const system::error_code& /*error*/,
			size_t /*bytes_transferred*/) = 0;

		virtual void set_attribute( const string & key, any value ) {
			mutex::scoped_lock	lock(attribute_mutex_);
			attributes_[key] = value;
		}
		virtual any get_attribute( const string & key ) {
			mutex::scoped_lock	lock(attribute_mutex_);
			if( attributes_.find( key ) == attributes_.end() ) {
				return any();
			}
			return attributes_[key];
		}
		virtual void remove_attribute( const string & key ) {
			mutex::scoped_lock	lock(attribute_mutex_);
			attributes_.erase(key);
		}

		virtual bool is_connected() {
			return connected_;
		}

		virtual void connected() {
			connected_ = true;
		}

		virtual bool is_idle() {
			return ( last_active_time_ + idle_timeout_ > microsec_clock::local_time() );
		}

	protected:
		session_manager &				manager_;

		endpoint						local_endpoint_;
		endpoint						remote_endpoint_;

		shared_ptr<session_handler>		handler_;
		shared_ptr<session_filter_chain> filter_chain_;

		bool							connected_;

		ptime							last_active_time_;
		time_duration					idle_timeout_;

		mutex							attribute_mutex_;
		map<string,any>					attributes_;

	};
}
