#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

//注：VisualStudio需要在“配置属性-高级-高级属性-字符集”下设置“使用多字节字符集”而非“使用 Unicode 字符集”。
//注：两种字符集的编码方式和使用的FindFirstFile()函数不同。
//注：使用unicode字符集时需要将(LPCSTR)替换为(LPCWSTR)并将dir_name也转为wchar编码，否则会编译报错或找不到文件。
//输入文件夹路径dir_name，输出文件夹列表dir与文件列表file
int find_dir_file(std::string dir_name, std::vector<std::string>& dir, std::vector<std::string>& file)
{
	dir.clear();
	file.clear();
	WIN32_FIND_DATA FindFileData;
	dir_name += "/*.*";
	HANDLE hFind = ::FindFirstFile((LPCSTR)dir_name.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "find_dir_file() error! GetLastError() = " << ::GetLastError() << std::endl;
		std::cout << "dir :" << dir_name.c_str() << std::endl;
		return -1;
	}
	while (1)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//directory
		{
			dir.push_back(std::string((char*)FindFileData.cFileName));
		}
		else if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)//file
		{
			file.push_back(std::string((char*)FindFileData.cFileName));
		}
		if (!FindNextFile(hFind, &FindFileData))
			break;
	}
	::FindClose(hFind);
	return 0;
}

int main(int argc, char** argv)
{
	std::vector<std::string> dir, file;
	find_dir_file("./", dir, file);
	for (std::string strOut : dir)
		std::cout << "dir:\t" + strOut << std::endl;
	for (std::string strOut : file)
		std::cout << "file:\t" + strOut << std::endl;
}
