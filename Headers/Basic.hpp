#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;
namespace nummap
{
	#define INTMAX numeric_limits<int>::max()
	#define INTMIN numeric_limits<int>::min()
	int numdigits(int num)
	{
		int digits = 0;
		for(int i = 1; ; i *= 10)
		{
			if(num / i)digits++;
			else if(i == 1)return 1;
			else break;
		}
		return digits;
	}
	int ithdigit(int num, int index)
	{
		int digs = numdigits(num);
		if(index > digs)return INTMAX;
		if(index < 1)return INTMIN;
		num /= pow(10, index - 1);
		return num % 10;
	}
}
namespace strmap
{
	char to_char(int num)
	{
		return num + 48;
	}
	bool strcheck(const char* str, const char* check)
	{
		int found = 0;
		if(strlen(str) < strlen(check))return 0;
		int* chk = new int[strlen(check)];
		for(int i = 0; i < strlen(check); i++) chk[i] = -1;
		if( !str || !check)return 0;
		for(int i = 0; check[i] != '\0'; i++)
		{
			for(int j = 0; str[j] != '\0'; j++)
			{
				if(str[j] == check[i])
				{
					chk[i] = j;
				}
			}
		}
		for(int i = 0; i < strlen(check) - 1; i++)
		{
			if(chk[i + 1] - chk[i] != 1)return 0;
		}
		return 1;
	}
	char* to_c_str(int num)
	{
		int digs = nummap::numdigits(num);
		char* c_str = new char[digs + 1];
		for(int i = 0; i < digs; i++)
		{
			c_str[i] = to_char(nummap::ithdigit(num, digs - i));
		}
		//c_str[digs] = '/0';
		return c_str;
	}
	string to_str(int num)
	{
		int digs = nummap::numdigits(num);
		string str;
		for(int i = 0; i < digs; i++)
		{
			str.push_back(to_char(nummap::ithdigit(num, digs - i)));
		}
		return str;
	}
	const char* to_cc_str(int num)
	{
		return (const char*)to_c_str(num);
	}
}
