#include <bugshan/io/Directory.h>
#include <bugshan/io/File.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include "Path.h"

namespace BugShan
{
	namespace IO
	{
		/*static*/const bool Directory::Exist(const std::string& path)
		{
			struct stat fileStat;
			return stat(path.c_str(), &fileStat);
		}
		/*static*/void Directory::Create(const std::string& path)
		{
			::mkdir(path.c_str(), S_IRWXU | S_IRWXO);
		}
		/*static*/void Directory::Delete(const std::string& path)
		{
			::remove(path.c_str());
		}
		/*static*/void Directory::Copy(const std::string& from, const std::string& to)
		{
		}
		/*static*/void Directory::Move(const std::string& from, const std::string& to)
		{
			rename(from.c_str(), to.c_str());
		}

		Directory::Directory(const std::string& path)
			: mFullPathStr(path)
			, mDirNameStr(Path::GetDirNameStr(path))
		{ ; }
		Directory::Directory(const Directory& other)
			: mFullPathStr(other.mFullPathStr)
			, mDirNameStr(other.mDirNameStr)
		{ ; }
		Directory::~Directory(void)
		{ ; }

		const std::vector<File> Directory::GetFiles(void) const
		{
			std::vector<File> ret;
			DIR* dir = opendir(mFullPathStr.c_str());
			char pathBuffer[1028];
			auto len = strlen(mFullPathStr.c_str());
			memcpy(pathBuffer, mFullPathStr.c_str(), len);
			pathBuffer[len] = '/';
			if(dir)
			{
				dirent* pdir = nullptr;
				struct stat statBuf;
				while(pdir = readdir(dir))
				{
					memcpy(pathBuffer + len + 1, pdir->d_name, pdir->d_namlen + 1);
					stat(pathBuffer, &statBuf);
					if(S_ISREG(statBuf.st_mode))
						ret.push_back(File(pathBuffer));
				}
				closedir(dir);
			}
			return ret;
		}
		const std::vector<Directory> Directory::GetDirectories(void) const
		{
			std::vector<Directory> ret;
			DIR* dir = opendir(mFullPathStr.c_str());
			if(dir)
			{
				dirent* pdir = nullptr;
				struct stat statBuf;
				char pathBuffer[1028];
				auto len = strlen(mFullPathStr.c_str());
				memcpy(pathBuffer, mFullPathStr.c_str(), len);
				pathBuffer[len] = '/';
				while(pdir = readdir(dir))
				{
					if(0 == strcmp(pdir->d_name, ".") || 0 == strcmp(pdir->d_name, ".."))
						continue;
					memcpy(pathBuffer + len + 1, pdir->d_name, pdir->d_namlen + 1);
					stat(pathBuffer, &statBuf);
					if(S_ISDIR(statBuf.st_mode))
						ret.push_back(Directory(pathBuffer));
				}
				closedir(dir);
			}
			return ret;
		}
		Directory Directory::GetParentDirectory(void) const
		{
		   std::string dirPath = Path::GetDirPathStr(mFullPathStr);
		   assert(!dirPath.empty());
		   return Directory(dirPath.c_str());
		}
	};//namespace IO
};//namespace BugShan
