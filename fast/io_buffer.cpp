#include "StdAfx.h"
#include "io_buffer.h"
using namespace fastnet;

io_buffer::io_buffer(void)
: capacity_(0)
, size_(0)
, data_()
, load_factor_( 0.6F )
{
	init_container();
}

io_buffer::io_buffer( const void * const data, size_t size )
: capacity_(size)
, size_(size)
, data_()
, load_factor_( 0.6F )
{
	init_container();
	::memcpy( data_.get(), data, size );
}

io_buffer::~io_buffer(void)
{
}

void io_buffer::prepend( const void * const data, size_t size )
{
	ensure_reserved( size );

	::memmove( reinterpret_cast<byte*>( data_.get() ) + size, data_.get(), size_ );
	::memcpy( data_.get(), data, size );
	size_ += size;
}

void io_buffer::append(const void * const data, size_t size)
{
	ensure_reserved( size );

	::memcpy( reinterpret_cast<byte*>( data_.get() ) + size_, data, size );
	size_ += size;
}

size_t io_buffer::consume(size_t size)
{
	size_t consume_size = size;
	if( consume_size > size_ ) {
		consume_size = size_;
	}

	::memmove( data_.get(), reinterpret_cast<byte*>( data_.get() ) + consume_size, size_ - consume_size );
	size_ -= consume_size;
	return consume_size;
}