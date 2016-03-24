#ifndef	_BUGSHAN_EXAMPLE_REFLECTION_PERSON_H_
#define	_BUGSHAN_EXAMPLE_REFLECTION_PERSON_H_

#include <string>

class Animal
{
public:
	const std::string& GetNameStr(void) const;
	const char* const GetNickNamePtr(void) const;
	const int GetAge(void);
	virtual void Run(void);
private:
	std::string				mNameStr;
	char*					mpNickNamePtr;
	int						mnAge;
};//class Animal

#endif//_BUGSHAN_EXAMPLE_REFLECTION_PERSON_H_
