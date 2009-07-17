#pragma once
#include "test_fixture.h"

class base_interface {
public:
	base_interface() {
		cout << "base interface created." << endl;
	}
	~base_interface() {
		cout << "base interface destroyed." << endl;
	}

	virtual void show() = 0;
};

class base_class;

typedef shared_ptr<base_class> base_class_ptr;

class base_class_user {
public:
	void show( base_class_ptr b );
};

typedef shared_ptr<base_class_user> user_ptr;

class base_class : public base_interface, public enable_shared_from_this<base_class> {
public:
	base_class() {
		cout << "base class created." << endl;
	}
	~base_class() {
		cout << "base class destroyed." << endl;
	}

	virtual void show_a() = 0;
	virtual void show() {
		cout << "this is base class." << endl;
	}
};

class derived_class : public base_class {
public:
	derived_class() {
		cout << "derived class created." << endl;
	}
	~derived_class() {
		cout << "derived class destroyed." << endl;
	}

	virtual void show() {
		cout << "this is derived class." << endl;
	}

	virtual void show_a() {
		user_ptr user( new base_class_user() );
		user->show(shared_from_this());
	}
};



class test_shared_ptr :
	public test_fixture
{
public:
	test_shared_ptr(void);
	~test_shared_ptr(void);

public:
	void test() {
		shared_ptr<base_class> d( new derived_class() );
		d->show_a();
	}
};
