#ifndef _CLIENT_H_
#define _CLIENT_H_ 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////模块接口-客户端
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include<boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "httplib.h"
using namespace std;

#define STORE_FILE "./C_filelist.text"
#define LISTEN_DIR "./backup/"
#define SERVER_IP   "192.168.80.100"
#define SERVER_PORT  9090


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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////数据管理模块
class DataManager{
public:
	DataManager(const string &filename) :_store_file(filename){}
	bool Insert(const string &key, const string &val);//插入文件列表信息
	bool GetEtag(const string &key, string*val);//通过文件名获取etag信息
	bool lnitLoad();///初始化加载原有数据
	bool Storage();//每次更新数据之后，持久化存储

private:
	string _store_file; //数据持久化存储路径/文件名
	unordered_map<string, string> _backup_list;//文件列表信息
};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////目录监控模块
class CloudClient{
public:
	CloudClient(const string &filename, const string &store_file, const string srv_ip, uint16_t srv_port)
		:_listen_dir(filename), data_manage(STORE_FILE), _srv_ip(srv_ip), _srv_port(srv_port){}

	bool GetBackUpFileList(vector<string> *list);//获取需要备份的文件列表---浏览目录下所有文件，逐个获取etag然后进行比对
	bool GetEtag(const string &pathname, string *etag);//计算一个文件的etag信息
	bool Start();//完成整体的文件备份流程
private:
	string _listen_dir; //监控模块要监控的目录名称   
	DataManager data_manage;
	string _srv_ip;
	uint16_t _srv_port;
};




#endif /*_CLIENT_H_*/

