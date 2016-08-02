#ifndef	_BUGSHAN_UTILITY_SINGLETON_H_
#define	_BUGSHAN_UTILITY_SINGLETON_H_

namespace BugShan
{
	template<typename T>
	class Singleton
	{
	public:
		inline static T& GetMe(void);
		inline static T* GetMePtr(void);
	};//class Singleton

	template<typename T>
	inline T& Singleton<T>::GetMe(void)
	{
		return *GetMePtr();
	}
	template<typename T>
	inline T* Singleton<T>::GetMePtr(void)
	{
		static T* spMyself = new T();
		return spMyself;
	}
};//namespace BugShan
#endif//_BUGSHAN_UTILITY_SINGLETON_H_
