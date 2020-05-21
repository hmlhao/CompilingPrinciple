#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 6
char key[7][max] = { "main","int","char","if","else","for","while" };
char kArithmeticOperator[5] = { '=','+','-','*','/' };
char delimiter[9] = { '(',')','[',']','{','}',',',':',';'};
char logicalOperator[9] = { '>','<','=','!','&','|' };
int digit = 0;
int CurPos_str = 0;
char str[10] = "";

void State0(char ch);
void State1(char ch);
void State3(char ch);
int IsKey(char ch[]);
bool IsDigit(char ch);
bool IsLetter(char ch);

int IsKey(char ch[])
{
	for (int i = 0; i < 7; i++)
		if (strcmp(key[i], ch) == 0)
		{
			return i + 1;    //返回关键字的序号，作为其种类编码
			break;
		}
	return -1;
}
bool IsDigit(char ch)  //判断字符是否为数字
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
bool IsLetter(char ch)   //判断字符是否为字母
{
	if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
		return true;
	else
		return false;

}

void State0(char ch)
{
	while (ch == ' ')
	{
		ch = getchar();
	}
	if (IsDigit(ch))
	{
		digit = 10 * digit + atoi(&ch);
		ch = getchar();
		State3(ch);
	}
	else if (IsLetter(ch))
	{
		str[CurPos_str++] = ch;
		ch = getchar();
		State1(ch);
	}
	else if (ch == '('|| ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}'||ch==','||ch==':'||ch==';')
	{
		for (int i = 0; i < 9; i++)
			if (delimiter[i] == ch)
			{
				printf("(%d,%c)\n",(26+i),ch);
			}
		ch = getchar();
		State0(ch);
	}
	else if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ',' || ch == ':' || ch == ';')
	{
		for (int i = 0; i < 9; i++)
			if (delimiter[i] == ch)
			{
				printf("(%d,%c)\n", (26 + i), ch);
			}
		ch = getchar();
		State0(ch);
	}
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
	{
		char c = ch;
		ch = getchar();
		if (ch == '+')
		{
			printf("(44,++)\n");
			ch = getchar();
			State0(ch);
		}
		else if (ch == '-')
		{
			printf("(45,--)\n");
			ch = getchar();
			State0(ch);
		}
		
		else
		{
			for (int i = 1; i < 5; i++)
				if (kArithmeticOperator[i] == c)
				{
					printf("(%d,%c)\n", (21 + i), c);
				}
			State0(ch);
		}
	}
	else if (ch == '=')
	{
		ch = getchar();
		if (ch == '=')
		{
			printf("(39,==)\n");
			ch = getchar();
			State0(ch);
		}
		else
		{
			printf("(21,=)\n");
			State0(ch);
		}
	}

	else if (ch == '>' || ch == '<'  || ch == '!')
	{
		char c = ch;
		ch = getchar();
		if (ch == '=')
		{
			for (int i = 0; i < 4; i++)
			{
				if (logicalOperator[i] == c)
					printf("(%d,%c=)\n", (37 + i), c);
			}

			ch = getchar();
			State0(ch);
		}

		else
		{
			for (int i = 0; i < 2; i++)
				if (kArithmeticOperator[i] == c)
				{
					printf("(%d,%c)\n", (35 + i), c);
				}
			State0(ch);
		}
	}
	else if (ch == '&' || ch == '|' )
	{
		ch = getchar();
		if (ch == '&')
		{
			printf("(42,&&)\n");
			ch = getchar();
			State0(ch);
		}
		else if (ch == '|')
		{
			printf("(43,||)\n");
			ch = getchar();
			State0(ch);
		}
		else
		{
			printf("(41,&)\n");
			ch = getchar();
			State0(ch);
		}


	}

}

void State1(char ch)   //分析标识符
{
	while (IsDigit(ch) || IsLetter(ch))
	{
		//strcat(str,&ch);
		str[CurPos_str++] = ch;
		ch = getchar();
	}
	int i = IsKey(str);
	if (i > 0)
		printf("(%d,%s)\n", i, str);
	else
		printf("(10,%s)\n", str);   //标识符分析结束，输出
	for (int j = 0; j < 10; j++)
		str[j] = 0;        //对str重新赋空值，以便存放下一个标识符
	CurPos_str = 0;
	State0(ch);           //进入状态0，重新进行下一轮的字符分析
}


void State3(char ch)     //分析常数
{
	while (IsDigit(ch))
	{
		digit = 10 * digit + atoi(&ch);
		ch = getchar();
	}
	printf("(20,%d)\n", digit);  //整常数分析结束
	digit = 0;
	State0(ch);
}


void main()
{
	printf("请输入源代码：");
	char ch;
	ch = getchar();
	State0(ch);
}
