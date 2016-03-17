#include <bugshan/io/FileStream.h>

namespace BugShan
{
	namespace IO
	{
		FileStream::FileStream(const char* const filePath)
			: mpFile(fopen(filePath, "rw"))
			, muOffset(0)
		{ ; }
		FileStream::~FileStream(void)
		{
			this->Close();
		}

		uint64 FileStream::Read(void* const dest, uint64 size)
		{
			fseek(mpFile, muOffset, SEEK_SET);
			muOffset += size;
			return fread(dest, 1, size, mpFile);
		}
		uint64 FileStream::Write(const void* const src, uint64 size)
		{
			fseek(mpFile, muOffset, SEEK_SET);
			muOffset += size;
			return fwrite(src, 1, size, mpFile);
		}

		void FileStream::Close(void)
		{
			if(mpFile)
				fclose(mpFile);
		}
	};//namespace IO
};//namespace BugShan
