#ifndef	_BUGSHAN_REFLECTION_RUNTIME_H_
#define	_BUGSHAN_REFLECTION_RUNTIME_H_

#include <bugshan/reflection/TypeDecl.h>

#include <vector>

namespace BugShan
{
	namespace Reflection
	{
		class Type;
		class Field;
		class Method;
		class Runtime final
		{
		public:
			static const Type* const GetType(const char* const typeName);
			static void DeclareType(const IType* const type);

		private:
			 Runtime(void)			= delete;
			~Runtime(void)			= delete;

		private:
			static std::vector<const IType* const>			sTypeMap;
		};//class Runtime
	};//namespace Reflection
};//namespace BugShan

#endif//_BUGSHAN_REFLECTION_RUNTIME_H_
