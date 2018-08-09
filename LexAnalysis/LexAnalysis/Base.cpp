#include "Base.h"

char KeyWord[35][20] = {     //使用const,修改函数参数即可
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long", "register",
	"return", "short", "signed", "sizeof", "static", "struct",
	"switch", "true", "false", "typedef", "union", "signed",
	"unsigned", "void", "volatile", "while" };

char OperatorOrDelimiter[37][10] = {
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",    //    \\    代表一个反斜线字符''\'
	"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",          //     \'    代表一个单引号（撇号）字符
	"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",   //     \"   代表一个双引号字符
	"}", "\\", ".", "\?", ":", "!" };


bool Base::is_Digtal(char c)
{
	if (c >= '0'&&c <= '9')
		return true;
	else
		  return false;
}

bool Base::is_Characters(char c)
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z')||c=='_')
		return true;
	else
		return	false;
}

bool Base::is_SingleOperatorOrDelimiter(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == ';' || c == '(' || c == ')' || c == '^' ||
		c == ',' || c == '\"' || c == '\'' || c == '~' || c == '#' || c == '%' || c == '[' || c == ']'
		|| c == '{' || c == '}' || c == '\\' || c == '.' || c == '\?' || c == ':'||c=='$')
		return true;
	else
		return false;
}

int Base::SearchKeyWord(char KeyWord[][20],char token[])
{
	for (int i = 0; i < 35; i++)
	{
		if (strcmp(KeyWord[i], token) == 0)
			return i + 1;		
	}
	return -1;
	
}