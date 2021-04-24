#include "stack.h"

/**
 * 初始化一个栈
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * 返回栈已使用长度
 * @param S 操作栈
 * @return 返回栈的长度
 */
int StackLength(Stack S)
{
    return S.top + 1;
}

/**
 * 获取栈的一个数组拷贝，顺序为从栈底到栈顶
 * @param S 操作栈
 * @param seq 栈中元素的一个拷贝
 */
void StackToArray(Stack S, DataType *seq)
{
    int i = 0;
    for (; i <= S.top; i++)
    {
        seq[i] = S.data[i];
    }
}

/**
 * 判断栈是否空，为空返回1，否则返回0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    //TODO
    //栈顶标志为-1时，标志栈顶即为栈底，栈为空
    if(S.top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * 向栈插入一个元素
 * @param S 操作栈
 * @param e 操作数
 * @return 成功返回1，否则返回0
 */
int Push(Stack *s, DataType e)
{
    //TODO
    //栈顶标志加1，再将元素插入数组中栈顶标志对应的位置
    s->top++;
    s->data[s->top]=e;
    if(s->top!=-1)
        return 1;
    else
        return 0;
}

/**
 * 从栈中弹出一个元素
 * @param S 操作栈
 * @param e 接受栈弹出的值
 * @return 成功返回1，否则返回0
 */
int Pop(Stack *S, DataType *e)
{
    //TODO
    int i=0;
    //先记录栈顶元素，将其置零后，将栈顶标志减一，即完成Pop操作
    if(*e=S->data[S->top])
        i=1;
    S->data[S->top]=0;
    S->top--;
    if(i)
        return 1;
    else
        return 0;
}

/**
 * 获取栈顶元素，不删除该元素
 * @param S 操作栈
 * @param e 接受栈顶元素
 * @return 成功返回1，否则返回0
 */
int GetTop(Stack S, DataType *e)
{
    //TODO
    //若栈顶即为栈顶，栈中无元素，
    if(S.top==-1)
        return 0;
    else
        //记录栈顶元素
        *e=S.data[S.top];
        return 1;
}

