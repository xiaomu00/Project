#ifndef _SERVER_H_
#define _SERVER_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////模块接口——服务端






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////数据管理模块
class DataManager
{
public:
	DataManager(const std::string &path):_back_file(path)
    {
        pthread_rwlock_init(&_rwlock,NULL);
    }
	~DataManager()
    {
        pthread_rwlock_destroy(&_rwlock);
    }

public:
	bool Exists(const string &name);//判断文件是否存在
	bool IsCompress(const string &name); //判断文件是否压缩
	bool NonCompressed(vector<string> *list); //获取未压缩文件列表
	bool Insert(const std:: string &src, const std::string &dst); //插入更新数据
	bool GetAllName(vector<string> *list); //获取所有文件名称
    bool GetGzName(const string &src,string *dst); //根据源文件名称，获取压缩包名称
	bool Storage(); //数据持久化存储
	bool InitLoad(); //服务端启动时加载所有文件信息

private:
	string _back_file; // 持久化数据信息存储文件名称
	unordered_map<string, string> _file_list; //数据管理容器
	pthread_rwlock_t _rwlock; //使用读写锁保护_file_list的操作--读共享，写互斥
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////非热点文件压缩模块
class NonHotCompress
{
public:
    NonHotCompress(const std::string file_name , const std::string gz_name)
        :_file_dir(file_name),_gz_dir(gz_name){}
public:
	/*******************************************/
	/*  循环每隔一段时间：
	1.获取未压缩文件列表        2.逐个判断是否是热点文件
	3.若是非热点文件，则压缩    4.更新数据 */
	/*******************************************/
	bool Start(); //启动压缩模块

private:
	bool FilelsHot(const string &filename);//判断文件是否是一个热点文件

private:
    string _file_dir; //备份文件目录
	string _gz_dir;   //压缩文件的存放路径
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////网络通信模块
class Server{
public:
	Server()
	{}
	~Server()
	{}

public:
	bool Start();//开始搭建HTTP服务器，进行业务处理
private:
	//文件上传请求的回调处理函数
	static void UpLoad(const httplib::Request &req, httplib::Response &rsp);
	//文件列表请求的回调处理函数
	static void List(const httplib::Request &req, httplib::Response &rsp);
	//文件下载请求的回调处理函数
	static void DownLoad(const httplib::Request &req, httplib::Response &rsp);

private:
	string file_dir;//上传文件的存放路径
	httplib::Server _server;//搭建http服务器的对象
};







#endif /* _SERVER_H_ */
