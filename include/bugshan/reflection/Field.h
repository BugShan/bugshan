#ifndef	_BUGSHAN_REFLECTION_FIELD_H_
#define	_BUGSHAN_REFLECTION_FIELD_H_

#include <bugshan/TypeDef.h>
#include <bugshan/reflection/TypeDecl.h>
#include <type_traits>
#include <string>

namespace BugShan
{
	namespace Reflection
	{
		namespace detail
		{
			template<typename T>
			struct field_trait;//struct field_trait
			template<typename Class, typename T>
			struct field_trait<T(Class::*)>
			{
				using field_type = T;
				using class_type = Class;
			};//struct field_Trait<T(Class::*)>
		};//namespace detail

		class Type;
		class Field final
		{
		public:
			/**
			 * The constructor.
			 * @param fieldName:	the name of this field
			 * @param fieldAddress:	the pointer to this field
			 */
			template<typename T, typename ClassType = typename detail::field_trait<T>::class_type, typename FieldType = typename detail::field_trait<T>::field_type>
			inline Field(const char* const fieldName, const T fieldAddress);
			/**
			 * The destructor.
			 */
			inline ~Field(void);

		public:
			/**
			 * Get the name of this field.
			 */
			inline const char* const GetNamePtr(void) const;

		public:
			/**
			 * Get the type of this field
			 */
			const Type* GetTypePtr(void) const;
			/**
			 * Set the value to this field of one object[ClassType].
			 * @param object: pass the object
			 * @param value:  pass the value of this field.
			 */
			void SetValue(const void* const object, const void* const value);
			/**
			 * Get the value from this field of one object[ClassType].
			 * @param ret:	  where the value write to
			 * @param object: pass the object
			 */
			void GetValue(void* ret, const void* const object);

		private:
			const char* const					mpFieldName;
			const char* const					mpTypeName;
			const uint							muOffset;
			const uint							muSize;
		};//class Field
		
		template<typename T, typename ClassType, typename FieldType>
		inline Field::Field(const char* const fieldName, const T fieldAddress)
			: mpFieldName(fieldName)
			, mpTypeName(TypeDecl<FieldType>::GetName())
			, muOffset((size_t)(&((ClassType*)0->*fieldAddress)))
			, muSize(sizeof(FieldType))
		{ ; }

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
