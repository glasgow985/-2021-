#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&Q->stack1);
    InitStack(&Q->stack2);
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
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
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //TODO
    //队列满，返回错误
    if(StackLength(Q->stack1)==MaxSize)
        return 0;
    //队列不满，进行插入
    else
    {
        //将元素插入stack1
        if(Push(&Q->stack1,e))
            return 1;
        else
            return 0;
    }
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    //TODO
    int m,i;
    //先将所有元素依次从stack1中弹出，压入stack2中
    while(!StackEmpty(Q->stack1))
    {
        Pop(&Q->stack1,&m);
        Push(&Q->stack2,m);
    }
    //Popstack2的栈顶元素，即为队列头元素
    i=Pop(&Q->stack2,e);
    //再将所有元素依次从stack2中弹出，压入stack1中，完成Pop操作
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
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    //TODO
    int m,i;
    //先将所有元素依次从stack1中弹出，压入stack2中
    while(!StackEmpty(Q.stack1))
    {
        Pop(&Q.stack1,&m);
        Push(&Q.stack2,m);
    }
    //获取stack2的栈顶元素，即为队列头元素
    i=GetTop(Q.stack2,e);
    //再将所有元素依次从stack2中弹出，压入stack1中
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
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
    */
    //TODO
    int i,m;
    //将所有元素依次从stack1中弹出，压入stack2中
    while(!StackEmpty(Q.stack1))
    {
        Pop(&Q.stack1,&m);
        Push(&Q.stack2,m);
    }
    //此时直接将stack2中元素依次弹出，即为队列的先进先出顺序
    for(i=0;!StackEmpty(Q.stack2);i++)
    {
        Pop(&Q.stack2,&seq[i]);
    }
}
