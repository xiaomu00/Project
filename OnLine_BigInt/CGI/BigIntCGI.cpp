#include"../BigInt/Bigint.h"
#include<string>

typedef enum{Add = 1, Sub, Mul, Div, Mod, Square} OPER;

void Html_Header()
{
    printf("Content-Type: text/html; charset=utf-8\n\n");
    printf("<title> xiaomu  BigInt </title>");
}

void Data_Handler(BigInt &bt, BigInt &bt1, BigInt &bt2,OPER op)
{
    bt.clear();
    bt1.clear(); 
    bt2.clear(); 

    //////////////////////////////////////////////////
    //读取环境变量的数据
    std::string data =getenv("QUERY_STRING");
    if(data.size() == 0)
        printf("data error");
    else{
        //////////////////////////////////////////////////
        //解析数据 例如 data: m=9%2B9-9*9%2F9%259
  


        //解析 m
        int pos = data.find('=');
        const char *p = data.c_str() + pos + 1;
        while(*p >= '0' && *p <= '9'){
            bt1.push_front(*p - '0');
            ++p;
        }

        //解析操作符
        if(*p == '-')
        {
            op = Sub;
        } else if (*p == '*'){
            op =Mul;
        }else{  
            p += 2;
            if(*p == 'B')
            {
                op = Add;
            } else if(*p == 'F'){
                op = Div;
            } else if(*p == '5'){
                op = Mod;
            }
        }

        p++;
        //解析bt2
        while(*p >= '0' && *p <= '9'){
            bt2.push_front(*p - '0');
            ++p;                                
        }

        if(op == Add)
            bt = bt1 + bt2;
        if(op == Sub)
            bt = bt1 - bt2;
        if(op == Mul)
            bt = bt1 * bt2;
        if(op == Div)
            bt = bt1 / bt2;
        if(op == Mod)
            bt = bt1 % bt2;


        //返回页面
        FILE *fp = fopen("/root/OnLine_BigInt/BigInt_Html/index.html" , "r");
        if(NULL == fp){
            printf("<h2 align=center> Return to page Failure. </h2>");
            exit(EXIT_FAILURE);
        }

        char buf[2048] = {0};
        string s;
        while(!feof(fp)){
            fgets(buf,2048,fp);
            s += buf;
        }
        fclose(fp);



        string sbt = bt.str_big();
        std::size_t ps = s.find('~');
            
        s.insert(ps+2,sbt); 
        cout<<s;

    }
}

int main(int argc ,char *argv[])
{
    Html_Header();

    BigInt bt, bt1, bt2;
    OPER op;

    Data_Handler(bt, bt1, bt2, op);

    return 0;
}
