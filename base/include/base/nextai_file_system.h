#ifndef _NEXTAI_FILE_SYSTEM_H_
#define _NEXTAI_FILE_SYSTEM_H_

#include "base/nextai_basic_types.h"
#include <fstream>

namespace NextAI
{
	/* 文件系统 */
	class FileSystem
	{
	public:
		/* 访问模式 */
		enum ACCESS_MODE
		{
			ACCESS_MODE_NO_EXIST,		/* 文件不存在 */
			/* ---------------- */
			ACCESS_MODE_DENIED,			/* 访问拒绝 */
			ACCESS_MODE_READ_ONLY,		/* 只读权限 */
			ACCESS_MODE_WRITE_ONLY,		/* 只写权限 */
			ACCESS_MODE_READ_WRITE		/* 读写权限 */
		};
		
	public:
		/* 判断文件是否存在 */
		static bool isExist(const std::wstring& path);
		
		/* 获得文件的权限 */
		static ACCESS_MODE getAccessMode(const std::wstring& path);
		
		/* 判断文件是否是绝对路径 */
		static bool isAbsolute(const std::wstring& path);
		
		/* 获得当前路径 */
		static const std::wstring getCurrentDirectory();
		
	private:
		FileSystem();
		virtual ~FileSystem();
		
		/* 禁用拷贝 */
		DISABLE_CLASS_COPY(FileSystem);
		
		static std::wstring m_currentDirectory;
	};
	
	/* 文件处理模式 */
	enum class FileAccessMode
	{
		Read,			/* 读文件 */
		Write,			/* 写文件 */
		ReadWrite,		/* 读写文件 */
		Append,			/* 追加文件 */
		ReadBinary,		/* 二进制读文件 */
		WriteBinary,	/* 写文件 */
		AppendBinary,	/* 追加文件 */
	};
	
	enum class FileStatus
	{
		OK,				/* 正常 */
		NotOpen			/* 未打开 */
	};
	
	/* 标准文件 */
	class File
	{
	public:
		File();
		virtual ~File();
		
		/* 打开文件 */
		bool open(const std::wstring& wpath, FileAccessMode mode);
		
		/* 文件是否已经被打开 */
		bool isOpen();
		
		/* 关闭文件 */
		FileStatus close();
		
		/* 输入内容 */
		FileStatus write(const std::wstring& string);
		FileStatus writeLine(const std::wstring& string);
		FileStatus write(const BIT_DATA* buffer, uint32 bufferSize);
		
#if 0	/* TODO */
		/* 读入内容 */
		FileStatus read(std::wstring& string);
		FileStatus readLine(std::wstring& string);
#endif
		FileStatus read(BIT_DATA* buffer, uint32 bufferSize);
		
		/* 是否到达文件尾部 */
		bool EndOfFile();
		
		/* 刷新文件 */
		FileStatus flush();
		
	private:
		/* 禁用拷贝 */
		DISABLE_CLASS_COPY(File);
		
		std::wfstream m_file;
	};
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::FileAccessMode);
OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::FileStatus);

#endif // !_NEXTAI_FILE_SYSTEM_H_