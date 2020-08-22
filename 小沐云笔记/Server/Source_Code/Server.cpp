#include "Public.hpp"
#include "Server.hpp"
#include "httplib.h"
////功能函数接口实现

DataManager datafile(DATA_FILE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////工具类

///////////////////////////////////////////////////////////////////
////从文件中读取数据

bool FileUtil::Read(const std::string &name, std::string *body)
{
	//输入文件流
	std::ifstream fs(name,std::ios::binary);//以二进制形式打开
	if (fs.is_open() == false){
		cout << "open file " << name << "failed\n";
		return false;
	}
	// boost::filesystem::file_size() 获取文件大小
	int64_t fsize = boost::filesystem::file_size(name);
	body->resize(fsize); // 给body申请空间接收数据
	fs.read(&(*body)[0],fsize);
	if (fs.good() == false){
		cout << "file" << name << "read data failed!\n";
			return false;
	}
	fs.close();
	return true;
}

///////////////////////////////////////////////////////////////////
////向文件中写入数据
bool FileUtil:: Write(const std::string &name, const std::string &body)
{
	//输出文件流 --ofstream 默认打开时清空文件内容
	std::ofstream ofs(name,std::ios::binary);
	if (ofs.is_open() == false){
		std::cout << "open file " << name << "failed\n";
		return false;
	}

	ofs.write(&body[0],body.size());
	if (ofs.good() == false){
		std::cout << "file" << name << "write data failed!\n";
		return false;
	}
	ofs.close();
	return true;
}

///////////////////////////////////////////////////////////////////
////压缩（源文件名称，压缩包名称）
bool CompressUtil::Compress(const std::string &src,const std::string &dst)
{
	std::string body;
	FileUtil::Read(src, &body); //读入数据
	gzFile gf = gzopen(dst.c_str(),"wb");//打开压缩包文件
	if (gf == NULL){
		std::cout << "open file "<<dst<<"failed!"<< endl;
		return false;
	}

	int wlen = 0;
	while (wlen < body.size())
	{
		int ret = gzwrite(gf, &body[wlen], body.size()- wlen);
		if (ret == 0){
			std::cout << "file " << dst << "write compress data failed!" << endl;
			return false;
		}
		wlen += ret;
	}
	
	gzclose(gf);
	return true;
}

///////////////////////////////////////////////////////////////////
//// 解压缩（压缩包名称，源文件名称）
bool CompressUtil::UnCompress(const std::string &src,const std::string &dst)
{
    std::ofstream ofs(dst,std::ios::binary);
	if (ofs.is_open() == false){
        std::cout << "open file " << dst << "failed\n";
		return false;
	}

	gzFile gf = gzopen(src.c_str(), "rb");//打开压缩包文件
	if (gf == NULL){
        std::cout << "open file " << src << "failed!" << endl;
		ofs.close();
		return false;
	}

	int ret;
	char tmp[4096] = {0};
	while((ret = gzread(gf,tmp,4096)) > 0){
        ofs.write(tmp,ret);
    }
	ofs.close();
	gzclose(gf);

	return true;
}

   



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////模块接口——服务端


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////数据管理模块

///////////////////////////////////////////////////////////////////////////////////
////判断文件是否存在
bool DataManager:: DataManager::  Exists(const string &name)
{
    pthread_rwlock_rdlock(&_rwlock);
    auto it = _file_list.find(name);
    if(it == _file_list.end()){
        pthread_rwlock_unlock(&_rwlock);
        return false;
    }
    pthread_rwlock_unlock(&_rwlock);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
////判断文件是否压缩
bool DataManager:: IsCompress(const string &name)
{
    pthread_rwlock_rdlock(&_rwlock);
    auto it = _file_list.find(name);
    if(it == _file_list.end()){
        pthread_rwlock_unlock(&_rwlock);
        return false;
    }
    if(it->first == it->second){
        pthread_rwlock_unlock(&_rwlock);
        return false;
    }
    else{
        pthread_rwlock_unlock(&_rwlock); 
        return true;
    }
}


///////////////////////////////////////////////////////////////////////////////////
////获取未压缩文件列表
bool DataManager:: NonCompressed(vector<string> *list)
{
    pthread_rwlock_rdlock(&_rwlock);
    auto it = _file_list.begin();
    while(it != _file_list.end()){
        if(it->first == it->second){
            list->push_back(it->first);
        } 
        ++it;
    }
    pthread_rwlock_unlock(&_rwlock);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
////插入更新数据
bool DataManager:: Insert(const std::string &src, const std::string &dst)
{
    
    pthread_rwlock_wrlock(&_rwlock);
    _file_list[src] = dst;
    pthread_rwlock_unlock(&_rwlock);

    Storage();
    return true;
}


///////////////////////////////////////////////////////////////////////////////////
////获取所有文件名称
bool DataManager:: GetAllName(vector<string> *list)
{
    pthread_rwlock_rdlock(&_rwlock);
    auto it = _file_list.begin();
    while(it != _file_list.end()){
        list->push_back(it->first);
        ++it;
    }
    pthread_rwlock_unlock(&_rwlock);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
////根据源文件名称，获取压缩包名称
bool DataManager:: GetGzName(const string &src,string *dst)
{
    auto it = _file_list.find(src);
    if(it == _file_list.end()){
        return false;
    }
    *dst = it->second;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
////数据持久化存储
bool DataManager:: Storage()
{
    //数据序列化
    std::stringstream tmp; //定义一个string流
    pthread_rwlock_rdlock(&_rwlock);
    auto it = _file_list.begin();
    for(;it != _file_list.end();++it){
        tmp << it->first << " " << it->second <<"\r\n";
    }
    pthread_rwlock_unlock(&_rwlock);

    _back_file = "../datafile/S_filelist.text";
    FileUtil::Write(_back_file,tmp.str());
    return true;
}

///////////////////////////////////////////////////////////////////////////////////
////服务端启动时加载所有文件信息
bool DataManager::InitLoad()
{
    //将数据文件里的文件数据信息读取出来
    string body;
    if(FileUtil::Read(DATA_FILE,&body) == false ){
        return false;
    }

    //按照序列化的格式进行处理
    vector<string> list;
    boost::split(list,body,boost::is_any_of("\r\n"),
            boost::token_compress_off);//将数据按照/r/n进行分割

    for(auto i : list){
        size_t pos = i.find(" ");
        if(pos == std::string::npos){
            continue;
        }
        string key = i.substr(0,pos);
        string val = i.substr(pos+1);

        Insert(key,val);
    }
    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////非热点文件压缩模块  


///////////////////////////////////////////////////////////////////////////////////
////判断文件是否是一个热点文件
bool NonHotCompress::FilelsHot(const string &filename)
{
    //获取当前时间
    time_t cur_t = time(NULL);

    //获取文件最后一次访问时间
    string name = "./file/" + filename;
    struct stat st;
    if(stat(name.c_str(),&st) < 0){
        cout<< "get file: "  << filename << " stat failed!" <<endl;
        return false;
    }

    //判断最后一次访问时间和当前时间的差值，从而判断是否是热点文件
    if((cur_t - st.st_atime) > HOT_EVENT ){
        return false;
    } 
    else 
        return true;
}



///////////////////////////////////////////////////////////////////////////////////
////启动压缩模块
bool NonHotCompress::Start()
{
    while(1){
        //1.获取未压缩文件列表
        vector<string> list;
        datafile.NonCompressed(&list);

        //2.逐个判断是否是热点文件
        for(int i = 0 ; i < list.size() ; ++i){
           bool ret = FilelsHot(list[i]);
           //3.若是非热点文件，则压缩
           if(ret == false){

               string src_name = list[i];
               string dst_name = list[i] + ".gz";
               string src = _file_dir + src_name;
               string dst = _gz_dir + dst_name;
               if(CompressUtil::Compress(src,dst)){
                   //4.如果压缩成功，则更新文件数据 ,删除源文件
                   datafile.Insert(src_name , dst_name);
                   unlink(src.c_str());
               }
           }
        }
        
        //等待一定的时间，再次检测
        sleep(TEST_TIME);
    }
    return true;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////网络通信模块模块  


///////////////////////////////////////////////////////////////////////////////////
////文件上传请求的回调处理函数                                                                                                        
void Server:: UpLoad(const httplib::Request &req, httplib::Response &rsp)
{
    string filename = req.matches[1]; //文件名称，（.*）获取到的字符串
    string pathname = FILE_DIR + filename; //文件的备份路径
    FileUtil::Write(pathname,req.body);//req.body里面就是要存储的文件的内容，将它写入到备份路径下

    //将备份的文件名写入到数据管理模块中。
    datafile.Insert(filename,filename);

    //填充响应信息
    rsp.status = 200;

    return;
}


///////////////////////////////////////////////////////////////////////////////////
////文件列表请求的回调处理函数
void Server:: List(const httplib::Request &req, httplib::Response &rsp)
{
    vector<string> list;
    datafile.GetAllName(&list);

    string s;
    for(int i = 0; i < list.size(); ++i){
        s += "<a href='/DownLoad/";
        s += list[i];
        s += "'>";
        s += list[i];
        s += "</a> <br>";
    }


    FILE *fp = fopen("/root/小沐云笔记/html/list.html" , "r");
    char buf[2048] = {0};
    string str;
    while(!feof(fp)){
        fgets(buf,2048,fp);
        str += buf;
    }
    fclose(fp);

    std::size_t ps = str.find('~');
    str.insert(ps+2,s); 

    stringstream tmp;
    tmp<<str;
    //状态码
    rsp.status= 200;
    //正文
    rsp.set_content(tmp.str().c_str() , tmp.str().size() , "text.html");
}


///////////////////////////////////////////////////////////////////////////////////
////文件下载请求的回调处理函数
void Server:: DownLoad(const httplib::Request &req, httplib::Response &rsp)
{
    string filename=req.matches[1]; //要下载的文件名称  （.*）获取到的字符串
    //判断该文件是否存在
    if(datafile.Exists(filename) == false){
        rsp.status = 404; //文件不存在
        return;
    }
    //如果该文件存在，判断该文件是否被压缩
    string pathname = FILE_DIR + filename;
    if(datafile.IsCompress(filename)){
        //如果压缩了，则解压
        string gzfilename;
        datafile.GetGzName(filename,&gzfilename);
        string gzpathname = GZFILE_DIR + gzfilename;//组织一个压缩包的存放名
        CompressUtil::UnCompress(gzpathname,pathname);//解压
        unlink(gzpathname.c_str());
        cout<<"解压成功，开始更新数据"<<endl; 
        datafile.Insert(filename,filename);
    }

    //读取文件数据,返回给客户端
    FileUtil::Read(pathname,&rsp.body);
    rsp.set_header("Content-Type","application/octet-stream");//二进制流文件下载
    rsp.status= 200;
    return;
}



///////////////////////////////////////////////////////////////////////////////////
////开始搭建HTTP服务器，进行业务处理件 
bool Server:: Start()
{
    _server.Put("/(.*)",UpLoad);
    _server.Get("/List",List);
    _server.Get("/DownLoad/(.*)",DownLoad);// .* 表示匹配任意字符串，（）表示捕捉这个字符串

    _server.listen("192.168.80.100",9090);//搭建http服务器，进行http数据处理

    return true; 
}



