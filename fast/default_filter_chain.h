#pragma once
#include <vector>
#include "session_filter_chain.h"

namespace fastnet {

	class default_filter_chain : public session_filter_chain
	{
	private:
		typedef void (session_filter::*session_fun)(shared_ptr<io_session>);
 
	public:
		default_filter_chain()
			: filters_()
		{}
		~default_filter_chain(void) {}

	public:
		void add_filter( boost::shared_ptr<session_filter> filter ) {
			add_filter( filters_.size(), filter );
		}
		void add_filter( size_t index, boost::shared_ptr<session_filter> filter ) {
			filters_.insert( filters_.begin() + index, filter );
		}

		void remove_filter( boost::shared_ptr<session_filter> filter ) {
			for( size_t i = 0; i < filters_.size(); ++i ) {
				if( filters_[i] == filter ) {
					filters_.erase( filters_.begin() + i );
					break;
				}
			}
		}

		void session_connected( shared_ptr<io_session> session ) {
			reverse_filters( session, &session_filter::session_connected );
			session->get_handler()->session_connected( session );
		}

		void session_closed( shared_ptr<io_session> session ) {
			session->get_handler()->session_closed( session );
			do_filters( session, &session_filter::session_closed );
		}

		void session_idle( shared_ptr<io_session> session ) {
			do_filters( session, &session_filter::session_idle );
			session->get_handler()->session_idle( session );
		}

		any filter_receive( shared_ptr<io_session> session, any packet ) {
			any p = packet;
			for( size_t i = filters_.size(); i > 0; --i ) {
				p = filters_[i - 1]->filter_receive( session, p );
			}
			return p;
		}

		any filter_send( shared_ptr<io_session> session, any packet ) {
			any p = packet;
			for( size_t i = 0; i < filters_.size(); ++i ) {
				p = filters_[i]->filter_send( session, p );
			}
			return p;
		}

	private:
		void do_filters( shared_ptr<io_session> session, session_fun fun ) {
			for( size_t i = 0; i < filters_.size(); ++i ) {
				(filters_[i].get()->*fun)( session );
			}
		}

		void reverse_filters( shared_ptr<io_session> session, session_fun fun ) {
			for( size_t i = filters_.size(); i > 0; --i ) {
				(filters_[i - 1].get()->*fun)( session );
			}
		}

	private:
		std::vector<boost::shared_ptr<session_filter>> filters_;
	};
		//virtual void message_received( boost::shared_ptr<io_session> session, boost::any message ) = 0;

		//virtual void message_sent( boost::shared_ptr<io_session> session, boost::any message ) = 0;

		//virtual void session_accepted( boost::shared_ptr<io_session> session ) = 0;

		//virtual void session_closed( boost::shared_ptr<io_session> session ) = 0;

		//virtual void session_timeout( boost::shared_ptr<io_session> session ) = 0;

}