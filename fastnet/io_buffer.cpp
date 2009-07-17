#include "StdAfx.h"
#include "io_buffer.h"
using namespace fastnet;

io_buffer::io_buffer(void)
: capacity_(0)
, size_(0)
, data_(NULL)
, load_factor_( 0.6F )
{
	init_container();
}

io_buffer::io_buffer( const void * const data, size_t size )
: capacity_(size)
, size_(size)
, data_(NULL)
, load_factor_( 0.6F )
{
	init_container();
	::memcpy( data_, data, size );
}

io_buffer::~io_buffer(void)
{
}

void io_buffer::append(void *data, size_t size)
{
	ensure_reserved( size );

	::memcpy( reinterpret_cast<char*>(data_) + size_, data, size );
	size_ += size;
}

size_t io_buffer::consume(size_t size)
{
	size_t consume_size = size;
	if( consume_size > size_ ) {
		consume_size = size_;
	}

	::memmove( data_, reinterpret_cast<char*>( data_ ) + consume_size, size_ - consume_size );
	size_ -= consume_size;
	return consume_size;
}