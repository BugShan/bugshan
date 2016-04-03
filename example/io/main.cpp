#include <bugshan/io/File.h>
#include <bugshan/io/Directory.h>
#include <bugshan/io/FileStream.h>

#include <iostream>

using namespace BugShan::IO;

const char* const G_COMMAND_SHOW_DIRECTORY		= "show_directory";
const char* const G_COMMAND_CREATE_FILE			= "create_file";
const char* const G_COMMAND_DELETE_FILE			= "delete_file";
const char* const G_COMMAND_MOVE_FILE			= "move_file";
const char* const G_COMMAND_COPY_FILE			= "copy_file";
const char* const G_COMMAND_WRITE_FILE			= "write_file";
const char* const G_COMMAND_FILE_SIZE			= "file_size";


void show_directory(const char* const dirPath)
{
	Directory dir(dirPath);
	const std::vector<File> fileVec = dir.GetFiles();
	const std::vector<Directory> subDirVec = dir.GetDirectories();
	std::cout << "List the files of this directory: " << dirPath << std::endl;
	for(auto& file : fileVec)
		std::cout << file.GetFullPath() << std::endl;
	std::cout << "List the directories of this directory: " << dirPath << std::endl;
	for(auto& dir : subDirVec)
		std::cout << dir.GetFullPath() << std::endl;
}

const char* const g_dir_path = ".";
int main(int argc, char** argv)
{
	if(0 == strcmp(argv[1], G_COMMAND_SHOW_DIRECTORY))
	{
		if(argc >= 3)
			show_directory(argv[2]);
	}
	else if(0 == strcmp(argv[1], G_COMMAND_CREATE_FILE))
	{
		if(argc >= 3)
			File::Create(argv[2]);
	}
	else if(0 == strcmp(argv[1], G_COMMAND_DELETE_FILE))
	{
		if(argc >= 3)
			File::Delete(argv[2]);
	}
	else if(0 == strcmp(argv[1], G_COMMAND_MOVE_FILE))
	{
		if(argc >= 4)
			File::Move(argv[2], argv[3]);
	}
	else if(0 == strcmp(argv[1], G_COMMAND_COPY_FILE))
	{
		if(argc >= 4)
			File::Copy(argv[2], argv[3]);
	}
	else if(0 == strcmp(argv[1], G_COMMAND_FILE_SIZE))
	{
		if(argc >= 3)
		{
			File file(argv[1]);
			auto size = file.GetSize();
			std::cout << size << std::endl;
		}
	}
	else if(0 == strcmp(argv[1], G_COMMAND_WRITE_FILE))
	{
		if(argc >= 3)
		{
			File* file = new File(argv[2]);
			FileStream writer = file->GetStream();
			char buff[] = "1 2 3 4 5 6 7 8 9 q w e r t y u i o p";
			writer.Write(buff, sizeof(buff) - 1);
			writer.Write(buff, sizeof(buff) - 1);
			writer.Close();
			delete file;
		}
	}
	return 0;
}
