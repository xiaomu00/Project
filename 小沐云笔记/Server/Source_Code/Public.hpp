#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <pthread.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>
#include <time.h>
#include "httplib.h"
using namespace std;


#define HOT_EVENT 20  //判断是否是热点文件的时间基准
#define TEST_TIME 30  //判断是否是热点文件的时间间隔
#define FILE_DIR       "../file/"      //文件备份目录
#define GZFILE_DIR     "../gzfile/"    //压缩文件的目录
#define DATA_FILE      "../datafile/S_filelist.text" 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////工具类

///////////////////////////////////////////////////////////////////
////文件工具
class FileUtil
{
public:
	static bool Read(const std::string &name, std::string *body);//从文件中读取数据
	static bool Write(const std::string &name, const std::string &body);//向文件中写入数据
};

///////////////////////////////////////////////////////////////////
////压缩工具
class CompressUtil
{
public:
	static bool Compress(const std::string &src, const std::string &dst);//压缩（源文件名称，压缩包名称）
	static bool UnCompress(const std::string &src, const std::string &dst); // 解压缩（压缩包名称，源文件名称）
};


#endif /*_PUBLIC_H_ */
