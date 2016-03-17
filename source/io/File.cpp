#include <bugshan/io/File.h>
#include <bugshan/io/Directory.h>
#include <bugshan/io/FileStream.h>
#include <sys/stat.h>

#include "Path.h"

namespace BugShan
{
	namespace IO
	{
		File::File(const char* const path)
			: mFullPathStr(path)
			, mFileNameStr(Path::GetFileNameStr(mFullPathStr))
			, mpFileStat(nullptr)
		{ ; }
		File::File(const File& other)
			: mFullPathStr(other.mFullPathStr)
			, mFileNameStr(other.mFileNameStr)
			, mpFileStat(nullptr)
		{ ; }
		File::~File(void)
		{
			if(mpFileStat)
				delete mpFileStat;
		}

		FileStream* File::GetStream(void) const
		{
			FileStream* ret = new FileStream(mFullPathStr.c_str());
			return ret;
		}

		Directory* File::GetDirectoryPtr(void) const
		{
			std::string dirPath = Path::GetDirPathStr(mFullPathStr);
			assert(!dirPath.empty());
			return new Directory(dirPath.c_str());
		}

		const uint64 File::GetSize(void) const
		{
			//struct stat* fileStat = GetFileStat();
			//assert(fileStat);
			//return fileStat->st_size;
			return 0;
		}


		struct stat* File::GetFileStat(void)
		{
			if(nullptr == mpFileStat)
			{
				mpFileStat = new struct stat;
				stat(mFullPathStr.c_str(), mpFileStat);
			}
			return mpFileStat;
		}
	};//namespace IO
};//namespace BugShan
