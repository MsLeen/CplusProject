#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
double Division(int a, int b) {
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
		throw "Division by zero condition!";
	else
		return ((double)a / (double)b);
}
void Func()
{
	int len, time;
	cin >> len >> time;
	cout << Division(len, time) << endl;
}
int main(){
	try {
		Func();
	}
	catch (const char* errmsg){
		cout << errmsg << endl;
	}
	catch (...){
		cout << "unkown exception" << endl;
	}
	return 0;
}