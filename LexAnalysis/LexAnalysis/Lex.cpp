#include "Lex.h"
#include<cstring>

Lex::Lex()
{
	fin = fopen("Test_In.txt", "r"); //fopen成功打开则返回一个FILE*指针,否则返回NULL
	fout = fopen("Test_Out.txt", "w");
}

Lex::~Lex()
{
	fclose(fin);
	fclose(fout);
}

void Lex::init()
{
	if (fin == NULL)
	{
		printf("打开Test_In文件失败\n");
		exit(0);
	}

	BufferCode[pos] = fgetc(fin);
	while (BufferCode[pos] != EOF)
	{
		pos++;
		BufferCode[pos] = fgetc(fin);
	}
	BufferCode[pos] = '\0';
}

void Lex::filter()
{
	char TempCode[10000];
	int count = 0;

	for (int i = 0; i <= pos; i++)
	{
		if (BufferCode[i] == '/'&&BufferCode[i+ 1] == '/')
		{
			while (BufferCode[i] != '\n')
				i++;
		}

		if (BufferCode[i] == '/'&&BufferCode[i + 1] == '*')
		{
			i += 2;
			while (BufferCode[i] != '*' || BufferCode[i + 1] != '/')
			{
				i++;
				if (BufferCode[i] ==EOF)
				{
					printf("过滤失败!注释符错误!\n");
					exit(0);
				}
			}
			i += 2;
		}

			if (BufferCode[i] != '\n'&&BufferCode[i] != '\r'&&BufferCode[i] != '\t'&&BufferCode[i] != '\v')
				TempCode[count++] = BufferCode[i];		
		}

	TempCode[count] = '\0';
	strcpy(BufferCode, TempCode);
	}

void Lex::Scanner(int &state, int &pos, char token[])//参数state, lex.pos为引用类型
{
	char temp = BufferCode[pos];
	for (int i = 0; i <MaxLen; i++) //每次扫描时清空 存储数组token
		token[i]= '\0';
	int count = 0;

	while (temp == ' ')   //重点:空格需要处理,扫描到空格时直接跳过,直到不是空格停下
	{
		pos++;
		temp = BufferCode[pos];
	}

	if (is_Digtal(temp))//开头为数字
	{
		while (is_Digtal(BufferCode[pos]))
		{
			token[count++] = BufferCode[pos];
			pos++;
		}
		token[count] = '\0';
		state =99;
		return;
	}
	else if (is_Characters(temp))//开头为字母或者下划线
	{
		while (is_Digtal(BufferCode[pos]) || is_Characters((BufferCode[pos])))
		{
			token[count++] = BufferCode[pos];
	//	printf("%c   %c    pos=%d   count=%d\n", token[count], BufferCode[pos], pos,count);
			pos++;	
		}	

		token[count] = '\0';	  //结尾处补上个'\0'
		state = SearchKeyWord(KeyWord, token);
		if (state == -1)  //找不到对应的对应保留字,说明 token为标识符
		{
			state = 100;
		}
		return;
	}
	else if (is_SingleOperatorOrDelimiter(temp))//开头为是否是长度为1的界限符
	{
		token[0] =temp;
		token[1] = '\0';

		for (int i = 0; i < 37; i++)
		{
			if (strcmp(token, OperatorOrDelimiter[i]) == 0)
			{
				state = i + 35;
				break;
			}
		}
		pos++;
		return;
	}
	else if (temp == '<')  //  如果为'<' 开头,有可能为 <,<=,<<
	{
		token[0] = '<';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 41;
			return;
		}
		else if (BufferCode[pos] == '<')
		{
			token[1] = '<';
			token[2] = '\0';
			pos++;
			state = 61;
			return;
		}
		token[1] = '\0';
		state = 40;
		return;
	}
	else if (temp == '>')//  如果为'<' 开头,有可能为 >,>=,>>
	{
		token[0] = '>';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 43;
			return;
		}
		else if (BufferCode[pos] == '>')
		{
			token[1] = '>';
			token[2] = '\0';
			pos++;
			state = 62;
			return;
		}
		token[1] = '\0';
		state = 42;
		return;
	}
	else if (BufferCode[pos] == '!')//  如果为'!' 开头,有可能为!,!=
	{
		token[0] = '!';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 46;
			return;
		}
		token[1] = '\0';
		state = 71;
		return;
	}
	else if (BufferCode[pos] == '=')//  如果为'=' 开头,有可能为=,==
	{
		token[0] = '=';
		pos++;
		if (BufferCode[pos] == '=')
		{
			token[1] = '=';
			token[2] = '\0';
			pos++;
			state = 45;
			return;
		}
		token[1] = '\0';
		state = 44;
		return;
	}
	else if (BufferCode[pos] == '|')//  如果为'\' 开头,有可能为|,||
	{
		token[0] = '|';
		pos++;
		if (BufferCode[pos] == '|')
		{
			token[1] = '|';
			token[2] = '\0';
			pos++;
			state = 58;
			return;
		}
		token[1] = '\0';
		state = 57;
		return;

	}
	else if (BufferCode[pos] == '&')//  如果为'&' 开头,有可能为&,&&
	{
		token[0] = '&';
		pos++;
		if (BufferCode[pos] == '&')
		{
			token[1] = '&';
			token[2] = '\0';
			pos++;
			state = 56;
			return;
		}
		token[1] = '\0';
		state = 55;
		return;
	}
	else if (BufferCode[pos] =='\0')
	{
		state = 0;
		 return;
	}	
	else
	{
		printf("%d无法识别的字符,程序即将退出!\n", temp);
		exit(0);
	}

	return;
}

