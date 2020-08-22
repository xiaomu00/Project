#include "Client.hpp"

;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////工具类

///////////////////////////////////////////////////////////////////
////从文件中读取数据

bool FileUtil::Read(const std::string &name, std::string *body)
{
	//输入文件流
	std::ifstream fs(name, std::ios::binary);//以二进制形式打开
	if (fs.is_open() == false){
		cout << "open file " << name << "failed\n";
		return false;
	}
	// boost::filesystem::file_size() 获取文件大小
	int64_t fsize = boost::filesystem::file_size(name);
	body->resize(fsize); // 给body申请空间接收数据
	fs.read(&(*body)[0], fsize);
	if (fs.good() == false){
		cout << "file" << name << "read data failed!\n";
		return false;
	}
	fs.close();
	return true;
}

///////////////////////////////////////////////////////////////////
////向文件中写入数据
bool FileUtil::Write(const std::string &name, const std::string &body)
{
	//输出文件流 --ofstream 默认打开时清空文件内容
	std::ofstream ofs(name, std::ios::binary);
	if (ofs.is_open() == false){
		std::cout << "open file " << name << "failed\n";
		return false;
	}

	ofs.write(&body[0], body.size());
	if (ofs.good() == false){
		std::cout << "file" << name << "write data failed!\n";
		return false;
	}
	ofs.close();
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////数据管理模块
/////////////////////////////////////////////////////////////////////////////
////插入文件列表信息
bool DataManager::Insert(const string &key, const string &val)
{
	_backup_list[key] = val;
	Storage();
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////通过文件名获取etag信息
bool DataManager::GetEtag(const string &key, string*val)
{
	auto it = _backup_list.find(key);
	if (it == _backup_list.end()){
		return false;
	}
	*val = it->second;
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////初始化加载原有数据
bool DataManager::lnitLoad()
{
	//将数据文件里的文件数据信息读取出来
	string body;
	if (FileUtil::Read(_store_file, &body) == false){
		return false;
	}

	//按照序列化的格式进行处理
	vector<string> list;
	boost::split(list, body, boost::is_any_of("\r\n"),
		boost::token_compress_off);//将数据按照/r/n进行分割

	for (auto i : list){
		size_t pos = i.find(" ");
		if (pos == std::string::npos){
			continue;
		}
		string key = i.substr(0, pos);
		string val = i.substr(pos + 1);

		Insert(key, val);
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////每次更新数据之后，持久化存储
bool DataManager::Storage()
{
	//数据序列化
	std::stringstream tmp; //定义一个string流
	auto it = _backup_list.begin();
	for (; it != _backup_list.end(); ++it){
		tmp << it->first << " " << it->second << "\r\n";
	}

	_store_file = "C_filelist.text";
	FileUtil::Write(_store_file, tmp.str());
	return true;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////目录监控模块

/////////////////////////////////////////////////////////////////////////////
////获取需要备份的文件列表---浏览目录下所有文件，逐个获取etag然后进行比对
bool CloudClient::GetBackUpFileList(vector<string> *list)
{
	//如果需要监控的目录不存在，则创建
	if (boost::filesystem::exists(_listen_dir) == false){
		boost::filesystem::create_directory(_listen_dir);
	}

	//1.获取指定目录下的所有文件名称
	boost::filesystem::directory_iterator begin(_listen_dir);
	boost::filesystem::directory_iterator end;
	for (; begin != end; ++begin){
		if (boost::filesystem::is_directory(begin->status())){
			//如果是目录，则不进行备份
			continue;
		}
		string pathname = begin->path().string();//获取文件路径名+文件名
		string name = begin->path().filename().string();//获取文件名
		string cur_etag;

		//2.逐个计算当前的etag值
		GetEtag(pathname,&cur_etag);

		//3.和data_manage中存在的原有etag进行比对
		string old_etag;
		data_manage.GetEtag(name,&old_etag);
		if (cur_etag != old_etag){
			list->push_back(name);
		}
	}
	return true;
}



/////////////////////////////////////////////////////////////////////////////
////计算一个文件的etag信息(etag: 文件大小 ，文件的最后一次修改时间)
bool CloudClient::GetEtag(const string &pathname, string *etag)
{
	int64_t fsize = boost::filesystem::file_size(pathname);
	time_t mtime = boost::filesystem::last_write_time(pathname);
	*etag = to_string(fsize) + " " + to_string(mtime);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////完成整体的文件备份流程
bool CloudClient::Start()
{
	//加载数据信息
	data_manage.lnitLoad();
	while (1)
	{
		vector<string> list;
		//获取到所有需要备份的文件名称
		GetBackUpFileList(&list);

		for (int i = 0; i < list.size(); ++i){
			string name = list[i];
			string pathname = _listen_dir + name;

			//获取文件数据
			string body;
			FileUtil::Read(pathname, &body);


			httplib::Client client(_srv_ip, _srv_port);

			//发送Put请求，进行备份
			string req_path = "/" + name;
			auto rsp = client.Put(req_path.c_str(), body, "application/octet-stream");//二进制流数据
			if (rsp == NULL || (rsp != NULL && rsp->status != 200)){

				//失败
				cout << "backup failed!" << endl;
				continue;
			}

			//备份成功，则更新数据
			cout << "backup success!" << endl;
			string etag;
			GetEtag(pathname, &etag);
			data_manage.Insert(name, etag);		
		}
		Sleep(1000);
	}
	return true;
}