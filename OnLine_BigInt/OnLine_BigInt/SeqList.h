#ifndef _SEQLIST_H_
#define _SEQLIST_H_
//////////////////////////////////////////
////底层数据存储结构——顺序表
////特点：(1) 0下标不存储数据，作为符号位  (2) 数据反着存储，便于处理进位。

#include"Public.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////顺序表类
template <typename Type>
class SeqList
{
public:
	SeqList(int sz = SEQLIST_DEFAULT_SIZE);
	SeqList<Type>& operator=(const SeqList<Type> &st);
	SeqList(const SeqList<Type> &st);
	~SeqList();

public:
	typedef Type& reference;
	typedef const Type& const_reference;

public:
	bool full()const;
	bool empty()const;
	void push_back(const Type &x); //尾部插入
	void push_front(const Type &x);//头部插入
	void pop_back();//尾部删除
	void pop_front();//头部删除
	reference front();//取出首元素
	const_reference front()const;
	reference back();//取出最后一个元素
	const_reference back()const;
	size_t size()const;//求长度
	void reverse();//反转
	void clear();//清除
	void sort();//排序
	int find(const Type &key); //查找
	void erase(const Type &key);//删除
protected:
	bool Expansion();//扩容
public:
	reference operator[](int pos);
	const_reference operator[](int pos)const;

private:
	Type *base;
	size_t capacity;
	size_t _size;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
////顺序表类——功能实现

/////////////////////////////////////////////
////构造
template <typename Type>
SeqList<Type>::SeqList(int sz)
{
	capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
	base = new Type[capacity+1];//第一个空间不存储数据
	memset(base, 0, sizeof(Type)*(capacity + 1));
	_size = 0;
}
template <typename Type>
SeqList<Type>:: SeqList(const SeqList<Type> &st)
{
	capacity = st.capacity;
	base = new Type[sizeof(Type)*(capacity+1)];
	memset(base, 0, sizeof(Type)*(capacity + 1));
	memcpy(base, st.base, sizeof(Type)*(st._size + 1));
	_size = st._size;
}
/////////////////////////////////////////////
////析构
template <typename Type>
SeqList<Type>::~SeqList()
{
	delete[]base;
	base = nullptr;
	capacity = _size = 0;
}

/////////////////////////////////////////////
////是否溢出
template <typename Type>
bool SeqList<Type>:: full()const
{
	return _size >= capacity;
}

/////////////////////////////////////////////
////是否为空
template <typename Type>
bool SeqList<Type>::empty()const
{
	return _size == 0;
}

/////////////////////////////////////////////
////求长度
template <typename Type>
size_t SeqList<Type>::size()const
{return _size;}

/////////////////////////////////////////////
////扩容
template <typename Type>
bool SeqList<Type>::Expansion()
{
	
	Type* new_base;
	try
	{
		new_base = new Type[2 * capacity + 1];//第一个空间不存储数据
	}
	catch (bad_alloc &e)
	{
		cout << "Out Of Memory" << endl;
		return false;
	}

	memset(new_base, 0, sizeof(Type)*(capacity*2 + 1));
	for (int i = 1; i <= _size; ++i)
	{
		new_base[i] = base[i];
	}
	delete[]base;
	capacity *= 2;
	base = new_base;
	return true;
}

/////////////////////////////////////////////
////尾部插入
template <typename Type>
void SeqList<Type>::push_back(const Type &x)
{
	if (full())//表示已满，需要扩容
	{
		Expansion();
	}
	base[++_size] = x;
}

/////////////////////////////////////////////
////头部插入
template <typename Type>
void SeqList<Type>::push_front(const Type &x)
{
	if (full())//表示已满，需要扩容
	{
		Expansion();
	}
	for (size_t i = _size; i > 0; --i)
		base[i + 1] = base[i];
	base[1] = x;
	_size++;
}

/////////////////////////////////////////////
////尾部删除
template <typename Type>
void SeqList<Type>::pop_back()
{
	if (empty())
		return;
	_size--;
}

/////////////////////////////////////////////
////头部删除
template <typename Type>
void SeqList<Type>::pop_front()
{
	if (empty())
		return;
	for (size_t i = 1; i <_size; ++i)
		base[i] = base[i + 1];
	_size--;
}

/////////////////////////////////////////////
////取出首元素
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::front()
{
	if (empty())
		ERR_EXIT("front");
	return base[1];
}
template <typename Type>
typename SeqList<Type>::const_reference SeqList<Type>::front()const
{
	if (empty())
		ERR_EXIT("front");
	return base[1];
}

/////////////////////////////////////////////
////取出最后一个元素
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::back()
{
	if (empty())
		ERR_EXIT("back");
	return base[_size];
}
template <typename Type>
typename SeqList<Type>::const_reference SeqList<Type>::back()const
{
	if (empty())
		ERR_EXIT("back");
	return base[_size];
}

/////////////////////////////////////////////
////反转
template <typename Type>
void SeqList<Type>::reverse()
{
	if (_size <= 1)
		return;
	size_t start = 1, end = _size;
	while (start < end)
	{
		Type tmp = base[start];
		base[start] = base[end];
		base[end] = tmp;
		start++;
		end--;
	}
}

/////////////////////////////////////////////
////清除
template <typename Type>
void SeqList<Type>::clear()
{_size = 0;}

/////////////////////////////////////////////
////排序
template <typename Type>
void SeqList<Type>::sort()
{
	if (_size <= 1)
		return;
	for (size_t i = 0; i < _size; ++i)
	{
		for (size_t j = 1; j <= _size - i - 1; ++j)
		{
			if (base[j]>base[j+1])
			{
				Type tmp = base[j];
				base[j] = base[j+1];
				base[j+1] = tmp;
			}
		}
	}
}

/////////////////////////////////////////////
////查找
template <typename Type>
int SeqList<Type>::find(const Type &key)
{
	for (size_t i = 1; i <= _size; ++i)
	{
		if (base[i] == key)
			return i;
	}
	return -1;
}

/////////////////////////////////////////////
////删除
template <typename Type>
void SeqList<Type>::erase(const Type &key)
{
	size_t pos = find(key);
	if (pos == -1)
		return;
	for (size_t i = pos; i < _size; ++i)
		base[i] = base[i + 1];
	_size--;
}

/////////////////////////////////////////////
////重载 =
template<class Type>
SeqList<Type>& SeqList<Type>::operator=(const SeqList<Type> &st)
{
	if (this != &st)
	{
		if (capacity < st._size)
		{
			Type* new_base = new Type[st.capacity + 1];
			delete[] base;
			base = new_base;
			capacity = st.capacity;
		}
		memcpy(base,st.base,sizeof(Type)*(st._size+1));
		_size = st._size;
	}
	return *this;
}

/////////////////////////////////////////////
////重载[]
template <typename Type>
typename SeqList<Type>::reference SeqList<Type>::operator[](int pos)
{
	return base[pos];
}

template <typename Type>
typename SeqList<Type>:: const_reference SeqList<Type>:: operator[](int pos)const
{
	return base[pos];
}

#endif /*_SEQLIST_H_*/