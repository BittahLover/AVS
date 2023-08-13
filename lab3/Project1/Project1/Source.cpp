#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int getIntFromBinaryText(const char* text)
{
    int value = 0;
    while (*text)
    {
        value <<= 1;
        if (*text == '1')    value |= 1;
        else if (*text == '0');          // do nothing
        else                     return -1; // invalid input... return a negative number to indicate error
        ++text;
    }

    return value;
}

std::string getBinaryTextFromInt(int value)
{
    std::string text;
    // note I'm assuming 'value' is positive here

    while (value > 0)
    {
        if (value & 1)       text += '1';
        else                text += '0';
        value >>= 1;
    }

    if (text.empty())        return "0";
    std::reverse(text.begin(), text.end());       // #include <algorithm>
    return text;
}

int main()  // note:  main... not that _tmain garbage.
{
    int divisor = getIntFromBinaryText("1011");  // or just "divisor = 11;"

    std::string text;
    cout << " dividend ?" << endl;
    cin >> text;

    int dividend = getIntFromBinaryText(text.c_str());
    if (dividend < 0)
    {
        cout << "Invalid input";
        return 1;
    }

    int result = dividend / divisor;
    int remainder = dividend % divisor;

    cout << "dividend=" << getBinaryTextFromInt(dividend);
    cout << "    divisor=" << getBinaryTextFromInt(divisor);
    cout << "    result=" << getBinaryTextFromInt(result);
    cout << "    remainder=" << getBinaryTextFromInt(remainder);

}