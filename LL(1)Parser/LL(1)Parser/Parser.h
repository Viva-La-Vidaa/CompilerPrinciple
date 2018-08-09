#ifndef _Parser_H_
#define _Parser_H_
#include "Base.h"

class Parser:public Base
{
	int Analysis_Table[Limit][Limit];
	vector<char> Left_Analysis_Str;//待分析的字符串
	vector<char> S;//符号栈,用vector模拟stack.便于输出分析过程

public:
	void Get_Table();
	void Print_Table();
	void Analysis_Program(string s);

};
#endif