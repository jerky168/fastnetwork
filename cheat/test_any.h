#pragma once
#include "test_fixture.h"

#include <boost/any.hpp>
using namespace boost;

class test_any :
	public test_fixture
{
public:
	test_any(void);
	~test_any(void);

public:
	void test() {
		string_copy s( "abc" );
		string_copy & r = s;

		cout << "s addr: " << &s << endl;
		cout << "r addr: " << &r << endl;

		cout << "to any." << endl;
		any a = &s;

		cout << "changing..." << endl;
		s.set( "def" );

		any b = a;

		try	{
			string_copy * c = any_cast<string_copy*>( b );
			cout << "c addr: " << c << endl;
			cout << c->get() << " has been casted." << endl;
			cout << "source is: " << s.get() << endl;
		} catch( const bad_any_cast & ) {
			cerr << "any cast failed." << endl;
		}
	}

private:

	class string_copy {
	public:
		string_copy( const string & s ) {
			cout << "construct" << endl;
			set( s );
		}
		string_copy( const string_copy & r ) {
			cout << "copy" << endl;
			set( r.s );
		}

		void set( const string & s ) {
			cout << "change" << endl;
			this->s = s;
		}

		string_copy & operator=( const string_copy& rhs ) {
			cout << "assign" << endl;
			set( rhs.s );
			return *this;
		}


		const string & get() const {
			return s;
		}

	private:
		string s;
	};

};
