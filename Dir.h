#ifndef DIR_H
#define DIR_H

#include "FileInfo.h"
#include <stdexcept>
#include <vector>

namespace Explorer
{
	class Dir : public FileInfo
	{
		public:
			Dir(void);
			Dir(const std::string& dirName);
			virtual ~Dir(void) { }

			bool createPath(const std::string& path);
			bool removePath(const std::string& path);

			// TODO 一级 子文件，使用 vector
			std::vector<FileInfo> children(void);
			FileInfo searchChild(const std::string& fileName);
	};
}


#endif // DIR_H
