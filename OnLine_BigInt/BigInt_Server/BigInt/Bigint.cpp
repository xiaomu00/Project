/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////大整数运算功能函数实现

#include"Bigint.h"

/////////////////////////////////////////////
////构造
BigInt::BigInt(u_long val)
{
	if (val == 0)
		push_back(0);
	while (val)
	{
		push_back(val % 10);
		val /= 10;
	}
}

/////////////////////////////////////////////
////加载数据
void BigInt:: LoadDdata(int bit_size)
{
	srand(time(0));
	for (int i = 0; i < bit_size; ++i)
	{
		int x = rand() % 10;
		while (i == bit_size-1 && x==0)
		{
			int x = rand() % 10;
		}
		_big.push_back(x);
	}
		
}

/////////////////////////////////////////////
////尾部插入
void BigInt::push_back(u_char x)
{  _big.push_back(x);  }

/////////////////////////////////////////////
////头部插入
void BigInt::push_front(u_char x)
{
	_big.push_front(x);
}

/////////////////////////////////////////////
////头部删除
void BigInt::pop_front()
{
	_big.pop_front();
}

/////////////////////////////////////////////
////尾部删除
void BigInt::pop_back()
{
	_big.pop_back();
}

/////////////////////////////////////////////
////大小
size_t BigInt::size()const
{  return _big.size();  }

/////////////////////////////////////////////
////清除
void BigInt::clear()
{
	_big.clear();
}

/////////////////////////////////////////////
////求最后一位数
u_char  BigInt:: back()const
{
	return _big.back();
}
/////////////////////////////////////////////
////调整第一位的0
void BigInt::clear_head_zero(BigInt& bt)
{
	if (bt == 0)
		return;
	while (bt.back() == 0)
	{
		bt.pop_back();
		if (bt == 0)
			return;
	}
}

/////////////////////////////////////////////
////转化为字符串
string BigInt:: str_big()
{
	return  _big.str_seq();
}

/////////////////////////////////////////////
////加某一项
u_char BigInt::Add_Item(u_char a, u_char b, u_char& c)
{
	u_char sum = a + b + c;
	if (sum > 9)
	{
		sum -= 10;
		c = 1;
	}
	else
		c = 0;
	return sum;
}

/////////////////////////////////////////////
////加法
void BigInt::Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	u_char c = 0;
	u_char sum;
	size_t i=1,j=1;
	while (i <= bt1.size() && j <= bt2.size())
	{
		sum = Add_Item(bt1[i], bt2[j], c);
		bt.push_back(sum);
		j++;
		i++;
	}
	
	while (i <= bt1.size())
	{
		sum = Add_Item(bt1[i],0, c);
		bt.push_back(sum);
		++i;
	}
	while (j <= bt2.size())
	{
		sum = Add_Item(0, bt2[j], c);
		bt.push_back(sum);
		++j;
	}
	if (c > 0)
		bt.push_back(c);
		
}

/////////////////////////////////////////////
////减某一项
u_char BigInt::Sub_Item(u_char a, u_char b, u_char& c)
{
	u_char sub;
	if (a >= b + c)
	{
		sub = a - b - c;
		c = 0;
	}
	else
	{
		sub = (a + 10) - b - c;
		c = 1;
	}
	return sub;
}

/////////////////////////////////////////////
////减法
void BigInt::Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if (bt1 < bt2)
		return;
	else if (bt1 == bt2)
		bt = 0;
	else
	{
		bt.clear();
		u_long i, j;
		i = j = 1;
		u_char sub, c = 0;
		while (i <= bt1.size() && j <= bt2.size())
		{
			sub = Sub_Item(bt1[i], bt2[j], c);
			bt.push_back(sub);
			i++;
			j++;
		}
		while (i <= bt1.size())
		{
			sub = Sub_Item(bt1[i], 0, c);
			bt.push_back(sub);
			i++;
		}
	}
}

/////////////////////////////////////////////
////乘某一项
void BigInt::Mul_Item(BigInt &bt, const BigInt &bt1, u_char x)
{
	u_long i = 1;
	u_char res,c = 0;
	while (i <= bt1.size())
	{
		res = x * bt1[i] + c;
		c = res / 10;
		res %= 10;
		bt.push_back(res);
		i++;
	}
	if (c > 0)
		bt.push_back(c);
}

/////////////////////////////////////////////
////移位相加（用于乘法）
void BigInt::MoveAdd(BigInt &bt, const BigInt &bt1, u_long offset)
{
	u_long i = offset;
	u_long j = 1;
	u_char c = 0;
	while (i <= bt.size() && j <= bt1.size())
	{
		bt[i] = Add_Item(bt[i],bt1[j],c);
		i++;
		j++;
	}
	while (c > 0 && i <= bt.size())
	{
		bt[i] = Add_Item(bt[i], 0, c);
		i++;
	}
	while (j <= bt1.size())
	{
		u_char sum = Add_Item(0, bt1[j], c);
		bt.push_back(sum);
		j++;
	}
	if (c>0)
	{
		bt.push_back(c);
	}
}

/////////////////////////////////////////////
////乘法
void BigInt::Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if (bt1 == 0 || bt2 == 0)
		bt = 0;
	else
	{
		BigInt Mul_table[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		for (u_long i = 1; i <= bt2.size(); ++i)
		{
			
			if (bt2[i] != 0 && Mul_table[bt2[i]] == 0)
			{
				Mul_table[bt2[i]].clear();
				Mul_Item(Mul_table[bt2[i]], bt1, bt2[i]);
			}
			MoveAdd(bt, Mul_table[bt2[i]], i);
		}
	}
}

/////////////////////////////////////////////
////除法
void BigInt:: Div(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if (bt1 < bt2)
		bt = 0;
	else if (bt1 == bt2)
		bt = 1;
	else
	{
		int len = bt1.size() - bt2.size();
		BigInt tmp;
		tmp.clear();

		for (u_long i = 1; i <= bt2.size(); ++i)//给除数后面补0；使除数的长度等于被除数
			tmp.push_back(bt1[i+len]);

		while (len >= 0)
		{
			u_char div = 0;
			while (tmp >= bt2)
			{
				tmp -= bt2;
				div++;
				clear_head_zero(tmp);
			}
			bt.push_front(div);
			if (len > 0)
			{
				tmp.push_front(bt1[len]);
				clear_head_zero(tmp);
			}
				
			--len;
		}
		clear_head_zero(bt);////去除结果前面的0，方便显示
	}
}

/////////////////////////////////////////////
////取模
void BigInt::Mod(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if (bt1 < bt2)
		bt = bt1;
	else if (bt1 == bt2)
		bt = 0;
	else
	{
		int len = bt1.size() - bt2.size();
		BigInt tmp;
		tmp.clear();

		for (u_long i = 1; i <= bt2.size(); ++i)//给除数后面补0；使除数的长度等于被除数
			tmp.push_back(bt1[i + len]);

		while (len >= 0)
		{
			while (tmp >= bt2)
			{
				tmp -= bt2;
				clear_head_zero(tmp);
			}
			if (len > 0)
			{
				tmp.push_front(bt1[len]);
				clear_head_zero(tmp);
			}
			--len;
		}
		bt = tmp;
		clear_head_zero(bt);////去除结果前面的0，方便显示
	}
}


/////////////////////////////////////////////
////平方 bt = bt1^2;

void BigInt::Square(BigInt &bt, const BigInt &bt1)
{
	Mul(bt,bt1,bt1);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////重载

/////////////////////////////////////////////
////重载[]
u_char BigInt::operator[](int pos)const
{
	return _big[pos];
}
u_char& BigInt::operator[](int pos)
{
	return _big[pos];
}

/////////////////////////////////////////////
////重载 <<
ostream& operator<<(ostream& out, const BigInt &bt)
{

	for (u_long i = bt.size(); i>0; --i)
		cout << (int)bt[i];
	return out;
}

/////////////////////////////////////////////
////重载 ==
bool BigInt:: operator==(const BigInt &bt)const
{
	if (size() != bt.size())
		return false;
	for (u_long i = bt.size(); i > 0; --i)
	{
		if (_big[i] != bt[i])
			return false;
	}
	return true;
}

/////////////////////////////////////////////
////重载 !=
bool BigInt:: operator!=(const BigInt &bt)const
{
	return !(*this==bt);
}

/////////////////////////////////////////////
////重载 <
bool BigInt:: operator<(const BigInt &bt)const
{
	if (size() < bt.size())
		return true;
	else if (size() > bt.size())
		return false;
	else
	{
		for (u_long i = bt.size(); i > 0; --i)
		{
			if ((*this)[i] > bt[i])
				return false;
			else if ((*this)[i] < bt[i])
				return true;
		}
		return false;
	}
}

/////////////////////////////////////////////
////重载 >=
bool BigInt:: operator>=(const BigInt &bt)const
{
	return !(*this < bt);
}


/////////////////////////////////////////////
////重载 >
bool BigInt:: operator>(const BigInt &bt)const
{
	if (size() > bt.size())
		return true;
	else if (size() < bt.size())
		return false;
	else
	{
		for (u_long i = bt.size(); i > 0; --i)
		{
			if ((*this)[i] < bt[i])
				return false;
			else if ((*this)[i] > bt[i])
				return true;
		}
		return false;
	}
}

/////////////////////////////////////////////
////重载 <=
bool BigInt:: operator<=(const BigInt &bt)const
{
	return !(*this > bt);
}

/////////////////////////////////////////////
////重载 ++
BigInt& BigInt::operator++()//前++
{
	BigInt tmp;
	tmp.clear();
	Add(tmp, *this, 1);
	*this = tmp;
	return *this;
}
BigInt BigInt::operator++(int)//后++
{

	BigInt tmp = *this;
	tmp.clear();
    ++*this;
	return tmp;
}

/////////////////////////////////////////////
////重载 --
BigInt& BigInt::operator--()//前--
{
	BigInt tmp;
	tmp.clear();
	Sub(tmp, *this, 1);
	*this = tmp;
	return *this;
}
BigInt BigInt::operator--(int)//后--
{
	BigInt tmp = *this;
	tmp.clear();
	--*this;
	return tmp;
}

/////////////////////////////////////////////
////重载 +=
BigInt& BigInt::operator+=(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Add(tmp, *this, bt);
	*this = tmp;
	return *this;
}

/////////////////////////////////////////////
////重载 -=
BigInt& BigInt::operator-=(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Sub(tmp, *this, bt);
	*this = tmp;
	return *this;
}

/////////////////////////////////////////////
////重载 *=
BigInt& BigInt::operator*=(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Mul(tmp, *this, bt);
	*this = tmp;
	return *this;
}

/////////////////////////////////////////////
////重载 /=
BigInt& BigInt::operator/=(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Div(tmp, *this, bt);
	*this = tmp;
	return *this;
}


/////////////////////////////////////////////
////重载 +
BigInt BigInt::operator+(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Add(tmp, *this, bt);
	return tmp;
}

/////////////////////////////////////////////
////重载 -
BigInt  BigInt::operator-(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Sub(tmp, *this, bt);
	return tmp;
}

/////////////////////////////////////////////
////重载 *
BigInt BigInt::operator*(const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Mul(tmp, *this, bt);
	return tmp;
}

///////////////////////////////////////////
////重载 除号 /
BigInt BigInt::operator / (const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Div(tmp,*this, bt);
	return tmp;
}

///////////////////////////////////////////
////重载 %
BigInt BigInt::operator % (const BigInt &bt)
{
	BigInt tmp;
	tmp.clear();
	Mod(tmp, *this, bt);
	return tmp;
}
