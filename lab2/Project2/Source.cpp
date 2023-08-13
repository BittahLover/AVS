#include <iostream>
#include <stdio.h>
#include <math.h>
//
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>

using namespace std;

int binaryproduct(int, int);
string to2(long x);
string toReverse(string value);


int bits = 8;
long binary1, binary2, multiply = 0;
long int1, int2;
string sa, sb;

int main()
{

    int digit, factor = 1;
    cout << "Enter a first integer number: ";
    cin >> int1;
    cout << "Enter a first integer number: ";
    cin >> int2;

    if (int1 == 0 || int2 == 0) {
        printf("Product of two binary numbers: 0");
        return 0;
    }

    cout << "\nFirst number in binary code: ";
    if (int1 < 0) {
        cout << toReverse(to2(int1)) << endl;
        sa = to2(-int1);
    }
    else {
        cout << to2(int1) << endl;
        sa = to2(int1);
    }

    cout << "Second number in binary code:";
    if (int2 < 0) {
        cout << toReverse(to2(int2)) << endl;
        sb = to2(-int2);
    }
    else {
        cout << to2(int2) << endl;
        sb = to2(int2);
    }


    binary1 = stoi(sa);
    binary2 = stoi(sb);
    //cout<<binary1<<endl;
    //cout<<binary2<<endl;


    while (binary2 != 0)
    {
        digit = binary2 % 10;
        if (digit == 1)
        {
            binary1 = binary1 * factor;
            multiply = binaryproduct(binary1, multiply);
        }
        else
            binary1 = binary1 * factor;
        binary2 = binary2 / 10;
        factor = 10;
    }

    int count = 0;
    int numb = multiply;
    while (numb) {
        numb /= 10;
        count++;
    }

    
    cout << "\nProduct of two binary numbers: overflow" << endl;
    /*if (int1 * int2 > 0) cout << multiply;
    else
    {
        cout << '1';
        for (int i = 1; i < bits - count; i++)
            cout << '0';
        cout << multiply;
    }
    */
    return 0;
}

int binaryproduct(int binary1, int binary2)
{
    int i = 0, remainder = 0, sum[20];
    int binaryprod = 0;

    while (binary1 != 0 || binary2 != 0)
    {
        sum[i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;
        remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;
        binary1 = binary1 / 10;
        binary2 = binary2 / 10;
    }
    if (remainder != 0)
        sum[i++] = remainder;
    --i;
    while (i >= 0)
        binaryprod = binaryprod * 10 + sum[i--];
    return binaryprod;
}

string to2(long x) {
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
