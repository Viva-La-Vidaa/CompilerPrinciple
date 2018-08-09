#include "Parser.h"

int main()
{
	Parser parser;
	parser.init();
	parser.Print_FirstAndFollow();//输出First集与Follow集
	parser.Get_Table();
	cout << "请输入分析字符串:"<<endl;
	cout << setw(15)<< "分析栈" << setw(15) << "剩余输入串" << setw(15) << "产生式" << endl;
	string str;
	cin >> str;
	parser.Analysis_Program(str);
	return 0;
}