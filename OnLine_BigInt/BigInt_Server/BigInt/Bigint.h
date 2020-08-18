#ifndef _BIGINT_H_
#define _BIGINT_H_
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////大整数运算类

#include"SeqList.h"

class BigInt;
ostream& operator<<(ostream& out, const BigInt &bt);

class BigInt
{

public:
	BigInt(u_long val);
	BigInt()
	{}

	~BigInt()
	{}

public:
	void LoadDdata(int bit_size);//加载数据
	void push_back(u_char x);//尾部插入
	void push_front(u_char x);//头部插入
	void pop_front();//头部删除
	void pop_back();//尾部删除
	void clear();//清除
	size_t size()const;//求长度
	u_char back()const;//求最后一位数
	static void clear_head_zero(BigInt& bt);//调整第一位的0
	string str_big();
public:
	static u_char  Add_Item(u_char a, u_char b, u_char& c);//加某一项
	static void    MoveAdd(BigInt &bt, const BigInt &bt1, u_long offset);//移位相加（用于乘法）
	static u_char  Sub_Item(u_char a, u_char b, u_char& c);//减某一项
	static void    Mul_Item(BigInt &bt, const BigInt &bt1, u_char x);//乘某一项
	static void    Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//加法
	static void    Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//减法
	static void    Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//乘法
	static void    Div(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//除法
	static void    Mod(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//取模
	static void    Square(BigInt &bt, const BigInt &bt1);//bt = bt1^2;
	static void    Power(BigInt &bt, const BigInt &bt1, u_long n);// bt =bt1^n;
	static void    Power(BigInt &bt, const BigInt &bt1, const BigInt &bt2);//bt = bt1^bt2
public:
	u_char operator[](int pos)const;
	u_char& operator[](int pos);
	friend ostream& operator<<(ostream& out, const BigInt &bt);
	BigInt operator+(const BigInt &bt);
	BigInt operator-(const BigInt &bt);
	BigInt operator*(const BigInt &bt);
	BigInt operator/(const BigInt &bt);
	BigInt operator%(const BigInt &bt);
public:
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);
public:
	BigInt& operator+=(const BigInt &bt);
	BigInt& operator-=(const BigInt &bt);
	BigInt& operator*=(const BigInt &bt);
	BigInt& operator/=(const BigInt &bt);
	BigInt& operator%=(const BigInt &bt);

public:
	bool operator<(const BigInt &bt)const;
	bool operator>(const BigInt &bt)const;
	bool operator>=(const BigInt &bt)const;
	bool operator<=(const BigInt &bt)const;
	bool operator==(const BigInt &bt)const;
	bool operator!=(const BigInt &bt)const;
private:
	SeqList<u_char> _big;
};


#endif /*_BIGINT_H_*/