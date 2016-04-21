#ifndef	_BUGSHAN_POINTERS_REFPTR_H_
#define	_BUGSHAN_POINTERS_REFPTR_H_

#include <bugshan/TypeDef.h>
#include <bugshan/utility/DisableOnHeap.h>

#include <stdlib.h>
#include <type_traits>

namespace BugShan
{
	template<typename T, typename RefTy = uint>
	class RefPtr final : private Detail::DisableOnHeap
	{
	public:
		/**
		 * The paramterless constructor.
		 */
		inline RefPtr(void);
		/**
		 * The copy constructor.
		 */
		inline RefPtr(const RefPtr&);
		/**
		 * The destructor.
		 */
		inline ~RefPtr(void);

		/**
		 * The assignment operator overload.
		 */
		inline RefPtr& operator = (const RefPtr&);

		/**
		 * Pass the multi template arguments to the constructor of type(T) directly.
		 * @return: new RefPtr.
		 */
		template<typename... Args>
		inline static RefPtr<T, RefTy> Create(Args...);

	public:
		/**
		 * Get the total reference count.
		 */
		inline const uint GetRefCount(void) const;
		/**
		 * Release the data[refCount = 0].
		 */
		inline void Release(void);

		template<typename _Ty, typename _RefTy>
		friend class RefPtr;
		template<typename CastTy, typename = typename std::enable_if<std::is_base_of<T, CastTy>::value || std::is_base_of<CastTy, T>::value>::type>
		inline RefPtr<CastTy> CastPtr(void);

	public:
		/**
		 * Check if nullptr.
		 */
		inline operator const bool(void) const;
		/**
		 * Get the pointer to the designated object.
		 */
		inline T* operator -> (void) const;
		/**
		 * Get the reference to designated object.
		 */
		inline T& operator *  (void) const;
		/**
		 * The equality operation;
		 */
		inline const bool operator == (const RefPtr) const;
		/**
		 * The inequality operation.
		 */
		inline const bool operator != (const RefPtr) const;

	private:
		inline void IncreaseRefCount(void);
		inline void DecreaseRefCount(void);
		inline void FreeData(void);
	private:
		T*			mpData;
		RefTy*		mpRefCount;
	};//class RefPtr

	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>::RefPtr(void)
		: mpData(nullptr)
		, mpRefCount(nullptr)
	{ ; }
	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>::RefPtr(const RefPtr<T, RefTy>& other)
		: mpData(other.mpData)
		, mpRefCount(other.mpRefCount)
	{
		IncreaseRefCount();
	}
	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>::~RefPtr(void)
	{
		if(nullptr == mpData) return;
		DecreaseRefCount();
		if(*mpRefCount <= 0) this->FreeData();
	}
	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>& RefPtr<T, RefTy>::operator = (const RefPtr& other)
	{
		if(mpData)
		{
			DecreaseRefCount();
			if(*mpRefCount <= 0) this->FreeData();
		}
		mpData		= other.mpData;
		mpRefCount	= other.mpRefCount;
		IncreaseRefCount();
		return *this;
	}
	template<typename T, typename RefTy>
	template<typename... Args>
	inline RefPtr<T, RefTy> RefPtr<T, RefTy>::Create(Args... args)
	{
		RefPtr<T, RefTy> ret;
		void* address = malloc(sizeof(T) + sizeof(*(ret.mpRefCount)));
		ret.mpData = (T*)(address);
		new(ret.mpData) T(args...);
		ret.mpRefCount = (uint*)((char*)address + sizeof(*(ret.mpRefCount)));
		new(ret.mpRefCount) RefTy(1);
		return ret;
	}

	template<typename T, typename RefTy>
	inline const uint RefPtr<T, RefTy>::GetRefCount(void) const
	{
		return *(this->mpRefCount);
	}

	template<typename T, typename RefTy>
	inline void RefPtr<T, RefTy>::Release(void)
	{
		this->FreeData();
		mpRefCount = 0;
	}
	template<typename T, typename RefTy>
	template<typename CastTy, typename /*= typename std::enable_if<std::is_base_of<T, CastTy>::value || std::is_base_of<CastTy, T>::value>::type*/>
	inline RefPtr<CastTy> RefPtr<T, RefTy>::CastPtr(void)
	{
		RefPtr<CastTy> ret;
		ret.mpData		= static_cast<CastTy*>(this->mpData);
		ret.mpRefCount	= this->mpRefCount;
		IncreaseRefCount();
	}

	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>::operator const bool(void) const
	{
		return mpData > 0;
	}
	template<typename T, typename RefTy>
	inline T* RefPtr<T, RefTy>::operator -> (void) const
	{
		return this->mpData;
	}
	template<typename T, typename RefTy>
	inline T& RefPtr<T, RefTy>::operator * (void) const
	{
		return *(this->mpData);
	}
	template<typename T, typename RefTy>
	inline const bool RefPtr<T, RefTy>::operator == (const RefPtr other) const
	{
		return this->mpData == other.mpData;
	}
	template<typename T, typename RefTy>
	inline const bool RefPtr<T, RefTy>::operator != (const RefPtr other) const
	{
		return this->mpData != other.mpData;
	}

	template<typename T, typename RefTy>
	inline void RefPtr<T, RefTy>::IncreaseRefCount(void)
	{
		(*mpRefCount) ++;
	}
	template<typename T, typename RefTy>
	inline void RefPtr<T, RefTy>::DecreaseRefCount(void)
	{
		(*mpRefCount) --;
	}
	template<typename T, typename RefTy>
	inline void RefPtr<T, RefTy>::FreeData(void)
	{
		mpData->~T();
		free(mpData);
		mpData = nullptr;
	}
};//namespace BugShan

#endif//_BUGSHAN_POINTERS_REFPTR_H_
