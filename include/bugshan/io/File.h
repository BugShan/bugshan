#ifndef	_BUGSHAN_IO_FILE_H_
#define	_BUGSHAN_IO_FILE_H_

#include <bugshan/TypeDef.h>
#include <string>
#include <vector>

struct stat;
namespace BugShan
{
	namespace IO
	{
		class Directory;
		class FileStream;
		class File final
		{
		public:
			 /**
			  * The constructor.
			  * @param path: the full path of this File.
			  */
			 File(const char* const path);
			 /**
			  * The copy constructor.
			  * @param other: the other file
			  */
			 File(const File& other);
			 /**
			  * The destructor.
			  */
			~File(void);

		public:
			/**
			 * The equal operator overload.
			 */
			inline const bool operator ==(const File& other) const;
			inline const bool operator !=(const File& other) const;

		public:
			/**
			 * Get the name of this file.
			 */
			inline const std::string& GetName(void) const;
			/**
			 * Get the full path of this file.
			 */
			inline const std::string& GetFullPath(void) const;

		public:
			/**
			 * Get the file stream.
			 */
			FileStream* GetStream(void) const;
			/**
			 * Get the directory information of this file.
			 */
			Directory*	GetDirectoryPtr(void) const;
			/**
			 * Get the size of this file.
			 */
			const uint64 GetSize(void) const;

		public:
			/**
			 * Create a specified file.
			 * @param path: the path of the file to create
			 */
			static void Create(const char* const path);
			/**
			 * Delete a specified file.
			 * @param path: the path of the file to delete.
			 */
			static void Delete(const char* const path);
			/**
			 * Copy the file to another path.
			 * @param from: the src path of the file copied from
			 * @param to:   the dest path of the file copied to
			 */
			static void Copy(const char* const from, const char* const to);
			/**
			 * Move the file to another path.
			 * @param from: the src path of the file copied from
			 * @param to:   the dest path of the file copied to
			 */
			static void Move(const char* const from, const char* const to);

		private:
			/**
			 * The assignment operator overload.
			 * @param other: the other file
			 */
			File& operator = (const File& other)		= delete;

		private:
			const std::string			mFullPathStr;
			const std::string			mFileNameStr;
			stat*						mpFileStat;
		};//class File

		inline const bool File::operator ==(const File& other) const
		{
			return this->mFullPathStr == other.mFullPathStr;
		}
		inline const bool File::operator !=(const File& other) const
		{
			return this->mFullPathStr != other.mFullPathStr;
		}

		inline const std::string& File::GetName(void) const
		{
			return mFileNameStr;
		}
		inline const std::string& File::GetFullPath(void) const
		{
			return mFullPathStr;
		}
	};//namespace IO
};//namespace BugShan
#endif//_BUGSHAN_IO_FILE_H_
