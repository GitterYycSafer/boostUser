#include "stdafx.h"
#include <boost\scoped_ptr.hpp>

struct Shoe 
{ 
	~Shoe() { std::cout << "Buckle my shoe\n"; } // 证明scope_ptr 自动执行了析构
};

class MyClass 
{
	boost::scoped_ptr<int> ptr;
public:
	MyClass() : ptr(new int) { *ptr = 0; }	// 构造初始化智能指针为0
	int add_one() { return ++*ptr; }
};

