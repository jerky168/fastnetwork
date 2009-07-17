#pragma once
#include "session_type.h"
#include "io_acceptor.h"
#include "udp_acceptor.h"

namespace fastnet {
	class acceptor_factory
	{
	public:
		acceptor_factory(void){}
		~acceptor_factory(void){}

	public:
		static boost::shared_ptr<io_acceptor> new_acceptor( session_type type ) {
			boost::shared_ptr<io_acceptor> acceptor;
			switch( type ) {
	case UDP:
		acceptor.reset( new fastnet::udp::udp_acceptor() );
		break;
	default:
		break;
			}
			return acceptor;
		}
	};
}
