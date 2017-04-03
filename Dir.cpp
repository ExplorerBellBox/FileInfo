#include "Dir.h"
#include <iostream>
using namespace Explorer;
using std::string;


Dir::Dir(void): FileInfo("./")
{
	
}

Dir::Dir(const std::string& dirName): FileInfo(dirName)
{
	
}

bool Dir::createPath(const std::string& path)
{
	// TODO
	return true;
}

bool Dir::removePath(const std::string& path)
{
	// TODO
	return true;
}

std::vector<FileInfo> Dir::children()
{
	std::vector<FileInfo> tmpChildren;
	// TODO
	return tmpChildren;
}

FileInfo Dir::searchChild(const std::string& fileName)
{
	std::vector<FileInfo> tmpChildren = children();
	
	for (auto fileInfo: tmpChildren)
	{
		if (fileInfo == fileName)
		{
			return fileName;
		}
	}
	
	// TODO
	throw -1;
}

