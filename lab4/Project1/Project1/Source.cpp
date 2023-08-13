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
int* Addition(int* arr1, int* arr2, int* arr3);

void printIEEE(myfloat var)
{


    printf("%d | ", var.raw.sign);
    printBinary(var.raw.exponent, 8);
    printf(" | ");
    printBinary(var.raw.mantissa, 23);
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Russian");
    myfloat var, var2, razn, summ;
    float float_max = fabs(numeric_limits<float>::max());
    float float_min = (numeric_limits<float>::min());
    float num, num2;
    cout << "Limit of program: " << endl << float_max << endl;
    cout << "Limit of program: " << endl << float_min << endl;
    cout << "Enter first number: ";
    cin >> num;
    cout << "Enter second number: ";
    cin >> num2;
    


    var.f = num;
    var2.f = num2;
    summ.f = num + num2;
    razn.f = num - num2;

    printf("\n\nBinary representation of %f is : \n", var.f);
    printf("sign|exponent|mantissa");
    printIEEE(var);

    printf("\nBinary representation of %f is : \n", var2.f);
    printIEEE(var2);

    int* arr1 = new int[32];
    arr1 = MakeArr(arr1, var);
    int* arr2 = new int[32];
    arr2 = MakeArr(arr2, var2);

    int* arr3 = new int[32];
    arr3 = Addition(arr1, arr2, arr3);

    if ((num - num2) >= float_max)
    {
        cout << "\nПереполнение в операции вычитания";
        return 0;
    }
    else if ((num - num2) <= pow(0.1, 25))
    {
        cout << "\nПотеря значимости в операции вычитания";
        return 0;
    }

    else
    {
        cout << "\n\nDecimal substraction is : \n" << razn.f;
        cout << "\nBinary substraction  is : \n";
        printIEEE(razn);
    }

    if (fabs(num + num2) >= float_max)
    {
        cout << "\nПереполнение в операции сложения";
        return 0;
    }
    else if ((num + num2) <= pow(0.1, 25))
    {
        cout << "\nПотеря значимости в операции сложения";
        return 0;
    }
    else
    {
        cout << "\n\nDecimal summ is : \n" << summ.f;
        cout << "\nBinary summ  is : \n";
        printIEEE(summ);
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

int* Addition(int* arr1, int* arr2, int* sum) {
    for (int i = 31; i >= 0; i--)
    {
        sum[i] = arr1[i] + arr2[i];

    }

    return sum;
}
