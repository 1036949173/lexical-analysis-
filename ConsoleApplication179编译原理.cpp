// ConsoleApplication179编译原理作业1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//不显示窗口  

#define NUMOFKEYS              8              //关键词数量
#define MAXSIZEOFMARKSIGN      15             //最大储存标识符数量
#define MAXSIZEOFCONSTANT      15             //最大储存常量数量
#define RELATIONSIZE           6              //关系运算符数量
#define DELIMITER              6              //分界符数量
#define SIZEOFONELINEINPUT     100
string keys[NUMOFKEYS] = { "do", "end", "for", "If", "printf", "scanf", "then", "while" };    //关键字表
string idenSign[MAXSIZEOFMARKSIGN];                           //标识符表
unsigned constants[MAXSIZEOFCONSTANT];                           //常量表
string relaSign[RELATIONSIZE] = { "<", "<=", "=", ">", ">=", "<>" }; //关系运算符
char limSign[DELIMITER] = { ',', ';', '(', ')', '{', '}' };         //分界符表
string inputLine;
string word;
int splitPos;
int T, I, row, column;
int Liden, Lcons;    //length of identifier list and constant list
string temp1, temp2, temp3;

int searchInKeys(string a)
{
	int i;
	for (i = 0; i < NUMOFKEYS; i++)
	{
		if (a == keys[i])
			return i;
	}
	return -1;
}
int searchInidenSign(string a)
{
	int i;
	for (i = 0; i < Liden; i++)
	{
		if (a == idenSign[i])
			return i;
	}
	return -1;
}

int searchInCons(int a)
{
	int i;
	for (i = 0; i < Lcons; i++)
	{
		if (a == constants[i])
			return i;
	}
	return -1;
}

string splitToKeys(int& pos)
{
	int i;
	int tpos = pos;
	for (i = pos+1; i < inputLine.size(); i++)
	{
		if ('a' <= inputLine[i] && inputLine[i] <= 'z' || 'A' <= inputLine[i] && inputLine[i] <= 'Z')
		{
			continue;
		}
		else
		{
			pos = i;
			return inputLine.substr(tpos, i-tpos);
		}
	}
	pos = i;
	return inputLine.substr(tpos, i-tpos);
}
string splitToConstant(int& pos)
{
	int i;
	int tpos = pos;
	for (i = pos+1; i < inputLine.size(); i++)
	{
		if ('0' <= inputLine[i] && inputLine[i] <= '9')
		{
			continue;
		}
		else
		{
			pos = i;
			return inputLine.substr(tpos, i-tpos);
		}
	}
	pos = i;
	return inputLine.substr(tpos, i-tpos);
}

string splitToRelaSign(int& pos)
{
	int i;
	string ttmp;
	for (i = pos + 1; i < inputLine.size(); i++)
	{
		if (inputLine[i] == '=')
		{
			ttmp = inputLine.substr(pos, 2);	
			pos += 2;
			return ttmp;
		}
		else
		{
			pos++;
			ttmp = inputLine[pos-1];
			return ttmp;
		}
	}
	pos++;
	ttmp = inputLine[pos - 1];
	return ttmp;
}

string splitToArithmeticSign(int& pos)
{
	int i;
	string ttmp;
	for (i = pos + 1; i < inputLine.size(); i++)
	{
		if (inputLine[pos] == '-'&&inputLine[i]=='-'|| inputLine[pos] == '+'&&inputLine[i] == '+')
		{
			ttmp = inputLine.substr(pos, 2);
			pos += 2;
			return ttmp;
		}
		else
		{
			pos++;
			ttmp = inputLine[pos - 1];
			return ttmp;
		}
	}
	pos++;
	ttmp = inputLine[pos - 1];
	return ttmp;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	fstream stream("in.txt");	
	while (getline(stream, inputLine))                        
	{
		row++;
		column = 0;
		splitPos = 0;
		while (splitPos < inputLine.size())
		{
			if (inputLine[splitPos] == ' ')
			{
				splitPos++;
			}
			else if ('a' <= inputLine[splitPos] && inputLine[splitPos] <= 'z' || 'A' <= inputLine[splitPos] && inputLine[splitPos] <= 'Z')
			{
				column++;
				word = splitToKeys(splitPos);
				I = searchInKeys(word);
				if (I >= 0)
				{
					T = 1;
					temp1 = "(" + to_string(T) + ", " + word + ")";
					temp2 = "关键字";
					printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
				}
				else
				{
					I = searchInidenSign(word);
					T = 6;
					if (I >= 0)
					{
						temp1 = "(" + to_string(T) + ", " + word + ")";
						temp2 = "标识符";
						printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
					}
					else
					{
						idenSign[Liden++] = word;
						temp1 = "(" + to_string(T) + ", " + word + ")";
						temp2 = "标识符";
						printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
					}
				}
			}
			else if ('0' <= inputLine[splitPos] && inputLine[splitPos] <= '9')
			{
				column++;
				word = splitToConstant(splitPos);
				if ('a' <= inputLine[splitPos] && inputLine[splitPos] <= 'z' || 'A' <= inputLine[splitPos] && inputLine[splitPos] <= 'Z')
				{
					string tt = splitToKeys(splitPos);
					word += tt;
					temp1 = "Error";
					temp2 = "Error";
					printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
					continue;
				}
				I = searchInCons((unsigned)atoi(word.c_str()));
				T = 5;
				if (I >= 0)
				{
					temp1 = "(" + to_string(T) + ", " + word + ")";
					temp2 = "常量";
					printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
				}
				else
				{
					constants[Lcons++] = atoi(word.c_str());
					temp1 = "(" + to_string(T) + ", " + word + ")";
					temp2 = "常量";
					printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
				}
			}
			else if (inputLine[splitPos] == '+' || inputLine[splitPos] == '-' || inputLine[splitPos] == '*' || inputLine[splitPos] == '/') //算术运算符
			{
				word = splitToArithmeticSign(splitPos);
				column++;
				T = 3;
				if (word.length() == 1)
				{
					temp1 = "(" + to_string(T) + ", " + word + ")";
					temp2 = "算术运算符";
				}
				else
				{
					temp1 = "Error";
					temp2 = "Error";
				}
				printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
			}
			else if (inputLine[splitPos] == '%')
			{
				word = '%';
				column++;
				temp1 = "Error";
				temp2 = "Error";
				splitPos++;
				printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
			}
			else if (inputLine[splitPos] == '<' || inputLine[splitPos] == '>' || inputLine[splitPos] == '=') //关系运算符
			{
				word = splitToRelaSign(splitPos);
				column++;
				T = 4;
				temp1 = "(" + to_string(T) + ", " + word + ")";
				temp2 = "关系运算符";
				printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
			}
			else if (inputLine[splitPos] == ',' || inputLine[splitPos] == ';' || inputLine[splitPos] == '(' 
				|| inputLine[splitPos] == ')' || inputLine[splitPos] == '[' || inputLine[splitPos] == ']')
			{
				word = inputLine[splitPos];
				splitPos++;
				column++;
				T = 2;
				temp1 = "(" + to_string(T) + ", " + word + ")";
				temp2 = "分界符";
				printf("%-15s%-15s%-15s(%d, %d)\n", word.c_str(), temp1.c_str(), temp2.c_str(), row, column);
			}

		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
