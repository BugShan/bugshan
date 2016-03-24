#include <bugshan/reflection/Field.h>
#include <iostream>

using namespace BugShan::Reflection;

template<>
struct TypeDecl<int>
{
	inline static const char* const GetName()
	{
		return "int";
	}
};

class Test
{
public:
	char c;
	short s;
	int i;
};

template<typename T>
void Foo(Test* t, T fieldAddress)
{
	t->*fieldAddress = 11112323;
}

int main(void)
{
	std::cout << "test field" << std::endl;
	Field* field = new Field("i", &Test::i);
	Test* t = new Test;

	int value = 1213123;
	field->SetValue(t, &value);
	std::cout << t->i << std::endl;
	value = 43434;
	field->SetValue(t, &value);
	std::cout << t->i << std::endl;

	delete field;
	return 0;
}
