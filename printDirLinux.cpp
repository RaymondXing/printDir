//示例程序：输出当前目录下的文件
//编译(compile)：g++ printDirLinux.cpp -o printDirLinux -O3 -std=c++11
//运行(execute)：./printDirLinux
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>

//输入文件夹路径dir_name，输出文件夹列表dir与文件列表file
int find_dir_file(std::string dir_name, std::vector<std::string>& dir, std::vector<std::string>& file)
{
	dir.clear();
	file.clear();
	DIR *dirp;
	struct dirent *dp;
	dirp = opendir(dir_name.c_str());
	if(dirp == NULL)
	{
		std::cout << "find_dir_file() error!\n dir_name = " << dir_name << std::endl;
		return -1;
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		if(std::string(dp->d_name) == std::string(".") || std::string(dp->d_name) == std::string(".."))
		{//当前路径或者父路径
			continue;
		}
		else if(dp->d_type == DT_REG)//文件
		{
			file.push_back(std::string(dp->d_name));
		}
		else if(dp->d_type == DT_DIR)//路径
		{
			dir.push_back(std::string(dp->d_name));
		}
	}
	(void) closedir(dirp);
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
