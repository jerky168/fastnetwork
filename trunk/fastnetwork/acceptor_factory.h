#pragma once
#include "transport_type.h"
#include "io_acceptor.h"
#include "udp_acceptor.h"

namespace fastnetwork {
	class acceptor_factory
	{
	public:
		acceptor_factory(void){}
		~acceptor_factory(void){}

	public:
		static boost::shared_ptr<io_acceptor> new_acceptor( transport_type type, io_service & ios ) {
			boost::shared_ptr<io_acceptor> acceptor;
			switch( type ) {
	case UDP:
		acceptor.reset( new fastnetwork::udp::udp_acceptor(ios) );
		break;
	default:
		break;
			}
			return acceptor;
		}
	};
}
