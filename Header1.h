#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fstream>

using namespace std;


class XD {
private:
	static int count;
	char *arr = nullptr;
	bool min = 0;
	int length = 0;
	int len(long long x) {
		int i = 0;
		while (x != 0) {
			x /= 10;
			++i;
		}
		return i;
	}
	XD(char* _arr, int len) {
		length = len;
		arr = new char[len + 1];
		for (int i = 0; i < len; i++)
			arr[i] = _arr[i];
		arr[len] = 0;
		++count;
	}
	XD(char* _arr, bool flag) {
		int l = 0;
		while (_arr[l] != 0) {
			if (_arr[l] == '-')
				min = 1;
			++l;
		}
		if (min)
			length = l - 1;
		else
			length = l;
		arr = new char[l + 1];
		for (int i = 0; i <= length; i++) {
			if (_arr[i] == '-')
				continue;
			arr[i] = _arr[i];
		}
		++count;
	}
	XD(int* x, int len) {
		length = len;
		arr = new char[len + 1];
		for (int i = 0; i < len; i++) {
			arr[i] = x[i] + 48;
		}
		arr[len] = 0;
		++count;
	}
	int difference(char *x, char *y, char *z, int length, int min)
	{
		for (int i = 0; i < length; i++)
			z[i] = 48;
		for (int ix = 0; ix < min; ix++) // проход по всем разрядам числа, начиная с последнего, не доходя до первого
		{
			if (x[ix] < y[ix]) {
				int i = 0;
				while (x[ix + 1 + i] == 48) {
					x[ix + 1 + i++] = '9';
				}
				--x[ix + 1 + i];
				z[ix] = x[ix] + 58 - y[ix];
			}
			else {
				z[ix] = x[ix] - y[ix] + 48;
			}

		}
		for (int i = min; i < length; i++) {
			z[i] += x[i] - 48;
		}
		/*if (x[length - 1] < y[length - 1]) {
		z[length - 1] = y[length - 1] - x[length - 1] + 48;
		z[length] = '-';
		z[length + 1] = 0;
		}
		else {
		z[length - 1] = x[length - 1] - y[length - 1] + 48;
		z[length] = 0;
		}*/
		return 0;
	}
	XD Multiply(int x) {//x<10
		for (int i = 0; i < length; i++)
			arr[i] *= x;
	}
public:
	friend ostream& operator <<(ostream &,XD &);

	friend istream& operator >>(istream &, XD &);

	friend ofstream& operator <<(ofstream &, XD &);

	friend ifstream& operator >>(ifstream &, XD &);

	explicit XD(int x) {
		length = len(x);
		arr = new char[length];
		int i = 0;
		while (x != 0) {
			arr[i++] = 48 + x % 10;
			x /= 10;
		}
		arr[i] = 0;
		++count;
	}

	XD(XD &x) {
		length = x.length;
		min = x.min;
		arr = new char[length + 1];
		for (int i = 0; i <= length; i++)
			arr[i] = x.arr[i];
		arr[length] = 0;
		++count;
	}

	explicit XD(char* x) {
		if (x[0] == 0) {
			length = 0;
			arr = new char[2];
			arr[0] = '0';
			arr[1] = 0;
		}
		if (x[0] == '-')
			min = true;
		if (x[0] != '-' && (x[0] > 57 || x[0] < 48)) {
			length = 0;
			arr = new char[2];
			arr[0] = '0';
			arr[1] = 0;
		}
		int l = 1;
		while (x[l] != 0) {
			if (x[l] > 57 || x[l] < 48)
				break;
			++l;
		}
		int d = (bool)min;
		arr = new char[l + 1 - d];
		int minimum = 0;
		if (min)
			minimum = 1;
		for (int i = l - 1; i >= minimum; i--)
			arr[i - d] = x[l - i - 1 + d];
		arr[l - d] = 0;
		length = l - d;
		++count;
	}

	XD() {
		arr = new char[1];
		length = 0;
		arr[0] = 0;
	}

	operator unsigned long() {
		unsigned long res = 0;
		unsigned long gg = 0;
		int a = 0;
		char* la = getString();
		int n = 0;

		if (la[0] == '-') {
			for (int i = 0; la[i] != 0; i++) {
				a = arr[i] - 48;
				res *= 10;
				res += a;
			}
			res = res * -1;
		}
		else {
			for (int i = 0; la[i] != 0; i++) {
				a = arr[i] - 48;
				res *= 10;
				res += a;
				n++;
			}
		}
		for (int i = 1;i != n;i++) {
			gg = gg + res % 10;
			res /= 10;
			gg *= 10;
		}
		delete[]la;
		return gg;
	}

	XD &Add(XD &x) {
		int new_length = 0;
		if (min == false && x.min == false) {
			if (length > x.length)
				new_length = length + 1;
			else
				new_length = x.length + 1;
			char *buf = new char[new_length];
			for (int i = 0; i < new_length; i++) {
				buf[i] = 48;
			}
			bool a = 0;//совершился ли перенос
			for (int ix = 0; ix < new_length && ix < length && ix < x.length; ix++)
			{
				buf[ix] += x.arr[ix] + arr[ix] - 48 - 48; // суммируем последние разряды чисел
				int d = 0;
				while (buf[ix + d] - 48 > 9) {
					buf[ix + d] = buf[ix + d] - 10;
					++buf[ix + d + 1];
					if (ix + d >= x.length || ix + d >= length)
						a = 1;
					++d;
				}
				buf[ix + 1] += ((x.arr[ix] - 48) / 10); // если есть разряд для переноса, переносим его в следующий разряд
				if (buf[ix + 1] != 48)
					a = 1;
				buf[ix] = (buf[ix] - 48) % 10 + 48; // если есть разряд для переноса он отсекается
			}
			int min = (length < x.length) ? length : x.length;
			int max = (length > x.length) ? length : x.length;
			XD *t_max = (length > x.length) ? this : &x;
			for (int ix = min; ix < max; ix++) {
				buf[ix] += t_max->arr[ix] - 48;
				if (buf[ix] - 48 > 9) {
					buf[ix] = buf[ix] - 10;
					++buf[ix + 1];
				}
				else {
					a = 0;
				}
			}
			//if (buf[new_length - 1] == 0)
			if (!a)
				--new_length;
			XD *res = new XD(buf, new_length);
			delete[]buf;
			return *res;
		}
		if (min == true && x.min == true) {
			if (length > x.length)
				new_length = length + 1;
			else
				new_length = x.length + 1;
			char *buf = new char[new_length];
			for (int i = 0; i < new_length; i++) {
				buf[i] = 48;
			}
			bool a = 0;//совершился ли перенос
			for (int ix = 0; ix < new_length - 1 && ix < length - 1 && ix < x.length - 1; ix++)
			{
				buf[ix] += x.arr[ix] + arr[ix] - 48 - 48; // суммируем последние разряды чисел
				buf[ix + 1] += ((x.arr[ix] - 48) / 10); // если есть разряд для переноса, переносим его в следующий разряд
				if (buf[ix + 1] != 48)
					a = 1;
				buf[ix] = (buf[ix] - 48) % 10 + 48; // если есть разряд для переноса он отсекается
			}

			//if (buf[new_length - 1] == 0)
			if (a)
				--new_length;
			XD *res = new XD(buf, new_length);
			delete[]buf;
			return *res;
		}
		if (min == true && x.min == false) {
			min = false;
			XD res = x.Minus((*this));
			min = true;
			res.min = !res.min;
			return res;
		}
		if (min == false && x.min == true) {
			x.min = false;
			XD res = this->Minus(x);
			x.min = true;
			return res;
		}

	}

	XD operator +(XD &x) {
		int new_length = 0;
		if (min == false && x.min == false) {
			if (length > x.length)
				new_length = length + 1;
			else
				new_length = x.length + 1;
			char *buf = new char[new_length];
			for (int i = 0; i < new_length; i++) {
				buf[i] = 48;
			}
			bool a = 0;//совершился ли перенос
			for (int ix = 0; ix < new_length && ix < length && ix < x.length; ix++)
			{
				buf[ix] += x.arr[ix] + arr[ix] - 48 - 48; // суммируем последние разряды чисел
				int d = 0;
				while (buf[ix + d] - 48 > 9) {
					buf[ix + d] = buf[ix + d] - 10;
					++buf[ix + d + 1];
					if (ix + d >= x.length || ix + d >= length)
						a = 1;
					++d;
				}
				buf[ix + 1] += ((x.arr[ix] - 48) / 10); // если есть разряд для переноса, переносим его в следующий разряд
				if (buf[ix + 1] != 48)
					a = 1;
				buf[ix] = (buf[ix] - 48) % 10 + 48; // если есть разряд для переноса он отсекается
			}
			int min = (length < x.length) ? length : x.length;
			int max = (length > x.length) ? length : x.length;
			XD *t_max = (length > x.length) ? this : &x;
			for (int ix = min; ix < max; ix++) {
				buf[ix] += t_max->arr[ix] - 48;
				if (buf[ix] - 48 > 9) {
					buf[ix] = buf[ix] - 10;
					++buf[ix + 1];
				}
				else {
					a = 0;
				}
			}
			//if (buf[new_length - 1] == 0)
			if (!a)
				--new_length;
			XD *res = new XD(buf, new_length);
			delete[]buf;
			return *res;
		}
		if (min == true && x.min == true) {
			if (length > x.length)
				new_length = length + 1;
			else
				new_length = x.length + 1;
			char *buf = new char[new_length];
			for (int i = 0; i < new_length; i++) {
				buf[i] = 48;
			}
			bool a = 0;//совершился ли перенос
			for (int ix = 0; ix < new_length - 1 && ix < length - 1 && ix < x.length - 1; ix++)
			{
				buf[ix] += x.arr[ix] + arr[ix] - 48 - 48; // суммируем последние разряды чисел
				buf[ix + 1] += ((x.arr[ix] - 48) / 10); // если есть разряд для переноса, переносим его в следующий разряд
				if (buf[ix + 1] != 48)
					a = 1;
				buf[ix] = (buf[ix] - 48) % 10 + 48; // если есть разряд для переноса он отсекается
			}

			//if (buf[new_length - 1] == 0)
			if (a)
				--new_length;
			XD *res = new XD(buf, new_length);
			delete[]buf;
			return *res;
		}
		if (min == true && x.min == false) {
			min = false;
			XD res = x.Minus((*this));
			min = true;
			res.min = !res.min;
			return res;
		}
		if (min == false && x.min == true) {
			x.min = false;
			XD res = this->Minus(x);
			x.min = true;
			return res;
		}

	}

	char* getString() {
		char* str = new char[length + 1];
		for (int i = 0;i < length;i++)
			str[i] = arr[length - i - 1];
		str[length] = 0;
		return str;
	}

	XD operator -(XD &x) {
		if (!min&&x.min) {
			x.min = 0;
			XD res = this->Add(x);
			x.min = 1;
			return res;
		}
		if (min && !x.min) {
			min = false;
			XD res = Add(x);
			min = true;
			res.min = true;
			return res;
		}
		int k = 3; // если к == 3, значит числа одинаковой длинны
		int new_length = length;
		if (length > x.length)
		{
			new_length = length;
			k = 1; // если к == 1, значит первое число длиннее второго
		}
		else
			if (x.length > length)
			{
				new_length = x.length;
				k = 2; // если к == 2, значит второе число длиннее первого
			}
			else // если числа одинаковой длинны, то необходимо сравнить их веса
				for (int ix = 0; ix < length; ix++) // поразрядное сравнение весов чисел
				{
					if (arr[ix] > x.arr[ix]) // если разряд первого числа больше
					{
						k = 1; // значит первое число длиннее второго
						break; // выход из цикла for
					}

					if (x.arr[ix] > arr[ix]) // если разряд второго числа больше
					{
						k = 2; // значит второе число длиннее первого
						break; // выход из цикла for
					}
				} // конец for
		char *c = new char[length + 2];
		char *arrcpy = new char[length + 1];
		for (int i = 0; i < length + 1; i++)
			arrcpy[i] = arr[i];
		char *xarrcpy = new char[x.length + 1];
		for (int i = 0; i < x.length + 1; i++)
			xarrcpy[i] = x.arr[i];
		if (k == 1) difference(arrcpy, xarrcpy, c, new_length, x.length);
		if (k == 2) difference(xarrcpy, arrcpy, c, new_length, length);
		while (c[new_length - 1] < 48 || c[new_length - 1]>57)
			--new_length;
		XD a(c, new_length);
		if (k == 2)
			a.min = x.min;
		if (k == 1)
			a.min = min;
		delete[]arrcpy;
		delete[]xarrcpy;
		delete[]c;
		return a;
	}

	XD &Minus(XD &x) {
		if (!min&&x.min) {
			x.min = 0;
			XD res = this->Add(x);
			x.min = 1;
			return res;
		}
		if (min && !x.min) {
			min = false;
			XD res = Add(x);
			min = true;
			res.min = true;
			return res;
		}
		int k = 3; // если к == 3, значит числа одинаковой длинны
		int new_length = length;
		if (length > x.length)
		{
			new_length = length;
			k = 1; // если к == 1, значит первое число длиннее второго
		}
		else
			if (x.length > length)
			{
				new_length = x.length;
				k = 2; // если к == 2, значит второе число длиннее первого
			}
			else // если числа одинаковой длинны, то необходимо сравнить их веса
				for (int ix = 0; ix < length; ix++) // поразрядное сравнение весов чисел
				{
					if (arr[ix] > x.arr[ix]) // если разряд первого числа больше
					{
						k = 1; // значит первое число длиннее второго
						break; // выход из цикла for
					}

					if (x.arr[ix] > arr[ix]) // если разряд второго числа больше
					{
						k = 2; // значит второе число длиннее первого
						break; // выход из цикла for
					}
				} // конец for
		char *c = new char[length + 2];
		char *arrcpy = new char[length + 1];
		for (int i = 0; i < length + 1; i++)
			arrcpy[i] = arr[i];
		char *xarrcpy = new char[x.length + 1];
		for (int i = 0; i < x.length + 1; i++)
			xarrcpy[i] = x.arr[i];
		if (k == 1) difference(arrcpy, xarrcpy, c, new_length, x.length);
		if (k == 2) difference(xarrcpy, arrcpy, c, new_length, length);
		while (c[new_length - 1] < 48 || c[new_length - 1]>57)
			--new_length;
		XD a(c, new_length);
		if (k == 2)
			a.min = x.min;
		if (k == 1)
			a.min = min;
		delete[]arrcpy;
		delete[]xarrcpy;
		delete[]c;
		return a;
	}

	XD &operator ^(int n) {
		if (length + n <= 0)
			return *(new XD(0));
		if (n > 0) {
			int new_length = n + this->length + 1;
			char *c = new char[new_length];
			for (int i = new_length - 2; i >= n; i--)
				c[i] = arr[i - n];
			for (int i = n - 1;i >= 0;i--)
				c[i] = 48;
			c[new_length - 1] = 0;
			XD* res = new XD(c, false);
			return *res;
		}
		else {
			int new_length = n + this->length + 1;
			char *c = new char[new_length];
			int k = 0;
			n = -n;
			for (int i = n; i <= length; i++) {
				c[k++] = arr[i];
			}
			return *(new XD(c, false));
		}
	}

	XD &Multiply(XD &x) {
		int new_length = length + x.length + 1;
		//char *c = new char[new_length];
		int *c = new int[new_length];
		for (int i = 0; i < new_length; i++)
			c[i] = 0;
		if (length <= x.length) {
			for (int ix = 0; ix < length; ix++) {
				for (int jx = 0; jx < x.length; jx++)
					c[ix + jx] += (arr[ix] - 48) * (x.arr[jx] - 48);
				//++i;
			}
		}
		else {
			for (int ix = 0; ix < x.length; ix++) {
				for (int jx = 0; jx < length; jx++)
					c[ix + jx] += (arr[jx] - 48) * (x.arr[ix] - 48);
				//++i;
			}
		}

		for (int ix = 0; ix < new_length; ix++)
		{
			c[ix + 1] += (c[ix]) / 10;
			c[ix] = (c[ix]) % 10;
		}

		while (c[new_length - 1] == 0)
			new_length--;
		XD *res = new XD(c, new_length);
		delete[]c;
		if (min^x.min)//если одно из чисел - отрицательно, то результат - отрицателен
			res->SetMinus(1);
		return *res;
	}

	void SetMinus(bool x) {
		min = x;
	}

	XD& operator=(XD& x) {
		this->length = x.length;
		if (arr)
			delete[] arr;
		arr = new char[length + 1];
		for (int i = 0; i < length; i++)
			arr[i] = x.arr[i];
		arr[length] = 0;
		return (*this);
	}

	bool isBigger(XD &x) {
		if (this->length > x.length)
			return true;
		if (x.length == length) {
			for (int i = length - 1; i >= 0; i--) {
				if (arr[i] == x.arr[i])
					continue;
				if (arr[i] > x.arr[i])
					return true;
				if (arr[i] < x.arr[i])
					return false;
			}
		}
		return false;
	}

	bool Equal(XD &x) {
		if (length != x.length)
			return false;
		for (int i = length - 1; i >= 0; i--) {
			if (arr[i] != x.arr[i])
				return false;
		}
		return true;
	}

	XD &Del(XD &x) {
		if (!isBigger(x))
			return XD(0);
		int i = 0;
		XD t = x;
		while (isBigger(t)) {
			if (i == 499)
				int a = 0;
			t = t.Add(x);
			++i;
		}
		if (Equal(t))
			return XD(i + 1);
		else
			return XD(i);
	}

	/*fstream fil(XD &x)	 {
		fstream ja("algebra.txt", ios::out);
	}*/

	~XD() {
		if (arr != nullptr)
			delete[]arr;
		arr = nullptr;
		--count;
	}
};

int XD::count = 0;

ostream& operator<<(ostream &os, XD &x)
{
	os << x.getString();
	return os;
}

istream& operator >> (istream &os, XD &x)
{
	return os;
}

ofstream& operator <<(ofstream &of, XD &x)
{
//	of << &x.len;
//	return of;
}

ifstream& operator >> (ifstream &os, XD &x)
{
	return os;
}


