#ifndef	_BUGSHAN_POINTERS_REFPTR_H_
#define	_BUGSHAN_POINTERS_REFPTR_H_

#include <bugshan/TypeDef.h>
#include <bugshan/utility/DisableOnHeap.h>

#include <stdlib.h>
#include <memory.h>
#include <type_traits>

namespace BugShan
{
	template<typename T, typename RefTy = uint>
	class RefPtr final : private Detail::DisableOnHeap
	{
	public:
		/**
		 * Point to null.
		 */
		static RefPtr NullPtr(void);
		/**
		 * Create RefPtr from a original pointer and take the ownership.
		 */
		static RefPtr Own(const T* const ptr);
	public:
		/**
		 * Pass the multi template arguments to the constructor of type(T) directly.
		 */
		template<typename... Args>
		inline RefPtr(Args...);
		/**
		 * The copy constructor.
		 */
		inline RefPtr(const RefPtr& other);
		/**
		 * The destructor.
		 */
		inline ~RefPtr(void);

		/**
		 * The assignment operator overload.
		 * @param other: the l-value reference.
		 */
		inline RefPtr& operator = (const RefPtr& other);
		/**
		 * The assignment operator overload.
		 * @param other: the r-value reference.
		 */
		inline RefPtr& operator = (RefPtr&& other);

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
	inline /*static*/ RefPtr<T, RefTy> RefPtr<T, RefTy>::NullPtr(void)
	{
		const unsigned size = sizeof(RefPtr<T, RefTy>);
		unsigned char block[size];
		memset(block, 0, sizeof(block));
		return *((RefPtr<T, RefTy>*)block);
	}
	template<typename T, typename RefTy>
	inline /*static*/ RefPtr<T, RefTy> RefPtr<T, RefTy>::Own(const T* const ptr)
	{
		RefPtr<T, RefTy> ret = RefPtr::NullPtr();

		void* address = realloc((void*)ptr, sizeof(T) + sizeof(RefTy));
		ret.mpData = (T*)address;
		ret.mpRefCount = (RefTy*)((char*)address + sizeof(T));
		new(ret.mpRefCount) RefTy(1);
		return ret;
	}


	template<typename T, typename RefTy>
	template<typename... Args>
	inline RefPtr<T, RefTy>::RefPtr(Args... args)
		: mpData(nullptr)
		, mpRefCount(nullptr)
	{
		void* address = malloc(sizeof(T) + sizeof(RefTy));
		this->mpData = (T*)(address);
		new(this->mpData) T(args...);
		this->mpRefCount = (RefTy*)((char*)address + sizeof(T));
		new(this->mpRefCount) RefTy(1);
	}

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
			this->DecreaseRefCount();
			if(GetRefCount() <= 0) this->FreeData();
		}
		this->mpData		= other.mpData;
		this->mpRefCount	= other.mpRefCount;
		this->IncreaseRefCount();
		return *this;
	}
	template<typename T, typename RefTy>
	inline RefPtr<T, RefTy>& RefPtr<T, RefTy>::operator = (RefPtr&& other)
	{
		std::swap(this->mpData,		other.mpData);
		std::swap(this->mpRefCount,	other.mpRefCount);
		return *this;
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
		RefPtr<CastTy, RefTy> ret = RefPtr<CastTy, RefTy>::NullPtr();
		ret.mpData		= static_cast<CastTy*>(this->mpData);
		ret.mpRefCount	= this->mpRefCount;
		IncreaseRefCount();
		return ret;
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
		if(mpRefCount)
			(*mpRefCount) ++;
	}
	template<typename T, typename RefTy>
	inline void RefPtr<T, RefTy>::DecreaseRefCount(void)
	{
		if(mpRefCount)
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
