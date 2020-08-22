========================================================================
                      小沐云笔记 项目概述
========================================================================
 
一、项目概述
        为了方便平时做的笔记及时保存。该项目实现了对文件的自动上传及浏览下载。
        该项目包含一个 linux 下的服务器端，以及一个 windows 下的客户端，
        windows下的客户端对指定的一个文件夹进行监控，将修改/新建的文件自动上传备份到服务器上，然后可以通过浏览器查看/下载这个文件信息
        linux下的服务端，会对备份的文件进行热点判断，非热点文件进行压缩存储，提高磁盘利用率

二、功能模块介绍
       //////////////////////////////////////////////////////////////
     （一）服务端

       1、文件压缩模块
             检测出非热点文件，进行压缩存储
       2、数据管理模块
            用户备份的文件信息管理
       3、网络通信模块
          （1）响应客户端的文件上传请求
          （2）响应客户端的文件列表请求
          （3）响应客户端的文件下载请求

        //////////////////////////////////////////////////////////////
     （二）客户端

        1、数据管理模块
            管理指定目录下的文件信息（etag-最后一次修改时间，文件大小）
        2、目录监控模块
            检测目录下有哪些文件需要备份，并搭建http客户端进行备份
       
                    


三、代码模块介绍

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      （一）服务端


           ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           /////工具类

            （1）文件工具
             class FileUtil
               {
            public:
                  static void Read(const string &name, string *body);//从文件中读取数据
                  static void Write(const string &name, const string &body);//向文件中写入数据
            };

              （2） 压缩、解压缩工具
            class CompressUtil {
            public：
                  static bool Compress（const std:string&src name，const std:string&dst name）；//压缩（源文件名称，压缩包名称）
                  static bool UnCompress（const std:string&src_name，const std:：string&dst_name）；/解压缩（压缩包名称，源文件名称）
               }；

        

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        1、网络通信接口 （HTTP协议）
            （1）文件上传请求
            请求：
               PUT/filename HTTP/1.1\r\n
                  Content-Length：上传的文件大小小rin            
                   \r\n
                  正文：文件数据

            响应：
                  HTTP/1.1 200 OK\r\n 
                  Content-Length: 0\r\n
       
            （2）文件列表请求
             请求：
                  GET /list HTTP/1.1\r\n
                  Content-Length:0\r\n

            响应：
                  HTTP/1.1200 OK\r\n
                  Content-Length：最终组织的html长度\r\n
                  Content-Type:text/html\r\n
                  正文：具体组织出来的html文件列表页面数据

            （3）文件上传请求
             请求：
                  GET/filename HTTP/1.1\r\n 
                  Content-Length:0\r\n

             响应：
                  HTTP/1.1 200 OK\r\n
                  Content-Length：文件大小\r\n
                   r\n
                  正文：文件数据

            （4）模块类
            class Server{

            public:
                  bool Start();//开始搭建HTTP服务器，进行业务处理
            private:
                  //文件上传请求的回调处理函数
                  static void UpLoad  (const httplib::Request &req ,httplib::Response &rsp);
                  //文件列表请求的回调处理函数
                  static void List    (const httplib::Request &req ,httplib::Response &rsp);
                  //文件下载请求的回调处理函数
                  static void DownLoad(const httplib::Request &req ,httplib::Response &rsp);
	
            private:
                  string file_dir;//上传文件的存放路径
                  httplib::Server _server;//搭建http服务器的对象
            };

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         2、非热点文件压缩模块
            非热点文件的压缩解压缩模块--基于zlib封装实现非热点文件的压缩/解压缩
            (1)文件是否是热点文件的判断---文件属性中有一个属性--最后一次访问时间--若当前时间减去文件最后一次访问时间>基准值----非热点
            (2)文件的压缩功能（将源文件进行压缩存储，保留压缩文件，删除源文件），--》更新数据管理
            (3)文件的解压缩功能（先将文件解压缩，得到源文件，删除压缩文件）
                   
            //模块类
            class NonHotCompress
            {
            public:
                  /*******************************************/
                  /*  循环每隔一段时间：
                  1.获取未压缩文件列表           2.逐个判断是否是热点文件
                  3.若是非热点文件，则压缩    4.更新数据 */
                  /*******************************************/
                  bool Start(); //启动压缩模块

            private:
                  bool FilelsHot(const string &filename); //判断文件是否是一个热点文件
            private:
                  string _gz_dir;//压缩文件的存放路径
            };


            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            3、数据管理模块
            class DataManager
            {
            public:
                  bool Exists(const string &name);//判断文件是否存在
                  bool IsCompress(const string &name); //判断文件是否压缩
                  bool NonCompressed(vector<string> *list); //获取未压缩文件列表
                  bool Insert(const string &src, const string &dst); //插入更新数据
                  bool GetAllName(vector<string> list); //获取所有文件名称
                  bool Storage(); //数据持久化存储
                  bool InitLoad(); //服务端启动时加载所有文件信息

            private:
                  string _back_file; // 持久化数据信息存储文件名称
                  unordered_map<string, string> _file_list; //数据管理容器
                  pthread_rwlock_t _rwlock; //使用读写锁保护_file_list的操作--读共享，写互斥
            };


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      （二）客户端
         
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         1、数据管理模块
            管理指定目录下的文件信息（etag-最后一次修改时间，文件大小），管理两个数据，<文件名，文件etag信息>

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


         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
        2、目录监控模块
            读取目录下所有文件，每个文件都计算一下文件的etag信息，通过文件名到数据管理对象中查找原有etag信息，如果没有这个信息，则表示这是一个新文件，需要进                      行备份。如果有原有etag信息，则对新计算的etag和原有的etag进行比对，不相等则认为修改过，需要备份；否则不需要备份
            通过目录监控模块获取到需要备份的文件列表，搭建http客户端逐个上传文件即可上传完毕后，更新数据对象的etag信息。
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
                    
































































































































