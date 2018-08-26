# CompilerPrinciple
**LexAnalysis:**<br/>
Input:<br/>
class Base<br/>
{<br/>
public:<br/>
bool is_Digtal(char);  //字符是否是数字<br/>	
bool is_Characters(char);//字符是否是大小写字母<br/>
bool is_SingleOperatorOrDelimiter(char);/*字符是否是  长度为1的界限符*/<br/>
int SearchKeyWord(char [][20],char []);<br/>
};<br/>
Output:<br/>![image](https://github.com/Chinese-Dd/CompilerPrinciple/blob/master/LexAnalysis_Output.png)<br/>   

--------------------------------------------------------------------------

**LL(1)Parser:**<br/>
Input:<br/>
8<br/>
E->TK<br/>
K->+TK<br/>
K->$<br/>
T->FM<br/>
M->*FM<br/>
M->$<br/>
F->i<br/>
F->(E)<br/>
i+i\*i# <br/>  
Output:<br/>![image](https://github.com/Chinese-Dd/CompilerPrinciple/blob/master/LL(1)_Output.png)<br/>  
