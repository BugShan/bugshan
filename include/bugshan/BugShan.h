#ifndef _BUGSHAN_BUGSHAN_H_
#define _BUGSHAN_BUGSHAN_H_

#define	NULLPTR		0
#define NULL		0
/**
 * Returns value with bit x set (2^x)
 */
#define BIT(x) (1 << (x))

namespace BugShan
{
	/**
	 * safe delete pointer
	 * @param ptr: the poiter to delete, and ptr will be assigned to NULLPTR
	 */
	template<typename T>
	inline void Delete(T*& ptr)
	{
		if(ptr)
		{
			delete ptr;
			ptr = NULLPTR;
		}
	}
	/**
	 * safe delete array pointer
	 * @param ptr: the poiter to delete, and ptr will be assigned to NULLPTR
	 */
	template<typename T>
	inline void DeleteArr(T*& ptr)
	{
		if(ptr)
		{
			delete[] ptr;
			ptr = NULLPTR;
		}
	}
};//namespace BugShan
#endif//_BUGSHAN_BUGSHAN_H_
