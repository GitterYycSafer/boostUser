#include "stdafx.h"
#include <boost\scoped_ptr.hpp>

struct Shoe 
{ 
	~Shoe() { std::cout << "Buckle my shoe\n"; } // ֤��scope_ptr �Զ�ִ��������
};

class MyClass 
{
	boost::scoped_ptr<int> ptr;
public:
	MyClass() : ptr(new int) { *ptr = 0; }	// �����ʼ������ָ��Ϊ0
	int add_one() { return ++*ptr; }
};

