#include "Path.h"

namespace BugShan
{
	namespace IO
	{
		const char CHAR_DOT				= '.';
		const char CHAR_SEPARATOR		= '/';
		const std::string STRING_EMPTY	= std::string();

		const std::string Path::GetFileNameStr(const std::string& fullPath)
		{
			assert(!fullPath.empty());
			for(int i = fullPath.length() - 1; i >= 0; -- i)
			{
				char c = fullPath[i];
				if(CHAR_SEPARATOR == c)
				{
					return fullPath.substr(i + 1, fullPath.length() - (i - 1));
				}
			}
			return fullPath;
		}
		const std::string Path::GetDirPathStr(const std::string& fullPath)
		{
			assert(!fullPath.empty());
			for(int i = fullPath.length() - 1; i >= 0; -- i)
			{
				char c = fullPath[i];
				if(CHAR_SEPARATOR == c)
				{
					return fullPath.substr(0, i);
				}
			}
			return fullPath;
		}

		const std::string Path::GetDirNameStr(const std::string& fullPath)
		{
			assert(!fullPath.empty());
			for(int i = fullPath.length() - 1; i >= 0; -- i)
			{
				char c= fullPath[i];
				if(CHAR_SEPARATOR == c)
				{
					return fullPath.substr(i + 1, fullPath.length() - (i - 1));
				}
			}
			return fullPath;
		}

		const std::string Path::GetExtensionStr(const std::string& fullPath)
		{
			assert(!fullPath.empty());
			for(int i = fullPath.length() - 1; i >= 0; -- i)
			{
				char c = fullPath[i];
				if(CHAR_DOT == c)
				{
					if(i != fullPath.length() - 1)
					{
						return fullPath.substr(i, fullPath.length() - i);
					}
					else
					{
						return STRING_EMPTY;
					}
				}
			}
			return STRING_EMPTY;
		}
	};//namespace IO
};//namespace BugShan
