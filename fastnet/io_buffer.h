#pragma once

namespace fastnet
{

	// TODO: implement io_buffer, or use asio::mutalbe_buffer
	class io_buffer
	{
	public:
		io_buffer(void);
		io_buffer( const void * const data, size_t size );
		virtual ~io_buffer(void);

	public:
		void append( void * data, size_t size );
		size_t consume( size_t size );
		void* data() {
			return data_;
		}
		size_t size() const {
			return size_;
		}

	private:
		void init_container() {
			data_ = new char[capacity_];
		}

		void ensure_reserved( size_t size ) {
			if( size + size_ > capacity_ ) {
				size_t capacity = static_cast<size_t>( capacity_ / load_factor_ );
				void * data = new char[ capacity ];
				assert( data != NULL );
				delete[] data_;

				data_ = data;
				capacity_ = capacity;
			}
		}


	private:
		size_t		capacity_;
		size_t		size_;
		void *		data_;

		float		load_factor_;
	};

} // namespace fastnet