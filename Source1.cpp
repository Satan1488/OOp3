#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"Header1.h"

using namespace std;
enum interface_operations
{
	EXIT, SUM, MINUS, MULTIPLY, SHARE, CONCLUSION, CONVERSION, FIL
};

int charToInt(char *ch) {
	int ches = 0;
	for (int i = 0; ch[i] != 0; ch++) {
		if (ch[i] < 48 || ch[i]>58) return ches;
		ches *= 10;
		ches += ch[i] - 48;
	}
	return ches;
}

void PoC() {
	cout << "Enter one of the commands" << endl;
	cout << "EXIT-0" << endl;
	cout << "SUM-1" << endl;
	cout << "MINUS-2" << endl;
	cout << "MULTIPLICATION BY 10 IN DEGREE-3" << endl;
	cout << "DIVISION BY 10 IN DEGREE-4" << endl;
	cout << "CONCLUSION-5" << endl;
	cout << "CONVERSION FROM ARRAY TO VARIABLE-6" << endl;
}

void main() {
	int a;
	char *stc = new char[BUFSIZ];
	/*
	SoFuckingLong a(56);
	SoFuckingLong b(1900500);
	SoFuckingLong c = b.Del(a);
	SoFuckingLong d("4");
	SoFuckingLong e("10000000");
	SoFuckingLong f = e.Del(d);
	char *str = b.getString();
	*/
	do {
		PoC();
		cin >> stc;
		a = charToInt(stc);
		switch (a)
		{
		case SUM:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			int len2 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len2;
			char *c = new char[len2 + 1];
			cout << "Enter the number" << endl;
			cin >> c;
			XD f(b);
			XD g(c);
			XD h = f + g;
			cout << h.getString();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case MINUS:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			int len2 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len2;
			char *c = new char[len2 + 1];
			cout << "Enter the number" << endl;
			cin >> c;
			XD f(b);
			XD g(c);
			XD h = f - g;
			cout << h.getString();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case MULTIPLY:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			int n;
			cout << "Enter the power of ten" << endl;
			cin >> n;
			XD f(b);
			XD h = f^n;
			cout << h.getString();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		/*case MULTIPLY:
		{
		int len1 = 0;
		cout << "enter the length of the number" << endl;
		cin >> len1;//длина числа
		char *b = new char[len1 + 1];
		cout << "" << endl;
		cin >> b;
		int len2 = 0;
		cout << "enter the length of the number" << endl;
		cin >> len2;
		char *c = new char[len2 + 1];
		cin >> c;
		XD f(b);
		XD g(c);
		XD h = f.Multiply(g);
		cout << h.getString();
		cout << endl;
		system("pause");
		system("cls");
		break;
		}*/
		case SHARE:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			int n;
			cout << "Enter the power of ten" << endl;
			cin >> n;
			XD f(b);
			XD h = f^-n;
			cout << h.getString();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		/*case SHARE:
		{
		int len1 = 0;
		cout << "enter the length of the number" << endl;
		cin >> len1;//длина числа
		char *b = new char[len1 + 1];
		cout << "" << endl;
		cin >> b;
		int len2 = 0;
		cout << "enter the length of the number" << endl;
		cin >> len2;
		char *c = new char[len2 + 1];
		cin >> c;
		XD f(b);
		XD g(c);
		XD h = f.Del(g);
		cout << h.getString();
		cout << endl;
		system("pause");
		system("cls");
		break;
		}*/
		case CONCLUSION:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			XD f(b);
			cout << f.getString();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case CONVERSION:
		{
			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			XD f(b);
			int h = unsigned long(f);
			cout << h;
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case FIL:
		{

			int len1 = 0;
			cout << "Enter the length of the number" << endl;
			cin >> len1;//длина числа
			char *b = new char[len1 + 1];
			cout << "Enter the number" << endl;
			cin >> b;
			XD f(b);
			fstream ja("algebra.txt", ios::out);
			ja << f;
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		}
	} while (a != EXIT);
	getchar();
}