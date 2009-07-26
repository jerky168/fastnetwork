#pragma once
#include "session_filter.h"

namespace fastnet {
	using namespace std;
	using namespace boost;

	class io_session;
	class session_filter;	

	class session_filter_chain : public session_filter
	{
	public:
		session_filter_chain(void) {}
		virtual ~session_filter_chain(void) {}

	public:
		virtual void add_filter( shared_ptr<session_filter> filter ) = 0;
		virtual void add_filter( size_t index, shared_ptr<session_filter> filter ) = 0;
		virtual void remove_filter( shared_ptr<session_filter> filter ) = 0;
	};

}