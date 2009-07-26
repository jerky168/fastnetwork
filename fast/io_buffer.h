#pragma once

namespace fastnet
{
	using namespace boost;

	// TODO: implement io_buffer, or use asio::mutalbe_buffer
	class io_buffer
	{
	private:
		typedef unsigned char byte;

	public:
		io_buffer(void);
		io_buffer( const void * const data, size_t size );
		virtual ~io_buffer(void);

	public:
		void prepend( const void * const data, size_t size );
		void append( const void * const data, size_t size );
		size_t consume( size_t size );
		void* data() {
			return data_.get();
		}
		size_t size() const {
			return size_;
		}
		size_t limit( size_t size ) {
			if( size_ >= size ) {
				return 0;
			}
			size_t removed = size_ - size;
			this->size_ = size;
			return removed;
		}

	private:
		void init_container() {
			const size_t MIN_SIZE = 16;
			if( capacity_ < MIN_SIZE ) {
				capacity_ = MIN_SIZE;
			}
			data_.reset( new byte[capacity_] );
		}

		void ensure_reserved( size_t size ) {
			if( size + size_ > capacity_ ) {
				size_t capacity = static_cast<size_t>( capacity_ / load_factor_ );

				if( capacity < size + size_ ) {
					capacity = size + size_;
				}

				byte * data = new byte[ capacity ];
				assert( data != NULL );
				::memcpy( data, data_.get(), size_ );
				data_.reset( data );
				capacity_ = capacity;
			}
		}


	private:
		size_t				capacity_;
		size_t				size_;
		scoped_ptr<byte>	data_;

		float				load_factor_;
	};

} // namespace fastnet