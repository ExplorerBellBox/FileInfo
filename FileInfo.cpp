#include "FileInfo.h"
#include <limits.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libgen.h>
#include <ctime>
#include <cstring>
using namespace Explorer;
using std::cout;
using std::endl;
using std::string;


FileInfo::FileInfo(const string& inFileName): m_exist(false), m_fileRealPath("#NOT_EXIST")
{
	memset(&m_fileStat, 0, sizeof(m_fileStat));
	m_exist = isExist(inFileName);
	if (m_exist)
	{
		m_fileRealPath = realPath(inFileName);
		fillFileStat();
	}
}

FileInfo::FileInfo(const FileInfo& src)
{
	doCopy(src);
}

bool FileInfo::isExist(const string& inFileName)
{
	if (0 == access(inFileName.c_str(), F_OK))
	{
		return true;
	}
	return false;
}

bool FileInfo::isExist()
{
	return m_exist;
}

FileInfo::FileType FileInfo::type()
{
    if (isExist())
    {
        if (S_ISREG(m_fileStat.st_mode))
        {
            return FileType::isFILE;
        }
        else if (S_ISDIR(m_fileStat.st_mode))
        {
            return FileType::isDir;
        }
    }
    return FileType::unknown;
}

string FileInfo::name()
{
	char tmpFileName[PATH_MAX] = {0};
	memcpy(tmpFileName, m_fileRealPath.c_str(), m_fileRealPath.length());
	// Note: basename() has some differences in different platform
	return basename(tmpFileName);
}

string FileInfo::path()
{
	if (!isExist())
	{
		return "#NOT_EXIST";
	}
	char tmpFilePath[PATH_MAX] = {0};
	memcpy(tmpFilePath, m_fileRealPath.c_str(), m_fileRealPath.length());
	return dirname(tmpFilePath);
}

string FileInfo::realPath(const string& inFileName)
{
	char tmpRealPath[PATH_MAX] = {0};
	realpath(inFileName.c_str(), tmpRealPath);
	return tmpRealPath;
}

const string& FileInfo::realPath()
{
	return m_fileRealPath;
}

__off_t FileInfo::size()
{
	 return m_fileStat.st_size;
}

string FileInfo::lastModifyTime()
{
	if (!isExist())
	{
		return "#NOT_EXIST";
	}
	return timeStr(m_fileStat.st_mtim);
}

string FileInfo::lastAccessTime()
{
	if (!isExist())
	{
		return "#NOT_EXIST";
	}
	return timeStr(m_fileStat.st_atim);
}

string FileInfo::lastStatusChangeTime()
{
	if (!isExist())
	{
		return "#NOT_EXIST";
	}
	return timeStr(m_fileStat.st_ctim);
}

const struct stat& FileInfo::getStat(void) const
{
	return m_fileStat;
};

void FileInfo::showFileInfo()
{
	if (!m_exist)
	{
		cout << "File not exist!" << endl;
		return;
	}

	if (FileType::isFILE == type())
	{
		cout << "File type: common file" << endl;
	}
	else if (FileType::isDir == type())
	{
		cout << "File type: dir file" << endl;
	}
	else
	{
		cout << "File type: unknown" << endl;
	}
	cout << "File name: " << name() << endl;
	cout << "File path: " << path() << endl;
	cout << "File size: " << size() << endl;
	cout << "File's last modify time: " << lastModifyTime() << endl;
	cout << "File's last access time: " << lastAccessTime() << endl;
	cout << "File's last status change time: " << lastStatusChangeTime() << endl;
}

FileInfo& FileInfo::operator=(const FileInfo& rhs)
{
	if (&rhs != this)
	{
		doCopy(rhs);
	}
	return *this;
}

FileInfo& FileInfo::operator=(const string& rhs)
{
	*this = FileInfo(rhs);
	return *this;
}

bool FileInfo::operator==(const FileInfo& rhs)
{
	if (m_fileRealPath == rhs.m_fileRealPath)
	{
		return true;
	}

	return false;
}

void FileInfo::fillFileStat()
{
	memset(&m_fileStat, 0, sizeof(m_fileStat));
	stat(m_fileRealPath.c_str(), &m_fileStat);
}

string FileInfo::timeStr(struct timespec& inTime)
{
	char tmpStr[128] = {0};
	struct tm *t = localtime(&inTime.tv_sec);
	if (nullptr != t)
	{
		sprintf(tmpStr,  "%04d-%02d-%02d %02d:%02d:%02d.%03ld",
				t->tm_year+1900, t->tm_mon+1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec, inTime.tv_nsec/1000000);
	}

	return tmpStr;
}

void FileInfo::doCopy(const FileInfo& src)
{
	m_exist = src.m_exist;
	m_fileRealPath = src.m_fileRealPath;
	memcpy(&m_fileStat, &(src.m_fileStat), sizeof(m_fileStat));
}

