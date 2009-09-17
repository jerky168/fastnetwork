// cheat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

template<typename T>
class container {
public:
	// 0
	size_t clear() {
		size_t s = c_.size();
		c_.clear();
		return s;
	}
	size_t size() const {
		return c_.size();
	}

	// 1
	size_t push( const T& a1 ) {
		c_.push_back( a1 );
		return 1;
	}
	void get( T& a1 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;
	}

	// 2
	size_t push( const T& a1, const T& a2 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		return 2;
	}
	void get( T& a1, T& a2 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;
	}

	// 3
	size_t push( const T& a1, const T& a2, const T& a3 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		return 3;
	}
	void get( T& a1, T& a2, T& a3 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;
	}
	// 4
	size_t push( const T& a1, const T& a2, const T& a3, const T& a4 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		c_.push_back( a4 );
		return 4;
	}
	void get( T& a1, T& a2, T& a3, T& a4 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;

		++it;
		a4 = *it;
	}

	// 5
	size_t push( const T& a1, const T& a2, const T& a3, const T& a4, const T& a5 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		c_.push_back( a4 );
		c_.push_back( a5 );
		return 5;
	}
	void get( T& a1, T& a2, T& a3, T& a4, T& a5 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;

		++it;
		a4 = *it;

		++it;
		a5 = *it;
	}

	// 6
	size_t push( const T& a1, const T& a2, const T& a3, const T& a4, const T& a5, const T& a6 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		c_.push_back( a4 );
		c_.push_back( a5 );
		c_.push_back( a6 );
		return 6;
	}
	void get( T& a1, T& a2, T& a3, T& a4, T& a5, T& a6 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;

		++it;
		a4 = *it;

		++it;
		a5 = *it;

		++it;
		a6 = *it;
	}

	// 7
	size_t push( const T& a1, const T& a2, const T& a3, const T& a4, const T& a5, const T& a6, const T& a7 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		c_.push_back( a4 );
		c_.push_back( a5 );
		c_.push_back( a6 );
		c_.push_back( a7 );
		return 7;
	}
	void get( T& a1, T& a2, T& a3, T& a4, T& a5, T& a6, T& a7 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;

		++it;
		a4 = *it;

		++it;
		a5 = *it;

		++it;
		a6 = *it;

		++it;
		a7 = *it;
	}

	// 8
	size_t push( const T& a1, const T& a2, const T& a3, const T& a4, const T& a5, const T& a6, const T& a7, const T& a8 ) {
		c_.push_back( a1 );
		c_.push_back( a2 );
		c_.push_back( a3 );
		c_.push_back( a4 );
		c_.push_back( a5 );
		c_.push_back( a6 );
		c_.push_back( a7 );
		c_.push_back( a8 );
		return 8;
	}
	void get( T& a1, T& a2, T& a3, T& a4, T& a5, T& a6, T& a7, T& a8 ) const {
		vector<T>::const_iterator it = c_.begin();
		a1 = *it;

		++it;
		a2 = *it;

		++it;
		a3 = *it;

		++it;
		a4 = *it;

		++it;
		a5 = *it;

		++it;
		a6 = *it;

		++it;
		a7 = *it;

		++it;
		a8 = *it;
	}

private:
	vector<T>	c_;
};

void test() {
	concurrent<container<int>> cv( new container<int>() );

	int i = 0;
	int a[10] = {0};

	// 1
	cout << "1: ";
	cout << cv.invoke( &container<int>::push, ++i );
	cv.invoke( &container<int>::get, boost::ref( a[0] ) );
	cout << ", a[0]=" << a[0] << endl;

	// 2
	cout << "2: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i );
	cv.invoke( &container<int>::get, boost::ref( a[0] ), boost::ref( a[1] ) );
	cout << ", a[0]=" << a[0] << ", a[1]=" << a[1] << endl;

	// 3
	cout << "3: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, boost::ref( a[0] ), boost::ref( a[1] ), boost::ref( a[2] ) );
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
		<< endl;

	// 4
	cout << "4: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, boost::ref( a[0] ), boost::ref( a[1] ), boost::ref( a[2] ), boost::ref( a[3] ) );
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
	<< ", a[3]=" << a[3] 
	<< endl;

	// 5
	cout << "5: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, boost::ref( a[0] ), boost::ref( a[1] ), boost::ref( a[2] ), boost::ref( a[3] ), boost::ref( a[4] ) );
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
	<< ", a[3]=" << a[3] 
	<< ", a[4]=" << a[4] 
	<< endl;

	// 6
	cout << "6: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, 
		boost::ref( a[0] ), 
		boost::ref( a[1] ), 
		boost::ref( a[2] ), 
		boost::ref( a[3] ), 
		boost::ref( a[4] ), 
		boost::ref( a[5] ) );
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
	<< ", a[3]=" << a[3] 
	<< ", a[4]=" << a[4] 
	<< ", a[5]=" << a[5] 
	<< endl;

	// 7
	cout << "7: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i, ++i, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, 
		boost::ref( a[0] ), 
		boost::ref( a[1] ), 
		boost::ref( a[2] ), 
		boost::ref( a[3] ), 
		boost::ref( a[4] ), 
		boost::ref( a[5] ), 
		boost::ref( a[6] ) 
		);
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
	<< ", a[3]=" << a[3] 
	<< ", a[4]=" << a[4] 
	<< ", a[5]=" << a[5] 
	<< ", a[6]=" << a[6] 
	<< endl;

	// 8
	cout << "8: ";
	cout << cv.invoke( &container<int>::push, ++i, ++i, ++i, ++i, ++i, ++i, ++i, ++i );
	cv.invoke( &container<int>::get, 
		boost::ref( a[0] ), 
		boost::ref( a[1] ), 
		boost::ref( a[2] ), 
		boost::ref( a[3] ), 
		boost::ref( a[4] ), 
		boost::ref( a[5] ), 
		boost::ref( a[6] ), 
		boost::ref( a[7] ) 
		);
	cout
		<< ", a[0]=" << a[0] 
	<< ", a[1]=" << a[1] 
	<< ", a[2]=" << a[2] 
	<< ", a[3]=" << a[3] 
	<< ", a[4]=" << a[4] 
	<< ", a[5]=" << a[5] 
	<< ", a[6]=" << a[6] 
	<< ", a[7]=" << a[7] 
	<< endl;

	// 0
	cout << "0: ";
	cout << cv.invoke( &container<int>::size );
	cv.invoke( &container<int>::clear );
	cout << "cleared: " << cv.invoke( &container<int>::size ) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();

	cin.get();
	return 0;
}

