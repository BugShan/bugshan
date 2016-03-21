#ifndef	_BUGSHAN_REFLECTION_FIELD_H_
#define	_BUGSHAN_REFLECTION_FIELD_H_

#include <bugshan/TypeDef.h>

namespace BugShan
{
	namespace Reflection
	{
		namespace detail
		{
			template<typename T>
			struct is_field : public std::false_type { ; };//struct is_field<T>
			template<typename Class, typename T>
			struct is_field<T(Class::*)> : public std::true_type { ; };//struct is_field<T(Class::*)>
		};//namespace detail

		class Type;
		class Field final
		{
		public:
			//template<typename T, typename = typename std::enable_if<!detail::is_field<T>::value>::type>
			//inline Field(const char* const fieldName, T fieldAddress);

			//template<typename Class, typename T, typename = typename std::enable_if<detail::is_field<T(Class::*)>::value>::type>
			//inline Field<T(Class::*)>(const char* const fieldName, T(Class::*) address);

			inline ~Field(void);

		public:
			inline const char* const GetNamePtr(void) const;

		public:
			const Type* GetTypePtr(void) const;
			void SetValue(const void* const object, const void* const value);
			void GetValue(void* ret, const void* const object);

		private:
			const char* const					mpFieldName;
			const char* const					mpTypeName;
			const uint							muOffset;
			const uint							muSize;
		};//class Field

		//template<typename T>
		//inline Field::Field(const char* const, T)
		//{
		//	//static_assert(false, "");
		//}
		inline Field::~Field(void)
		{ ; }

		inline const char* const Field::GetNamePtr(void) const
		{ return this->mpFieldName; }

		inline void Field::SetValue(const void* const object, const void* const value)
		{
			void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
			memcpy(address, value, muSize);
		}
		inline void Field::GetValue(void* ret, const void* const object)
		{
			void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
			memcpy(ret, address, muSize);
		}
	};//namespace Reflection
};//namespace BugShan

#endif//_BUGSHAN_REFLECTION_FIELD_H_
