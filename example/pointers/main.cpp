#include <bugshan/pointers/AutoPtr.h>
#include <iostream>

using namespace BugShan;

struct Test
{
	Test(void)
	{
		std::cout << "Test Constructor" << std::endl;
	}
	~Test(void)
	{
		std::cout << "Test Destructor" << std::endl;
	}
	int i;
};//struct Test
int main(void)
{
	AutoPtr<Test[]> tPtr(10);
	for(int i = 0; i < tPtr.GetSize(); ++ i)
	{
		tPtr[i].i = i;
	}
	for(int i = 0; i < tPtr.GetSize(); ++ i)
	{
		std::cout << tPtr[i].i << std::endl;
	}
	return 0;
}
