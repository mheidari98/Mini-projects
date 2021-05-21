/***************************************************************************//**

  @file         RomanNumber.cpp

  @author       mahdi heidari

  @date         I don't remember

  @brief        C Program to convert Roman Number to Decimal Number, and vice versa.

  @compile      g++ RomanNumber.cpp -o RomanNumber

*******************************************************************************/
#include <iostream> 
#include <string>
#include <iterator> 
#include <map> 
#include <Windows.h>

using namespace std;

void setTextColor(int textColor, int backColor = 0)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

string to_roman(unsigned int value)
{
	struct romandata_t 
	{ 
		unsigned int value; 
		char const* numeral; 
	};

	const struct romandata_t romandata[] =
	{
		{1000, "M"}, {900, "CM"},
		{500, "D"}, {400, "CD"},
		{100, "C"}, { 90, "XC"},
		{ 50, "L"}, { 40, "XL"},
		{ 10, "X"}, { 9, "IX"},
		{ 5, "V"}, { 4, "IV"},
		{ 1, "I"}, { 0, NULL} // end marker
	};

	string result;
	for (const romandata_t* current = romandata; current->value > 0; ++current)
	{
		while (value >= current->value)
		{
			result += current->numeral;
			value -= current->value;
		}
	}
	return result;
}
int romanToInt(string s) {

	map<char, int> m = { {'I', 1}, {'V', 5},{'X', 10},{'L', 50},{'C', 100},{'D', 500},{'M', 1000} };

	int total = 0;
	for (int i = 0; i < s.length(); i++) {
		if (m[s[i]] < m[s[i + 1]])
			total -= m[s[i]];
		else
			total += m[s[i]];
	}
	return total;
}
int main()
{

	int n, k;
	string s;

	while (1)
	{
		setTextColor(10, 0);
		cout << "\n 1.integer to Roman Numeral\n";
		cout << " 2.Roman Number to Decimal Number\n";
		cout << " 3.Exit\n";
		setTextColor(11, 0);
		cout << "\n please choose one : ";
		setTextColor(7, 0);
		cin >> n;
		setTextColor(1, 0);
		cout << "----------------------------------\n";
		setTextColor(7, 0);
		if (n == 1)
		{
			cout << " Please enter number to convert to Roman Numeral : ";
			cin >> k;
			setTextColor(6, 0);
			cout << "\t " << k << " = " << to_roman(k) << endl;
			setTextColor(7, 0);
		}
		else if (n == 2)
		{
			cout << " Please enter Roman Numeral to convert to Decimal Number : ";
			cin >> s;
			setTextColor(6, 0);
			cout << "\t " << s << " = " << romanToInt(s) << endl;
			setTextColor(7, 0);
		}
		else if (n == 3)
			break;
		else
		{
			setTextColor(4);
			cout << "\t Wrong input\n";
			setTextColor(7,0);
		}
		setTextColor(1, 0);
		cout << "----------------------------------\n\n\n";
		setTextColor(7, 0);
	}
}
