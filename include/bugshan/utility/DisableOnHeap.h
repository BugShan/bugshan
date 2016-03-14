#ifndef	_BUGSHAN_UTILITY_DISABLEONHEAP_H_
#define _BUGSHAN_UTILITY_DISABLEONHEAP_H_

#include <stddef.h>

namespace BugShan
{
	namespace Detail
	{
		struct DisableOnHeap
		{
		private:
			void* operator new(size_t)		= delete;
			void* operator new[](size_t)	= delete;
			void operator delete(void*)		= delete;
			void operator delete[](void*)	= delete;
		};//class DisableOnHeap
	};//namespace Detail
};//namespace BugShan

#endif//_BUGSHAN_UTILITY_DISABLEONHEAP_H_
