#ifndef	_BUGSHAN_IO_DIRECTORY_H_
#define	_BUGSHAN_IO_DIRECTORY_H_

#include <string>
#include <vector>

namespace BugShan
{
	namespace IO
	{
		class File;
		class Directory final
		{
		public:
			 /**
			  * The constructor.
			  * @param path: the full path of this File
			  */
			 Directory(const char* const path);
			 /**
			  * The copy constructor.
			  * @param other: the other file
			  */
			 Directory(const Directory& other);
			 /**
			  * The destructor.
			  */
			~Directory(void);

		public:
			/**
			 * The equal operator overload.
			 */
			inline const bool operator ==(const Directory& other) const;
			inline const bool operator !=(const Directory& other) const;

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
			 * List the files from this directory.
			 */
			const std::vector<File*> GetFiles(void) const;
			/**
			 * List the directories from this directory.
			 */
			const std::vector<Directory*> GetDirectories(void) const;
			/**
			 * Get the parent directory of this directory.
			 */
			Directory* GetParentDirectoryPtr(void) const;

		private:
			/**
			 * The assignment operator overload.
			 * @param other: the other file
			 */
			Directory& operator=(const Directory& other)		= delete;

		private:
			std::string				mFullPathStr;
			std::string				mDirNameStr;
		};//class Directory

		inline const bool Directory::operator ==(const Directory& other) const
		{
			return this->mFullPathStr == other.mFullPathStr;
		}
		inline const bool Directory::operator !=(const Directory& other) const
		{
			return this->mFullPathStr != other.mFullPathStr;
		}

		inline const std::string& Directory::GetName(void) const
		{
			return this->mDirNameStr;
		}
		inline const std::string& Directory::GetFullPath(void) const
		{
			return this->mFullPathStr;
		}
	};//namespace IO
};//namespace BugShan

#endif//_BUGSHAN_IO_DIRECTORY_H_
