#ifndef	_BUGSHAN_REFLECTION_TYPE_H_
#define	_BUGSHAN_REFLECTION_TYPE_H_

#include <vector>

namespace BugShan
{
	namespace Reflection
	{
		class Field;
		class Method;
		class Type final
		{
		public:
			 /**
			  * The constructor.
			  * @param typeName: the name of this Type
			  */
			 Type(const char* const typeName);
			 /**
			  * The destructor.
			  */
			~Type(void);

		public:
			/**
			 * Get the name of this Type.
			 * @return: the pointer to char
			 */
			inline const char* const GetNamePtr(void) const;
			/**
			 * Get the Methods of this Type.
			 * @return: the vector of the Method pointer
			 */
			inline const std::vector<const Method* const>& GetMethodPtrVec(void) const;
			/**
			 * Get the Field of this Type.
			 * @return: the vector of the Field pointer
			 */
			inline const std::vector<const Field*  const>& GetFieldPtrVec(void)  const;

		public:
			/**
			 * Get the specified Method by one name.
			 * @param methodName: the name of the Method to find
			 * @return: if not found return null pointer
			 */
			const Method* const GetMethodPtr(const char* const methodName) const;
			/**
			 * Get the specified Field by one name.
			 * @param fieldName: the name of the Field to find
			 * @return: if not found return null pointer
			 */
			const Field*  const GetFieldPtr(const char* const fieldName ) const;

		private:
			const char* const					mpTypeName;
			//const char* const					mpBaseTypeName;
			std::vector<const Method* const>	mMethodPtrVec;
			std::vector<const Field*  const>	mFieldPtrVec;
			//std::vector<const char* const>		mTemplateArgTypeNameVec;
		};//class Type

		inline const char* const Type::GetNamePtr(void) const
		{ return this->mpTypeName; }
		inline const std::vector<const Method* const>& Type::GetMethodPtrVec(void) const
		{ return this->mMethodPtrVec; }
		inline const std::vector<const Field* const>& Type::GetFieldPtrVec(void) const
		{ return this->mFieldPtrVec; }
	};//namespace Reflection
};//namespace BugShan

#endif//_BUGSHAN_REFLECTION_TYPE_H_
