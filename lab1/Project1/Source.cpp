#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include<limits>

using namespace std;

int bits = 8;
long long a, b;

string to2(long long x) {
	string value = "";
	for (int i = 0; i < bits; i++)value += '0';
	//if(x<0)value[0]='1';
	x = abs(x);
	for (int i = 0; x > 0; i++) {
		int j = bits - i - 1;
		value[j] = (x % 2) ? '1' : '0';
		x /= 2;
	}
	return value;
}

string toReverse(string value) {
	value[0] = '1';
	for (int i = 1; i < value.length(); i++) {
		value[i] = (value[i] == '1') ? '0' : '1';
	}
	return value;
}


string sum(string e, string q) {
	string val = "";
	for (int i = 0; i < bits; i++)val += "0";
	bool pre = false, last = false;

	for (int i = bits - 1; i >= 0; i--) {
		pre = last;
		last = false;
		if (e[i] == q[i]) {
			last = e[i] == '1';
			val[i] = '0';
		}
		else val[i] = '1';
		if (pre) {
			val[i] = (val[i] == '0') ? '1' : '0';
			last = (last || val[i] == '0');
		}
		pre = false;
	}
	if (last) {
		return sum(val, to2(1));
	}
	return val;
}

string toTwoComplement(string input)
{
	string sec_str = "";
	for (int i = 0; i < bits; i++) sec_str += '0';
	sec_str[bits - 1] = '1';

	string out = sum(input, sec_str);
	return out;
}

int main()
{
	//cout << "How many bits?(1 for sign)" << endl;
	//cin >> bits;
	cout << "Enter a first integer number: ";
	cin >> a;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "You have entered wrong input" << endl;
			cin >> a;
		}
		if (!cin.fail())
			break;
	}
	cout << "Enter a second integer number: ";
	cin >> b;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> b;
		}
		if (!cin.fail())
			break;
	}
/*
	if (bits <= 1 || powl(2, bits - 1) < abs(a) || powl(2, bits - 1) < abs(b)) {
		cout << "OverFlow of input number" << endl;
		return 0;
	}*/
	string sa, sb, smb; // binary code
	string a_twos, b_twos; // two's complement
	//binary
	if (a < 0) sa = toReverse(to2(a));
	else sa = to2(a);

	if (b < 0) sb = toReverse(to2(b));
	else sb = to2(b);

	if (-b < 0) smb = toReverse(to2(-b));
	else smb = to2(-b);
	//two's complement
	if (a >= 0) a_twos = sa; else a_twos = toTwoComplement(sa);
	if (b >= 0) b_twos = sb; else b_twos = toTwoComplement(sb);

	//output
	cout << "\nFirst number in binary code: \n";
	cout << to2(a) << endl;
	cout << "Second number in binary code: \n";
	cout << to2(b) << endl;

	cout << "\nTwo's complement for 1: \n";
	cout << a_twos << endl;
	cout << "Two's complement for 2: \n";
	cout << b_twos << endl;



	cout << "\nSum of two in twos completion: \n";
	if ((a + b) > pow(2, bits - 1) - 1 || (a + b) < -pow(2, bits - 1))
		cout << "Overflow\n";
	else
		cout << ((a + b < 0) ? toReverse(sum(sa, sb)) : (sum(sa, sb))) << endl;
	cout << "Sum of two in decimals: ";
	cout << a + b << endl << endl;

	cout << "\Substruction of two in twos completion: \n";
	if ((a - b) > pow(2, bits - 1) - 1 || (a - b) < -pow(2, bits - 1))
		cout << "Overflow\n";
	else
		cout << ((a - b < 0) ? toReverse(sum(sa, smb)) : (sum(sa, smb))) << endl;
	cout << "Substruction of two in decimals: ";
	cout << a - b << endl;
	return 0;
}
