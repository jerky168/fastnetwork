#pragma once
#include "transport_type.h"
#include "udp_connector.h"

namespace fastnet {
	using namespace boost;

	class connector_factory
	{
	public:
		static shared_ptr<io_connector> new_connector( transport_type type, io_service & ios ) {
			shared_ptr<io_connector> connector;
			switch( type ) {
	case UDP:
		connector.reset( new fastnet::udp::udp_connector( ios ) );
		break;
	default:
		break;
			}
			return connector;
		}
	};
}
