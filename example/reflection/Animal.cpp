#include "Animal.h" 

const std::string& Animal::GetNameStr(void) const
{
	return this->mNameStr;
}
const char* const Animal::GetNickNamePtr(void) const
{
	return this->mpNickNamePtr;
}
const int Animal::GetAge(void) const
{
	return this->mnAge;
}

TYPE_DECL(Animal);
FIELD_DECL(Animal, &Animal::mNameStr);
METHOD_DECL(Animal, &Animal::GetNameStr);
