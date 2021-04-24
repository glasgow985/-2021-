#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    //TODO
    if(Q.stack1.top==-1)
        return 1;
    else
        return 0;
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    //�����������ش���
    if(StackLength(Q->stack1)==MaxSize)
        return 0;
    //���в��������в���
    else
    {
        //��Ԫ�ز���stack1
        if(Push(&Q->stack1,e))
            return 1;
        else
            return 0;
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //TODO
    int m,i;
    //�Ƚ�����Ԫ�����δ�stack1�е�����ѹ��stack2��
    while(!StackEmpty(Q->stack1))
    {
        Pop(&Q->stack1,&m);
        Push(&Q->stack2,m);
    }
    //Popstack2��ջ��Ԫ�أ���Ϊ����ͷԪ��
    i=Pop(&Q->stack2,e);
    //�ٽ�����Ԫ�����δ�stack2�е�����ѹ��stack1�У����Pop����
    while(!StackEmpty(Q->stack2))
    {
        Pop(&Q->stack2,&m);
        Push(&Q->stack1,m);
    }
    if(i)
        return 1;
    else
        return 0;
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    int m,i;
    //�Ƚ�����Ԫ�����δ�stack1�е�����ѹ��stack2��
    while(!StackEmpty(Q.stack1))
    {
        Pop(&Q.stack1,&m);
        Push(&Q.stack2,m);
    }
    //��ȡstack2��ջ��Ԫ�أ���Ϊ����ͷԪ��
    i=GetTop(Q.stack2,e);
    //�ٽ�����Ԫ�����δ�stack2�е�����ѹ��stack1��
    while(!StackEmpty(Q.stack2))
    {
        Pop(&Q.stack2,&m);
        Push(&Q.stack1,m);
    }
    if(i)
        return 1;
    else
        return 0;
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    //TODO
    int i,m;
    //������Ԫ�����δ�stack1�е�����ѹ��stack2��
    while(!StackEmpty(Q.stack1))
    {
        Pop(&Q.stack1,&m);
        Push(&Q.stack2,m);
    }
    //��ʱֱ�ӽ�stack2��Ԫ�����ε�������Ϊ���е��Ƚ��ȳ�˳��
    for(i=0;!StackEmpty(Q.stack2);i++)
    {
        Pop(&Q.stack2,&seq[i]);
    }
}
