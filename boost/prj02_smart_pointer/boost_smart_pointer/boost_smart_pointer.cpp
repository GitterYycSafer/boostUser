// boost_smart_pointer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "studyForScoperPtr.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// using for scope_ptr list 01
	boost::scoped_ptr<Shoe> x(new Shoe);

	MyClass my_instance;
	my_instance .add_one();
	my_instance .add_one();

	return 0;
}

