// cheat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "test_bind.h"
#include "test_any.h"
#include "test_shared_ptr.h"

class Test { 
public: 
	Test( long inVal ) : mVal( inVal ){} 
	long TimesOne() const { return mVal; }
	long TimesTwo() const { return mVal * mVal; }
	long TimesThree() const { return mVal * mVal * mVal; } 
private: long mVal; 
}; 

typedef long (Test::*Multiplier)() const;


class TEST {
private:

typedef void (TEST::*f1)(int);
typedef void (TEST::*f2)(int, int);

public:
	void show( int i ) {
		cout << i << endl;
	}

	void add( int i, int j ) {
		cout << i + j << endl;
	}

public:
	void test() {
		f1 a1= &TEST::show;
		f2 a2= &TEST::add;

		
		(this->*a1)( 3 );
		(this->*a2)( 3, 6 );
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	//wstring ws(L"abc");
	//size_t size = wcstombs( NULL, ws.c_str(), 0 );

	//size_t buffer_size = size + 1;
	//scoped_array<char> buffer( new char[buffer_size] );
	//size = wcstombs(buffer.get(), ws.c_str(), buffer_size);
	//cout << size << endl;

	TEST t;
	t.test();


	//test_fixture * t = new test_shared_ptr();
	//t->test();

	//delete t;

	cin.get();
	return 0;
}

