#include"Base.h"
void Base::init()
{
	cout << "输入的产生式的个数：" << endl;
	freopen("in.txt", "r", stdin);
	cin >> Num;
	string s;
	//定义一个临时的终结符与非终结符set集,用于存储非重复元素
	set<char> Temp_Terminal;
	set<char> Temp_Not_Terminal;
	for (int i = 0; i < Num; i++)
	{
		cin >> s;
		int len = s.length();
		for (int j = 0; j < len; j++)
		{
			if (s[j] == '-' || s[j] == '>' || s[j] == ' ')//非法符号直接跳过
				continue;
			if (j == 0)  //初始化产生式
				Analysis[i].left = s[0];
			else
				Analysis[i].right += s[j];

			if (is_Not_Terminal(s[j]))  //初始化终结符集与非终结符
				Temp_Not_Terminal.insert(s[j]);
			else
				Temp_Terminal.insert(s[j]);
		}
	}


	//再将set集元素存储与vector集中
	for (set<char>::iterator it = Temp_Terminal.begin(); it != Temp_Terminal.end(); it++)//分析表中得用到非空终结符集,所以将空集排出
	{
		if (*it != '$')
		Terminal.push_back(*it);
	}

	for (set<char>::iterator it = Temp_Not_Terminal.begin(); it != Temp_Not_Terminal.end(); it++)
		Not_Terminal.push_back(*it);

	Terminal.push_back('#');
	cout << "初始化产生式后:" << endl;
	cout << "左部" << setw(10) << "右部" << endl;
	for (int i = 0; i < Num; i++)
		cout << Analysis[i].left << setw(12) << Analysis[i].right << endl;

	cout << "终结符集:" << endl;
	for (int i = 0; i < Terminal.size(); i++)
		cout << Terminal[i] << " ";
	cout << endl;

	cout << "非终结符集:" << endl;
	for (int i = 0; i < Not_Terminal.size(); i++)
		cout << Not_Terminal[i] << " ";
	cout << endl;



	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		if (First_Set[i].empty())
			Get_First(Not_Terminal[i]);
	}

	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		if (i == 0)
		{
			Follow_Set[0].insert('#');
			continue;
		}
		Get_Follow(Not_Terminal[i]);
	}
	return;
}

bool Base::is_Not_Terminal(char c)
{
	if (c >= 'A'&&c <= 'Z')
		return 1;
	return 0;
}

int Base::Get_Nindex(char Target)
{
	for (int i = 0; i < Not_Terminal.size(); i++)
	if (Not_Terminal[i] == Target)
		return i;
}

int Base::Get_Tindex(char Target)
{
	for (int i = 0; i < Terminal.size(); i++)
	if (Terminal[i] == Target)
		return i;
}

void Base::Get_First(char Target)
{
	for (int i = 0; i < Num; i++)
	{
		int temp = 0;//用于记录每条产生式右部$的个数
		if (Analysis[i].left == Target)
		{
			for (int j = 0; j < Analysis[i].right.length(); j++)
			{
				if (!is_Not_Terminal(Analysis[i].right[j])) //如果是终结符
				{
					First_Set[Get_Nindex(Target)].insert(Analysis[i].right[j]);
					break;
				}
				//如果是非终结符
				int flag = -1;
				Get_First(Analysis[i].right[j]);
				for (set<char>::iterator it = First_Set[Get_Nindex(Analysis[i].right[j])].begin(); it != First_Set[Get_Nindex(Analysis[i].right[j])].end(); it++)
				{
					if (*it == '$')
						flag = 1;
					else
						First_Set[Get_Nindex(Target)].insert(*it);
				}
				if (flag == 1)  //如果出现空集
					temp++;
				else
					break;
				if (temp == Analysis[i].right.length()) //若已经到达产生式的最右部的非终结符,则将$加入左部的first集
					First_Set[Get_Nindex(Target)].insert('$');

			}
		}
	}

	return;
}

void Base::Get_Follow(char Target)
{
	for (int i = 0; i < Num; i++)
	{
		if (Target == Analysis[i].left)   //target与左部相同时
			continue;
		int pos = -1;   //产生式右部的pos
		int target_pos = -1; //非终结符pos
		int len = Analysis[i].right.length();
		for (int j = 0; j < len; j++)
		{
			if (Analysis[i].right[j] == Target)
			{
				target_pos = j;
				pos = j;
				break;
			}
		}

		if (target_pos == -1)//在右部没找到target时
			continue;

		//cout << "target为" << target << "目前为第" << i << "条产生式" << endl;

		if (target_pos == len - 1) //课本P60,情况3前面一种
		{
			//	cout << "情况3前面一种" << endl;
			Get_Follow(Analysis[i].left);
			for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
				Follow_Set[Get_Nindex(Target)].insert(*it);
		}

		int isHasEmpty = 1;//检测是否含有空集,有的话就继续扫描下一个,否则中断
		while (pos + 1 < len&&isHasEmpty)
		{
			isHasEmpty = 0;
			pos++;
			char nxt = Analysis[i].right[pos];
			if (!is_Not_Terminal(nxt))  //如果是终结符,直接加入,//课本P60,情况1
			{
				Follow_Set[Get_Nindex(Target)].insert(nxt);
				break;
			}
			else
			{
				for (set<char>::iterator it = First_Set[Get_Nindex(nxt)].begin(); it != First_Set[Get_Nindex(nxt)].end(); it++)//课本P60,情况2
				{
					//			cout << "情况2前面一种" << endl;
					if (*it == '$')
						isHasEmpty = 1;
					else
						Follow_Set[Get_Nindex(Target)].insert(*it);
				}

				if (pos - target_pos == 1 && isHasEmpty&&pos == len - 1) //情况3后面一种	
				{
					//			cout << "情况3后面一种" << endl;
					Get_Follow(Analysis[i].left);
					for (set<char>::iterator it = Follow_Set[Get_Nindex(Analysis[i].left)].begin(); it != Follow_Set[Get_Nindex(Analysis[i].left)].end(); it++)
						Follow_Set[Get_Nindex(Target)].insert(*it);
				}
			}
		}

	}
	return;
}

void Base::Print_FirstAndFollow()
{
	cout << "First集合:" << endl;
	for (int i = 0; i < Not_Terminal.size(); i++)
	{
		cout << Not_Terminal[i] << ": ";
		for (set<char>::iterator it = First_Set[i].begin(); it != First_Set[i].end(); it++)
			cout << *it << " ";
		cout << endl;
	}

	cout << "FOLLOW集合" << endl;
	for (int i = 0; i<Not_Terminal.size(); i++)
	{
		cout << Not_Terminal[i] << ": ";
		for (set<char>::iterator it = Follow_Set[i].begin(); it != Follow_Set[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}

	return;
}
