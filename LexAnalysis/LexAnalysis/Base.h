#ifndef _Base_H_
#define _Base_H_
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define MaxLen 100
//全局变量，关键字表,
//state的值对应关键字,从1到35
extern char KeyWord[35][20];

 //界限符表
 //state的值对应关键字,从36到72
extern char OperatorOrDelimiter[37][10];
class Base
{
   public:
	   bool is_Digtal(char);  //字符是否是数字	
	   bool is_Characters(char);//字符是否是大小写字母
	   bool is_SingleOperatorOrDelimiter(char);//字符是否是  长度为1的界限符
	   int SearchKeyWord(char [][20],char []);
};
#endif