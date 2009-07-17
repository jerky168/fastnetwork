#include "StdAfx.h"
#include "test_shared_ptr.h"

test_shared_ptr::test_shared_ptr(void)
{
}

test_shared_ptr::~test_shared_ptr(void)
{
}

void base_class_user::show( base_class_ptr b )
{
	b->show();
}