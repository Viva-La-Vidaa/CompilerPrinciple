#ifndef _LEX_H_
#define _LEX_H_
#include "Base.h"

class Lex:public Base
{
          public:
			  FILE *fin;
			  FILE *fout;
			  Lex();
			  ~Lex();
			  char BufferCode[10000];    // 用来存储输入的代码
			  int pos = 0;                 
			  void init(); //初始化将代码拷贝到 BufferCode数组中
			  void filter();//过滤BufferCode中的代码,去除//和/*  */的内容，以及一些无用的、影响程序执行的符号如换行符、回车符、制表符等等
			  void Scanner(int &,int &,char[]);//扫描BufferCode,核心代码,实现了确定有限自动机的某些功能		  

};
#endif