#include "stack.h"

/**
 * ��ʼ��һ��ջ
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * ����ջ��ʹ�ó���
 * @param S ����ջ
 * @return ����ջ�ĳ���
 */
int StackLength(Stack S)
{
    return S.top + 1;
}

/**
 * ��ȡջ��һ�����鿽����˳��Ϊ��ջ�׵�ջ��
 * @param S ����ջ
 * @param seq ջ��Ԫ�ص�һ������
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
 * �ж�ջ�Ƿ�գ�Ϊ�շ���1�����򷵻�0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    //TODO
    //ջ����־Ϊ-1ʱ����־ջ����Ϊջ�ף�ջΪ��
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
 * ��ջ����һ��Ԫ��
 * @param S ����ջ
 * @param e ������
 * @return �ɹ�����1�����򷵻�0
 */
int Push(Stack *s, DataType e)
{
    //TODO
    //ջ����־��1���ٽ�Ԫ�ز���������ջ����־��Ӧ��λ��
    s->top++;
    s->data[s->top]=e;
    if(s->top!=-1)
        return 1;
    else
        return 0;
}

/**
 * ��ջ�е���һ��Ԫ��
 * @param S ����ջ
 * @param e ����ջ������ֵ
 * @return �ɹ�����1�����򷵻�0
 */
int Pop(Stack *S, DataType *e)
{
    //TODO
    int i=0;
    //�ȼ�¼ջ��Ԫ�أ���������󣬽�ջ����־��һ�������Pop����
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
 * ��ȡջ��Ԫ�أ���ɾ����Ԫ��
 * @param S ����ջ
 * @param e ����ջ��Ԫ��
 * @return �ɹ�����1�����򷵻�0
 */
int GetTop(Stack S, DataType *e)
{
    //TODO
    //��ջ����Ϊջ����ջ����Ԫ�أ�
    if(S.top==-1)
        return 0;
    else
        //��¼ջ��Ԫ��
        *e=S.data[S.top];
        return 1;
}

