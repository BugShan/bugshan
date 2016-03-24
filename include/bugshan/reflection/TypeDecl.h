#ifndef	_BUGSHAN_REFLECTION_TYPEDECL_H_
#define	_BUGSHAN_REFLECTION_TYPEDECL_H_


#include "Type.h"
#include "Field.h"
#include "Method.h"
#include <bugshan/utility/AutoRunHelper.h>
#include <assert.h>

namespace BugShan
{
	namespace Reflection
	{
		template<typename T>
		struct TypeDecl final
		{
			const char* const			name = nullptr;
		};//struct TypeDecl

		/*
		template<typename T>
		class TypeDecl final
		{
		public:
			 TypeDecl(const char* const typeName);
			~TypeDecl(void);

			template<typename BaseTy>
			TypeDecl& BaseType(BaseTy baseType);

			template<typename FieldTy>
			TypeDecl& Field(const char* const fieldName, FieldTy fieldAddress);

			template<typename MethodTy>
			TypeDecl& Method(const char* const fieldName, MethodTy methodAddress);

		protected:
			void DeclType_Imp(void);

		private:
			Type*					mpType;
		};//class TypeDecl
		
		template<typename T>
		TypeDecl::TypeDecl(const char* const typeName)
			: mpType(typeName)
		{
			assert(mpType);
			::BugShan::Runtime::DeclareType(mpType);
			this->DeclType_Imp(void);
		}
		template<typename T>
		TypeDecl::~TypeDecl(void)
		{ ; }

		template<typename T>
		template<typename BaseTy>
		TypeDecl& TypeDecl::BaseType(void)
		{
			const char* const typeName = TypeDecl<BaseTy>::GetTypeName();
			return *this;
		}

		template<typename T>
		template<typename FieldTy>
		TypeDecl& TypeDecl::Field(const char* const fieldName, FieldTy fieldAddress)
		{
			Field* field = new Field(fieldName, fieldAddress);
			mpType->AddMethod(field);
			return *this;
		}
		*/
	};//namespace Reflection
};//namespace BugShan

#define TYPE_DECL(type)							\
	template<>									\
	struct TypeDecl<type>						\
	{											\
		inline const char* const GetName(void)	\
		{										\
			return ##type;						\
		}										\
	};//struct TypeDecl<type>

/*
#define TYPE_DECL(type)							\
	Detail::AutoRunHelper type##auto_decl;		\
	Detail::AutoRunHelper::AutoRunHelper(void)

#define TYPE_DECL_ARGS(_1, _2, _3, _4, _5, N) N
#define TYPE_DECL_1(type)
#define TYPE_DECL_2(type, name)
#define TYPE_DECL(...) TYPE_DECL_ARGS((__VA_ARGS__), TYPE_DECL_2, TYPE_DECL_1)(__VA_ARGS__)
*/


#endif//_BUGSHAN_REFLECTION_TYPEDECL_H_
