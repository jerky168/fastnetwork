#pragma once

class test_fixture
{
public:
	test_fixture(void);
	virtual ~test_fixture(void);

	virtual void test() = 0;
};
