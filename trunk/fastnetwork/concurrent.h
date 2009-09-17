#pragma once
#include <boost/thread.hpp>

namespace fastnetwork {
	namespace utility {
		using namespace boost;


		template<typename T>
		class concurrent
		{
		public:
			concurrent( T * px )
				: px_(px)
			{
			}
			~concurrent(void) {}

		public:
			// 0
			template<typename R>
			R invoke( R ( T::* f )() ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_ )();
			}
			template<typename R>
			R invoke( R ( T::* f )() const ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_ )();
			}

			// 1
			template<typename R, typename A1, typename B1>
			R invoke( R ( T::* f )(A1), B1 b1 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1 )();
			}
			template<typename R, typename A1, typename B1>
			R invoke( R ( T::* f )(A1) const, B1 b1 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1 )();
			}

			// 2
			template<typename R, typename A1, typename A2, typename B1, typename B2>
			R invoke( R ( T::* f )(A1, A2), B1 b1, B2 b2 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2 )();
			}
			template<typename R, typename A1, typename A2, typename B1, typename B2>
			R invoke( R ( T::* f )(A1, A2) const, B1 b1, B2 b2 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2 )();
			}

			// 3
			template<typename R, 
				typename A1, typename A2, typename A3,
				typename B1, typename B2, typename B3
			>
			R invoke( R ( T::* f )(A1, A2, A3), 
			B1 b1, B2 b2, B3 b3 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3,
				typename B1, typename B2, typename B3
			>
			R invoke( R ( T::* f )(A1, A2, A3) const, 
			B1 b1, B2 b2, B3 b3 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3 )();
			}

			// 4
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4,
				typename B1, typename B2, typename B3, typename B4
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4), 
			B1 b1, B2 b2, B3 b3, B4 b4 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4,
				typename B1, typename B2, typename B3, typename B4
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4) const, 
			B1 b1, B2 b2, B3 b3, B4 b4 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4 )();
			}

			// 5
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5,
				typename B1, typename B2, typename B3, typename B4, typename B5
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5), 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5,
				typename B1, typename B2, typename B3, typename B4, typename B5
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5) const, 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5 )();
			}

			// 6
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6), 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6) const, 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6 )();
			}

			// 7
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6, typename B7
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6, A7), 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6, B7 b7 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6, b7 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6, typename B7
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6, A7) const, 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6, B7 b7 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6, b7 )();
			}

			// 8
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6, typename B7, typename B8
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6, A7, A8), 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6, B7 b7, B8 b8 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6, b7, b8 )();
			}
			template<typename R, 
				typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8,
				typename B1, typename B2, typename B3, typename B4, typename B5, typename B6, typename B7, typename B8
			>
			R invoke( R ( T::* f )(A1, A2, A3, A4, A5, A6, A7, A8) const, 
			B1 b1, B2 b2, B3 b3, B4 b4, B5 b5, B6 b6, B7 b7, B8 b8 ) {
				mutex::scoped_lock l(lock_);
				return ::boost::bind( f, px_, b1, b2, b3, b4, b5, b6, b7, b8 )();
			}

		private:
			mutex	lock_;
			shared_ptr<T>		px_;
		};

	}
}
