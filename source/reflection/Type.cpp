#include <bugshan/reflection/Type.h>
#include <bugshan/reflection/Field.h>
#include <bugshan/reflection/Method.h>

namespace BugShan
{
	namespace Reflection
	{
		Type::Type(const char* const typeName)
			: mpTypeName(typeName)
			, mFieldPtrVec()
			, mMethodPtrVec()
		{ ; }
		Type::~Type(void)
		{
			for(auto fieldPtr : mFieldPtrVec)
				delete fieldPtr;
			for(auto methodPtr : mMethodPtrVec)
				delete methodPtr;
		}
		const Field* const Type::GetFieldPtr(const char* const fieldName) const
		{
			for(auto f : mFieldPtrVec)
				if(0 == strcmp(f->GetNamePtr(), fieldName))
					return f;
			return nullptr;
		}
		const Method* const Type::GetMethodPtr(const char* const methodName) const
		{
			for(auto m : mMethodPtrVec)
				if(0 == strcmp(m->GetNamePtr(), methodName))
					return m;
			return nullptr;
		}
	};//namespace Reflection
};//namespace BugShan
