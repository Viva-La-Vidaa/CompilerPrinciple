#include "Parser.h"

void Parser::Get_Table()
{
	memset(Analysis_Table, -1, sizeof(Analysis_Table));//初始化分析表,置为-1
	for (int i = 0; i<Num; i++)
	{
		char temp = Analysis[i].right[0];
		if (!is_Not_Terminal(temp))//如果是终结符
		{
			if (temp != '$')
				Analysis_Table[Get_Nindex(Analysis[i].left)][Get_Tindex(temp)] = i;
			if (temp == '$')
			{
				for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
					Analysis_Table[Get_Nindex(Analysis[i].left)][Get_Tindex(*it)] = i;
			}
		}
		else
		{
			for (set<char>::iterator it = First_Set[Get_Nindex(temp)].begin(); it != First_Set[Get_Nindex(temp)].end(); it++)
				Analysis_Table[Get_Nindex(Analysis[i].left)][Get_Tindex(*it)] = i;

			if (First_Set[Get_Nindex(temp)].count('$') != 0)//如果有空集
			{
				for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
					Analysis_Table[Get_Nindex(Analysis[i].left)][Get_Tindex(*it)] = i;
			}
		}
	}

	Print_Table();
	return;
}

void Parser::Print_Table()
{
	  for (int i = 0; i < Terminal.size(); i++)
		  cout << setw(8) << Terminal[i];
	cout <<endl;
	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		cout << Not_Terminal[i] << " ";
		for (int j = 0; j < Terminal.size(); j++)
		{
			if (Analysis_Table[i][j] == -1)
				cout << setw(8) << "error";
			else
				cout << setw(8) << Analysis[Analysis_Table[i][j]].right;
		}
		cout << endl;
	}

	return;
}

void Parser::Analysis_Program(string str)
{
	for (int i = str.length() - 1; i >=0; i--)//std::vector::pop_back删除的是vector中的最后一个元素.所以得倒置
		Left_Analysis_Str.push_back(str[i]);

	S.push_back('#');
	S.push_back(Analysis[0].left);

	while (Left_Analysis_Str.size()>0)
	{
		string temp = "";//用string输出便于控制格式
		//输出分析栈
		for (int i = 0; i < S.size(); i++)
			temp += S[i];
		cout << setw(15)<<temp;
		//输出剩余待分析字符串
		temp = "";
		for (int i = Left_Analysis_Str.size()-1; i>=0; i--)
			temp += Left_Analysis_Str[i];
		cout << setw(15)<<temp;

		char Top_S = S[S.size() - 1];
		char ch = Left_Analysis_Str[Left_Analysis_Str.size() - 1];
		if (!is_Not_Terminal(Top_S))
		{
			if (Top_S == ch)
			{
				cout << endl;
				if (Top_S == '#')
				{
					cout << setw(15)<< "OK!" << endl;
					return;
				}
				else
				{
					S.pop_back();
					Left_Analysis_Str.pop_back();
					continue;
				}
			}
			else
			{
				cout << setw(15)<< "error" << endl;
				return;
			}
		}
		else if (Analysis_Table[Get_Nindex(Top_S)][Get_Tindex(ch)]!=-1)
		{
			int Res = Analysis_Table[Get_Nindex(Top_S)][Get_Tindex(ch)];
			S.pop_back();
			if (Analysis[Res].right != "$")
			{
				for (int i = Analysis[Res].right.size() - 1; i >= 0; i--)
					S.push_back(Analysis[Res].right[i]);
			}
			cout << setw(15) << Analysis[Res].right << endl;
		}
		else
		{
			cout << setw(15)<<"error" << endl;
			return;
		}
	}
	return;
}