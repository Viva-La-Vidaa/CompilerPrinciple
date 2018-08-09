#ifndef _Base_H_
#define _Base_H_
#include<iostream>
#include<set>
#include<cstring>
#include<string>
#include<vector>
#include<iomanip>


using namespace std;
#define Limit  100

struct Production  //定义产生式数据结构
{
	char left;
	string right;
};

class Base
{
protected:
	int Num=0;
	Production  Analysis[Limit];                  //分析式
	vector<char> Terminal;           //终结符集
	vector<char> Not_Terminal;  //非终结符集
	set<char> First_Set[Limit];            //First集
	set<char> Follow_Set[Limit];      //Follow集

public:
   void	init();//对输入的产生式初始化,去掉  -和>
   bool is_Not_Terminal(char c);
   void Get_First(char c);
   void Get_Follow(char c);
   int Get_Tindex(char c);
   int Get_Nindex(char c);
   void Print_FirstAndFollow(); 

};

#endif