#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include<limits>

using namespace std;
double n, bin, f1 = 0.0, f2, f3 = 0.1;
#include <stdio.h>

void printBinary(int n, int i)

{

	int k;

	for (k = i - 1; k >= 0; k--) {
		if ((n >> k) & 1)
			printf("1");
		else
			printf("0");
	}
}

typedef union {
	float f;
	struct
	{
		unsigned int mantissa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	} raw;

} myfloat;

int* MakeArr(int* array, myfloat var);
int* Division(int* arr1, int* arr2, int* arr3);

void printIEEE(myfloat var)

{
	printf("%d | ", var.raw.sign);
	printBinary(var.raw.exponent, 8);
	printf(" | ");
	printBinary(var.raw.mantissa, 23);
	printf("\n");
}

std::string decimalToBinary(double num, int k_prec)
{
	std::string binary = "";
	int Integral = num;
	double fractional = num - Integral;

	while (Integral)
	{
		int rem = Integral % 2;
		binary.push_back(rem + '0');
		Integral /= 2;
	}

	reverse(binary.begin(), binary.end());
	binary.push_back('.');

	while (k_prec--)
	{
		fractional *= 2;
		int fract_bit = fractional;

		if (fract_bit == 1)
		{
			fractional -= fract_bit;
			binary.push_back(1 + '0');
		}
		else
			binary.push_back(0 + '0');
	}
	return binary;
}

int main()

{
	setlocale(LC_ALL, "Russian");
	myfloat var, var2, div;
	float float_max = fabs(numeric_limits<float>::max());
	float float_min = fabs(numeric_limits<float>::min());
	float num, num2;
	cout << "Limit of float: " << endl << float_max << endl;
	cout << "Limit of float: " << endl << float_min << endl;
	cout << "First number: ";
	cin >> num;
	cout << "Second number: ";
	cin >> num2;
	if (num2 == 0)
	{
		printf("Деление на 0\n");
		return 0;
	}
	var.f = num;
	var2.f = num2;
	div.f = num / num2;

	printf("\n\nRepresentation of %f is : \n", var.f);
	printIEEE(var);
	printf("\nRepresentation of %f is : \n", var2.f);
	printIEEE(var2);

	int* arr1 = new int[32];
	arr1 = MakeArr(arr1, var);
	int* arr2 = new int[32];
	arr2 = MakeArr(arr2, var2);
	int* arr3 = new int[32];
	arr3 = Division(arr1, arr2, arr3);

	if (fabs(num / num2) >= float_max)
	{
		cout << "\nПереполнение";
		return 0;
	}
	else if (fabs(num / num2) <= pow(0.1, 25))
	{
		cout << "\nПотеря значимости";
		return 0;
	}
	
	else
	{
		cout << "\n\nDecimal division is : \n" << div.f;
		cout << "\nBinary division is : \n";
		printIEEE(div);
	}
	return 0;

}

int* MakeArr(int* num, myfloat var) {
	num[0] = var.raw.sign;
	for (int j = 0; j < 32; j++)
		num[j] = 0;
	int k;
	int n = var.raw.exponent;
	int i = 8;
	for (k = i - 1; k >= 0; k--) {
		if ((n >> k) & 1)
			num[8 - k] = 1;
		else
			num[8 - k] = 0;
	}

	n = var.raw.mantissa;
	i = 23;
	int z = 9;

	for (k = i - 1; k >= 0; k--) {
		if ((n >> k) & 1)
			num[z] = 1;
		else
			num[z] = 0;
		z++;
	}
	return num;
}

int* Division(int* arr1, int* arr2, int* sum) {
	for (int i = 31; i >= 0; i--)
	{
		sum[i] = arr1[i] - arr2[i];
	}
	return sum;
}
