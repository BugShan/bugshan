#ifndef	_BUGSHAN_POINTERS_PTR_H_
#define	_BUGSHAN_POINTERS_PTR_H_

#include <bugshan/utility/DisableOnHeap.h>
#include <assert.h>
namespace BugShan
{
	template<typename T>
	class Ptr : private Detail::DisableOnHeap
	{
	public:
		/**
		 * Get the pointer to the designated object
		 */
		inline T* const operator -> (void) const;
		/**
		 * Get the reference to designated object.
		 */
		inline T& operator *  (void) const;
		/**
		 * Check if nullptr
		 */
		inline operator const bool(void) const;
		/**
		 * The equality operation.
		 */
		inline const bool operator == (const Ptr&);
		/**
		 * The inequality operation.
		 */
		inline const bool operator != (const Ptr&);

	protected:
		inline Ptr(T*);
		/**
		 * Delete this pointer.
		 */
		inline void Delete(void);

	protected:
		T*						mpData;
	};//class ptr
	template<typename T>
	class Ptr<T[]> : private Detail::DisableOnHeap
	{
	public:
		/**
		 * Get the element at the specified pos.
		 */
		inline T& operator [] (const unsigned int index);
		/**
		 * Get the size of this array.
		 */
		inline const unsigned int GetSize(void) const;
		/**
		 * Check if nullptr
		 */
		inline operator const bool(void) const;
		/**
		 * The equality operation.
		 */
		inline const bool operator == (const Ptr&);
		/**
		 * The inequality operation.
		 */
		inline const bool operator != (const Ptr&);

	protected:
		inline Ptr(T*, const unsigned int);
		inline void Delete(void);

	protected:
		T*						mpData;
		unsigned int			muSize;
	};//class Ptr<T[]>

	template<typename T>
	inline T* const Ptr<T>::operator -> (void) const
	{
		return this->mpData;
	}
	template<typename T>
	inline T& Ptr<T>::operator *  (void) const
	{
		return *this->mpData;
	}
	template<typename T>
	inline Ptr<T>::operator const bool(void) const
	{
		return this->mpData;
	}
	template<typename T>
	inline const bool Ptr<T>::operator == (const Ptr& other)
	{
		return this->mpData == other.mpData;
	}
	template<typename T>
	inline const bool Ptr<T>::operator != (const Ptr& other)
	{
		return this->mpData != other.mpData;
	}
	template<typename T>
	inline Ptr<T>::Ptr(T* ptr)
		: mpData(ptr)
	{ ; }
	template<typename T>
	inline void Ptr<T>::Delete(void)
	{
		delete this->mpData;
		mpData = nullptr;
	}

	template<typename T>
	inline T& Ptr<T[]>::operator [] (const unsigned int index)
	{
		assert(index < muSize);
		return this->mpData[index];
	}
	template<typename T>
	inline const unsigned int Ptr<T[]>::GetSize() const
	{
		return this->muSize;
	}
	template<typename T>
	inline Ptr<T[]>::operator const bool(void) const
	{
		return this->mpData;
	}
	template<typename T>
	inline const bool Ptr<T[]>::operator == (const Ptr& other)
	{
		return this->mpData == other.mpData;
	}
	template<typename T>
	inline const bool Ptr<T[]>::operator != (const Ptr& other)
	{
		return this->mpData != other.mpData;
	}
	template<typename T>
	inline Ptr<T[]>::Ptr(T* ptr, const unsigned int size)
		: mpData(ptr)
		, muSize(size)
	{ ; }
	template<typename T>
	inline void Ptr<T[]>::Delete(void)
	{
		delete[] mpData;
		mpData = nullptr;
		muSize = 0;
	}
};//namespace BugShan
#endif//_BUGSHAN_POINTERS_PTR_H_
