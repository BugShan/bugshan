#include <bugshan/io/Directory.h>
#include <bugshan/io/File.h>
#include <dirent.h>
#include <sys/stat.h>

#include "Path.h"

namespace BugShan
{
	namespace IO
	{
		Directory::Directory(const char* const path)
			: mFullPathStr(path)
			, mDirNameStr(Path::GetDirNameStr(path))
		{ ; }
		Directory::Directory(const Directory& other)
			: mFullPathStr(other.mFullPathStr)
			, mDirNameStr(other.mDirNameStr)
		{ ; }
		Directory::~Directory(void)
		{ ; }

		const std::vector<File*> Directory::GetFiles(void) const
		{
			std::vector<File*> ret;
			DIR* dir = opendir(mFullPathStr.c_str());
			if(dir)
			{
				dirent* pdir = nullptr;
				struct stat statBuf;
				while(pdir = readdir(dir))
				{
					stat(pdir->d_name, &statBuf);
					if(S_ISREG(statBuf.st_mode))
						ret.push_back(new File(pdir->d_name));
				}
				closedir(dir);
			}
			return ret;
		}
		const std::vector<Directory*> Directory::GetDirectories(void) const
		{
			std::vector<Directory*> ret;
			DIR* dir = opendir(mFullPathStr.c_str());
			if(dir)
			{
				dirent* pdir = nullptr;
				struct stat statBuf;
				while(pdir = readdir(dir))
				{
					if(0 == strcmp(pdir->d_name, ".") || 0 == strcmp(pdir->d_name, ".."))
						continue;
					stat(pdir->d_name, &statBuf);
					if(S_ISDIR(statBuf.st_mode))
						ret.push_back(new Directory(pdir->d_name));
				}
				closedir(dir);
			}
			return ret;
		}
	};//namespace IO
};//namespace BugShan
