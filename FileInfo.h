/* class FileInfo
 */
#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Explorer
{
	class FileInfo
	{
		public:
			enum class FileType: int{isFILE=0, isDir, unknown};

		public:
			FileInfo(const std::string& inFileName);
			FileInfo(const FileInfo& src);
			virtual ~FileInfo(void) { }

			bool isExist(void);				// 文件是否存在
			FileType type(void);		// 文件类型
			std::string name(void);		// 文件名
			std::string path(void);		// 文件路径
			const std::string& realPath(void);	// 文件全路径名
			__off_t size(void);			// 文件大小
			virtual std::string lastModifyTime(void);	// 最后修改时间
			virtual std::string lastAccessTime(void);	// 最后访问时间
			virtual std::string lastStatusChangeTime(void);	// 最后状态改变时间
			virtual void showFileInfo(void);
			const struct stat& getStat(void) const;

			FileInfo& operator=(const FileInfo& rhs);
			FileInfo& operator=(const std::string& rhs);
			bool operator==(const FileInfo& rhs);

		public:
			static bool isExist(const std::string& inFileName);	// 文件是否存在
			static std::string realPath(const std::string& inFileName);	// 文件全路径名

        private:
			void fillFileStat(void);
			std::string timeStr(timespec& inTime);	// 格式化的时间字符串
			void doCopy(const FileInfo& src);

		private:
			bool m_exist;
			std::string m_fileRealPath;
			struct stat m_fileStat;

	};
}


#endif // FILEINFO_H
