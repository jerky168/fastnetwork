#pragma once
#include "io_session.h"

namespace fastnet
{

	class protocol_decoder
	{
	public:
		protocol_decoder(void);
		virtual ~protocol_decoder(void);

	public:
		virtual list<any> decode( io_session & session, any data ) = 0;
	};

} // namespace fastnet