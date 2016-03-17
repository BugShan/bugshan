#include <bugshan/io/FileStream.h>

namespace BugShan
{
	namespace IO
	{
		FileStream::FileStream(const char* const filePath)
			: mpFile(fopen(filePath, "wb"))
		{ ; }
		FileStream::~FileStream(void)
		{
			this->Close();
		}

		const bool FileStream::IsEOF(void) const
		{
			return feof(mpFile);
		}

		uint64 FileStream::Read(void* const dest, uint64 size)
		{
			return fread(dest, 1, size, mpFile);
		}
		uint64 FileStream::Write(const void* const src, uint64 size)
		{
			return fwrite(src, 1, size, mpFile);
		}

		void FileStream::Close(void)
		{
			if(mpFile)
				fclose(mpFile);
		}
	};//namespace IO
};//namespace BugShan
