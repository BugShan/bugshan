#include <bugshan/io/File.h>
#include <bugshan/io/Directory.h>
#include <bugshan/io/FileStream.h>
#include <sys/stat.h>
#include <stdio.h>

#include "Path.h"

namespace BugShan
{
	namespace IO
	{
		/*static*/const bool File::Exist(const std::string& path)
		{
			struct stat fileStat;
			return stat(path.c_str(), &fileStat);
		}
		/*static*/void File::Create(const std::string& path)
		{
			FILE* file = fopen(path.c_str(), "wb");
			fclose(file);
		}
		/*static*/void File::Delete(const std::string& path)
		{
			remove(path.c_str());
		}
		/*static*/void File::Copy(const std::string& from, const std::string& to)
		{
			FileStream reader(from);
			FileStream writer(to);
			const unsigned int size = 1024;
			unsigned char buffer[size];
			while(!reader.IsEOF())
			{
				int bytes = reader.Read(buffer, size);
				writer.Write(buffer, bytes);
			}
			reader.Close();
			writer.Close();
		}
		/*static*/void File::Move(const std::string& from, const std::string& to)
		{
			rename(from.c_str(), to.c_str());
		}

		File::File(const std::string& path)
			: mFullPathStr(path)
			, mFileNameStr(Path::GetFileNameStr(mFullPathStr))
		{
		}
		File::File(const File& other)
			: mFullPathStr(other.mFullPathStr)
			, mFileNameStr(other.mFileNameStr)
		{
		}
		File::~File(void)
		{ ; }

		FileStream File::GetStream(void) const
		{
			return FileStream(mFullPathStr.c_str());
		}

		Directory File::GetDirectory(void) const
		{
			std::string dirPath = Path::GetDirPathStr(mFullPathStr);
			assert(!dirPath.empty());
			return Directory(dirPath.c_str());
		}

		const uint64 File::GetSize(void) const
		{
			struct stat fileStat;
			stat(mFullPathStr.c_str(), &fileStat);
			return fileStat.st_size;
		}
	};//namespace IO
};//namespace BugShan
