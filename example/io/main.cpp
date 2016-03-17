#include <bugshan/io/File.h>
#include <bugshan/io/Directory.h>

#include <iostream>

using namespace BugShan::IO;

int main(void)
{
	const char* const dirPath = ".";
	Directory* pdir = new Directory(dirPath);
	const std::vector<File*> filePtrVec = pdir->GetFiles();
	const std::vector<Directory*> dirPtrVec = pdir->GetDirectories();

	std::cout << "List the files of this directory: "  << dirPath << std::endl;
	for(auto fp : filePtrVec)
	{
		std::cout << fp->GetFullPath() << std::endl;
	}
	std::cout << "List the directories of this directory: "  << dirPath << std::endl;
	for(auto dp : dirPtrVec)
	{
		std::cout << dp->GetFullPath() << std::endl;
	}
	return 0;
}
