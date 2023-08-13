#include <string> 
#include <iostream>

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
	double n, m;
	int k;
	std::cout << "Input digits(fractions): ";
	std::cin >> n >> m;
	if (m == 0.0)
	{
		std::cout << "Division by zero" << std::endl;
		return 0;
	}
	std::cout << "how many digits after the decimal point? ";
	std::cin >> k;
	std::cout << "\ndigit in binary: \n";
	std::cout << decimalToBinary(n, k) << std::endl;
	std::cout << decimalToBinary(m, k) << std::endl;
	double f = n / m;
	if (abs(f) > 255)
	{
		std::cout << "\nOverflow" << std::endl;
		return 0;
	}
	std::cout << "Answer:  ";
	std::cout << decimalToBinary(f, k) << std::endl;
	std::cout << f << std::endl;
	return 0;
}
