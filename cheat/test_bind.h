#pragma once
#include "test_fixture.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
using namespace boost;

class test_bind :
	public test_fixture
{
public:
	test_bind(void);
	~test_bind(void);

public:
	void test() {
		bind();
		test_bind_params();
	}

private:
	void bind() {
		boost::function<void( const string & )> fun = boost::bind( &test_bind::fun, this, _1 );
		fun( string( "hello" ) );
	}

	void test_bind_params() {
		boost::function<void()> fun = boost::bind( &test_bind::fun, this, string( "hi" ) );
		fun();
	}

	void fun( const string & i ) {
		cout << i << endl;
	}
};
