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
			 * Check if the directory exist or not.
			 */
			static const bool Exist(const std::string& path);
			/**
			 * Create a specified directory.
			 * @param path: the path of the directory to create
			 */
			static void Create(const std::string& path);
			/**
			 * Delete a specified directory.
			 * @param path: the path of the directory to delete.
			 */
			static void Delete(const std::string& path);
			/**
			 * Copy the directory to another path.
			 * @param from: the src path of the directory copied from
			 * @param to:   the dest path of the directory copied to
			 */
			static void Copy(const std::string& from, const std::string& to);
			/**
			 * Move the directory to another path.
			 * @param from: the src path of the directory copied from
			 * @param to:   the dest path of the directory copied to
			 */
			static void Move(const std::string& from, const std::string& to);

		public:
			 /**
			  * The constructor.
			  * @param path: the full path of this directory
			  */
			 Directory(const std::string& path);
			 /**
			  * The copy constructor.
			  * @param other: the other directory
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
			inline operator const bool(void) const;

		public:
			/**
			 * Get the name of this directory.
			 */
			inline const std::string& GetName(void) const;
			/**
			 * Get the full path of this directory.
			 */
			inline const std::string& GetFullPath(void) const;

		public:
			/**
			 * List the files from this directory.
			 */
			const std::vector<File> GetFiles(void) const;
			/**
			 * List the directories from this directory.
			 */
			const std::vector<Directory> GetDirectories(void) const;
			/**
			 * Get the parent directory of this directory.
			 */
			Directory GetParentDirectory(void) const;

		private:
			/**
			 * The assignment operator overload.
			 * @param other: the other directory
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
		inline Directory::operator const bool(void) const
		{ return Directory::Exist(mFullPathStr.c_str()); }

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
