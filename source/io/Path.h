#ifndef	_BUGSHAN_IO_PATH_H_
#define	_BUGSHAN_IO_PATH_H_

#include <string>
#include <assert.h>

namespace BugShan
{
	namespace IO
	{
		class Path final
		{
		public:
			static const std::string GetFileNameStr(const std::string& fullPath);
			static const std::string GetDirPathStr(const std::string& fullPath);
			static const std::string GetDirNameStr(const std::string& fullPath);
			static const std::string GetExtensionStr(const std::string& fullPath);
		private:
			 Path(void)		= delete;
			~Path(void)		= delete;
		};//class Path
	};//namespace IO
};//namespace BugShan

#endif//_BUGSHAN_IO_PATH_H_
