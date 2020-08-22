#include "Public.hpp"
#include "Server.hpp"
#include "httplib.h"

extern  DataManager datafile;

//压缩工具测试
void CompressUtil_test(char *argv[])
{
    CompressUtil::Compress(argv[1], argv[2]);
    string file = argv[2];

    file += ".text";
    CompressUtil::UnCompress(argv[2],file.c_str());
}


//服务端数据管理模块测试
void DataManager_test()
{
    DataManager data("./test.txt");
    
    /*data.Insert("a.txt","a.txt");
    data.Insert("b.txt","b.txt.gz");
    data.Insert("c.txt","c.txt");
    data.Insert("d.txt","d.txt.gz");
    data.Insert("e.txt","e.txt");
    
    //持久化存储
    data.Storage();*/

    data.InitLoad();
    vector<string> list;
    data.GetAllName(&list);

    for(auto i : list){
        printf("%s\n",i.c_str());
    }
    
    list.clear();
    data.NonCompressed(&list);
    for(auto i : list){
        printf("%s\n",i.c_str());
    }
}


//非热点压缩模块入口函数
void NonHotCompress_Entrance()
{
    NonHotCompress ncs(FILE_DIR , GZFILE_DIR);
    ncs.Start();
    return;
}

////网络通信服务端入口函数   
void http_server_Entrance()
{
    Server srv;
    srv.Start();
    return ;
}



//argv[1]为源文件名称，argv[2]为压缩包名称
int main(int argc , char *argv[])
{
    //测试
    // CompressUtil_test(argv);
    // DataManager_test();
   
    //非热点压缩测试
    //判断备份路径以及压缩路径是否存在，不存在则创建
    if(boost::filesystem::exists(FILE_DIR) == false){
        boost::filesystem::create_directory(FILE_DIR);
    }
    if(boost::filesystem::exists(GZFILE_DIR) == false){
        boost::filesystem::create_directory(GZFILE_DIR);
    }


    //加载文件数据
    datafile.InitLoad();

    //创建线程
    thread thr_compress(NonHotCompress_Entrance);//启动非热点文件压缩模块
    thread thr_server(http_server_Entrance);//网络通信服务端入口函数
    thr_compress.join(); //等待线程退出  
    thr_server.join(); //等待线程退出  

    Server srv;
    srv.Start();

    return 0;
}




