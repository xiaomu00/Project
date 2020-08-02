///////////////////////////////////////////////////////////////////////////
////π¶ƒ‹≤‚ ‘

#include"SeqList.h"
#include"Bigint.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////BigInt≤‚ ‘

void Test_BigInt()
{
	BigInt bt, bt1, bt2; 
	bt1.LoadDdata(1000);
	cout << "bt1: " << bt1<<endl;

	Sleep(1000);
	bt2.LoadDdata(1000);
	cout << "bt2: " << bt2 << endl;

	////BigInt::Add(bt,bt1, bt2);
	//BigInt::Sub(bt, bt1, bt2);
	BigInt::Mul(bt, bt1, bt2);



	cout << "bt : " << bt << endl;



	//BigInt bt3(123);
	//BigInt bt4(23);
	//cout << "bt3 : " << bt3 << endl;
	//cout << "bt4 : " << bt4 << endl;
	//cout << "bt3-bt4 : " << bt3-bt4 << endl;
	//cout << "bt3+bt4 : " << bt3+bt4 << endl;

	//cout << "bt3*bt4 : " << bt3*bt4 << endl;
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
