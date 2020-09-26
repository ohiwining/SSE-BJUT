#include<iostream>
using namespace std;
typedef char ElemType;
typedef struct Node//定义节点
{
    ElemType data;
    Node *next;//定义指针
}SqStack;//定义栈节点
SqStack *InitStack(SqStack *a)//初始化函数
{
    a=new SqStack;//分配内存
    a->data='E';//这个节点用于判断是否为空所以设置数据为一个特殊字符
    return a;
}
SqStack *Push(SqStack *a,ElemType input)//输入元素函数
{
    auto *temp=new SqStack;
    temp->data=input;//保存当前字符
    temp->next=a;//改变栈顶指针
    a=temp;
    return a;
}
SqStack *Pop(SqStack *a,char &e)//输出栈顶元素函数
{
    SqStack *temp=a;
    a=a->next;
    e=temp->data;//将输出的元素存入e中
    delete temp;//释放内存
    return a;
}
void GetTop(SqStack *a, char &e)//获取栈顶元素函数
{
    e=a->data;//直接获取并保存到e中
}
bool StackEmpty(SqStack *a)//判断栈是否为空
{
    return a->data == 'E';
}
void Trans(char exp[],char postexp[])//转换函数
{
    char e;
    SqStack *a;		       //定义运算符栈指针
    a=InitStack(a);		   //初始化运算符栈
    int i=0;			   //i作为postexp的下标
    while (*exp!='\0')     //exp表达式未扫描完时循环
    {
        switch(*exp)
        {
            case '(':	           //判定为左括号
                a=Push(a,'(');//左括号进栈
                exp++;		    //继续扫描其他字符
                break;
            case ')':		                  //判定为右括号
                a=Pop(a,e);	    //出栈元素e
                while (e!='(')	    //不为'('时循环
                {
                    postexp[i++]=e;	    //将e存放到postexp中
                    a=Pop(a,e);	    //继续出栈元素e
                }
                exp++;		     //继续扫描其他字符
                break;
            case '+':			//判定为加或减号
            case '-':
                while (!StackEmpty(a))	//栈不空循环
                {
                    GetTop(a,e);		//取栈顶元素e
                    if (e!='(')			//e不是'('
                    {
                        postexp[i++]=e;	//将e存放到postexp中
                        a=Pop(a,e);		//出栈元素e
                    }
                    else			//e是'(时退出循环
                        break;
                }
                a=Push(a,*exp);		//将'+'或'-'进栈
                exp++;				//继续扫描其他字符
                break;
            case '*':				//判定为'*'或'/'号
            case '/':
                while (!StackEmpty(a))	//栈不空循环
                {
                    GetTop(a,e);		//取栈顶元素e
                    if (e=='*' || e=='/')
                    {
                        postexp[i++]=e;	//将e存放到postexp中
                        a=Pop(a,e);	//出栈元素e
                    }
                    else			//e为非'*'或'/'运算符时退出循环
                        break;
                }
                a=Push(a,*exp);		//将'*'或'/'进栈
                exp++;			//继续扫描其他字符
                break;
            default:			//处理数字字符
                while (*exp>='0' && *exp<='9')      //判定为数字字符
                {
                    postexp[i++]=*exp;
                    exp++;
                }
                postexp[i++]='#';	//用#标识一个数值串结束
        }
    }
    while (!StackEmpty(a))	//此时exp扫描完毕,栈不空时循环
    {
        a=Pop(a,e);		//出栈元素e
        postexp[i++]=e;		//将e存放到postexp中
    }
    postexp[i]='\0';		//给postexp表达式添加结束标识
}
int main()
{
    char before[30],after[30];//before为要输入的中缀表达式。after为即将要转换的后缀表达式
    cout<<"Please input expression:"<<endl;
    cin>>before;
    Trans(before,after);
    cout<<"Translate completed."<<endl<<"Result: "<<after<<endl;
}