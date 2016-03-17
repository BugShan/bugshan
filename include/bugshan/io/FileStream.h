#ifndef	_BUGSHAN_IO_FILESTREAM_H_
#define	_BUGSHAN_IO_FILESTREAM_H_

#include <bugshan/TypeDef.h>
#include <stdio.h>

namespace BugShan
{
	namespace IO
	{
		class FileStream final
		{
		public:
			 /**
			  * The constructor.
			  * @param filePath: the full path of this file
			  */
			 FileStream(const char* const filePath);
			/**
			 * The destructor.
			 */
			~FileStream(void);

		public:
			const bool IsEOF(void) const;
			/**
			 * Read file to buffer.
			 * @param dest: the buffer to read
			 * @param size: the size to read
			 * @return: the real size of the buffer to read from file
			 */
			uint64 Read(void* const dest, uint64 size);
			/**
			 * Write buffer to file.
			 * @param src:  the buffer write from
			 * @param size: the size to write
			 * @return: the real size of the buffer wrote to file
			 */
			uint64 Write(const void* const src, uint64 size);
			/**
			 * Close the stream.
			 */
			void Close(void);

		private:
			FILE*							mpFile;
		};//class FileStream
	};//namespace IO
};//namespace BugShan

#endif//_BUGSHAN_IO_FILESTREAM_H_
