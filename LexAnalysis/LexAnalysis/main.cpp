#include<iostream>
#include"Lex.h"
using namespace std;

int main()
{
	Lex lex;
	lex.init();  
	cout << "过滤前的代码:" << endl;
	cout << lex.BufferCode<< endl;
	fprintf(lex.fout, "过滤前的代码    %s\n", lex.BufferCode);
	lex.filter();
	cout << "过滤后的的代码:" << endl;
	cout << lex.BufferCode <<endl; //输出字符串遇到"/0"就停下
	fprintf(lex.fout, "过滤后的代码    %s\n", lex.BufferCode);
	
	char token[MaxLen];//每次扫描的字符存在token里
	int state =-1;//初始化 种别码
	lex.pos = 0;
	while (state != 0) //种别码 为0时说明扫描到了 EOF,既文件结束标志
	{

	//	printf("lex.pos=%d   %c\n", lex.pos, lex.BufferCode[lex.pos]);
		lex.Scanner(state,lex.pos,token); 
		if (state >= 1 && state <= 35)//种别码为关键字
		{
			fprintf(lex.fout, "关键字    %s\n", token);
		}
		else if (state >= 36 && state <= 71)//种别码界限符
		{
			fprintf(lex.fout, "界限符    %s\n", token);
		}
		else if (state == 99)//种别码为数字
		{
		   fprintf(lex.fout, "数字    %s\n",token);
		}
		else if (state == 100)//种别码为标识符
		{
			fprintf(lex.fout, "标识符    %s\n", token);
		}

	}

	return 0;
}