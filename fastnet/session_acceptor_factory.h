#pragma once

#include "session_type.h"
#include "datagram_acceptor.h"

namespace fastnet
{

	class session_acceptor_factory
	{
	public:
		session_acceptor_factory(void);
		~session_acceptor_factory(void);

	public:
		static session_acceptor * new_session_acceptor( session_type type ) {
			switch( type ) {
	case UDP:
		return new fastnet::udp::datagram_acceptor();
		break;
	default:
		return NULL;
			}
		}
	};

}