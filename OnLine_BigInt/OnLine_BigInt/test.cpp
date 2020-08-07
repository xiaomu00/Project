///////////////////////////////////////////////////////////////////////////
////π¶ƒ‹≤‚ ‘

#include"SeqList.h"
#include"Bigint.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////BigInt≤‚ ‘

void Test_BigInt()
{
	BigInt bt;
	BigInt bt1, bt2;
	//BigInt bt3(120),bt4(2);

	bt1.LoadDdata(10);
	cout << "bt1: " << bt1<<endl;

	/*Sleep(1000);
	bt2.LoadDdata(2);
	cout << "bt2: " << bt2 << endl;*/

	//BigInt::Add(bt,bt1, bt2);
	//BigInt::Sub(bt, bt1, bt2);
	//BigInt::Mul(bt, bt1, bt2);
	//BigInt::Div(bt, bt1, bt2);
	BigInt::Square(bt, bt1);


	cout << "bt : " << bt << endl;
	//cout << "bt1*bt2 : " << bt1*bt2 << endl;

	
	//BigInt:: Square(bt, bt3);
	//cout << "bt3/bt4 : " << bt << endl;
	//bt3 *= bt4;
	//cout << "bt3*=bt4 : " << bt3<< endl;
	/*
	if (bt3 < bt4)
		cout << "bt3 < bt4" << endl;
	else
		cout << "bt3 >= bt4" << endl;*/
}





///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////À≥–Ú±Ì≤‚ ‘
void Test_SeqList()
{
	SeqList<int> list;
	for (int i = 1; i <= 20; ++i)
		list.push_front(i);
	for (int i = 1; i <= 20; ++i)
		list.push_back(i);

	for (size_t i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	list.pop_back();
	for (size_t i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;
	
	list.pop_front();
	for (size_t i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	cout << "front:" << list.front() << endl;
	cout << "back:"<<list.back() << endl;

	list.reverse();
	for (size_t i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	list.sort();
	for (size_t i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;
}
