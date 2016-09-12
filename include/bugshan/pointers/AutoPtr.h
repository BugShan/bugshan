#ifndef	_BUGSHAN_POINTERS_AUTOPTR_H_
#define	_BUGSHAN_POINTERS_AUTOPTR_H_

#include <bugshan/pointers/Ptr.h>
#include <bugshan/TypeDef.h>
#include <stdlib.h>

namespace BugShan
{
	template<typename T>
	class AutoPtr final : public Ptr<T>
	{
	public:
		template<typename... Args>
		inline AutoPtr(Args...);
		inline ~AutoPtr(void);

	private:
		AutoPtr(const AutoPtr&)					= delete;
		AutoPtr(const AutoPtr&&)				= delete;
		AutoPtr& operator = (const AutoPtr&)	= delete;
		AutoPtr& operator = (const AutoPtr&&)	= delete;
	};//class AutoPtr

	template<typename T>
	class AutoPtr<T[]> final : public Ptr<T[]>
	{
	public:
		inline AutoPtr(const unsigned int size);
		inline ~AutoPtr(void);

	private:
		AutoPtr(const AutoPtr&)					= delete;
		AutoPtr(const AutoPtr&&)				= delete;
		AutoPtr& operator = (const AutoPtr&)	= delete;
		AutoPtr& operator = (const AutoPtr&&)	= delete;
	};//class AutoPtr<T[]>

	template<typename T>
	template<typename... Args>
	inline AutoPtr<T>::AutoPtr(Args... args)
		: Ptr<T>(static_cast<T*>(malloc(sizeof(T))))
	{
		new(this->mpData) T(args...);
	}
	template<typename T>
	inline AutoPtr<T>::~AutoPtr(void)
	{
		Ptr<T>::Delete();
	}
	template<typename T>
	inline AutoPtr<T[]>::AutoPtr(const unsigned int size)
		: Ptr<T[]>(new T[size](), size)
	{ ; }
	template<typename T>
	inline AutoPtr<T[]>::~AutoPtr(void)
	{
		Ptr<T[]>::Delete();
	}
};//namespace BugShan
#endif//_BUGSHAN_POINTERS_AUTOPTR_H_
