#pragma once
#include "protocol_encoder.h"
#include "protocol_decoder.h"

namespace fastnet
{

	class protocol_codec :
		public protocol_encoder, 
		public protocol_decoder
	{
	public:
		protocol_codec(void);
		virtual ~protocol_codec(void);
	};

} // namespace fastnet