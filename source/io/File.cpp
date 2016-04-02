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
		File::File(const char* const path)
			: mFullPathStr(path)
			, mFileNameStr(Path::GetFileNameStr(mFullPathStr))
			, mpFileStat(new struct stat)
		{
			stat(mFullPathStr.c_str(), mpFileStat);
		}
		File::File(const File& other)
			: mFullPathStr(other.mFullPathStr)
			, mFileNameStr(other.mFileNameStr)
			, mpFileStat(new struct stat)
		{
			stat(mFullPathStr.c_str(), mpFileStat);
		}
		File::~File(void)
		{
			if(mpFileStat)
				delete mpFileStat;
		}

		FileStream File::GetStream(void) const
		{
			return FileStream(mFullPathStr.c_str());
		}

		Directory* File::GetDirectoryPtr(void) const
		{
			std::string dirPath = Path::GetDirPathStr(mFullPathStr);
			assert(!dirPath.empty());
			return new Directory(dirPath.c_str());
		}

		const uint64 File::GetSize(void) const
		{
			return mpFileStat->st_size;
		}

		void File::Create(const char* const path)
		{
			FILE* file = fopen(path, "wb");
			fclose(file);
		}
		void File::Delete(const char* const path)
		{
			remove(path);
		}
		void File::Copy(const char* const from, const char* const to)
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

		void File::Move(const char* const from, const char* const to)
		{
			rename(from, to);
		}
	};//namespace IO
};//namespace BugShan
