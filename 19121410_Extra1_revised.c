#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MaxSize 30

typedef int DataType;
typedef   struct
{
    DataType  data;
    int  prior, next;
}StLNode;

typedef  struct
{
    StLNode  StList[MaxSize];
    int head;
}StLink;

int IntialList(StLink *L);                      //初始化双向循环静态链表
//int CreatListH(StLink *L, int len);             //创建一个带头节点的双向循环静态链表, 长度为len（不包括头节点），头节点记录长度
int LengthList(StLink *L);                      //求静态链表长度
int InsertList(StLink *L, int i, DataType x);   //在第i个节点前一个位置插入
void PrintList(StLink *L);                      //打印静态链表
int GetList(StLink *L, int i, DataType *x);     //取得第i个位置的元素
int DeleteList(StLink *L, int i, DataType *x);  //删除第i个位置的元素
//void InverseList(StLink *L);                    //就地逆置静态链表
void Destroy(StLink *L);                        //撤销静态链表

int main(void)
{
    StLink MyStList;
    DataType x2, x3;
    /* 测试数据
    DataType x = 99;
    int len = 5;            //长度
    int i = 4;              //第i个节点前一个位置插入
    int j = 6;              //取得第j个位置的元素
    int k = 2;              //删除第k个位置的元素
    */
    int len, length;
    int i, j, k, ii;
    DataType x;

    IntialList(&MyStList);
    printf("Please input the length of the list:\n");
    scanf("%d", &len);

    //新建一个静态链表
    for ( ii = 0; ii < len; ii++)
    {
        printf("Please input the data of current node:\n");
        scanf("%d", &x);
        if (ii == 0)
        {
            MyStList.StList[ii+1].data = x;
            MyStList.StList[ii+1].prior = MyStList.head;
            MyStList.StList[ii+1].next = MyStList.head;
            MyStList.StList[MyStList.head].next = ii+1;
            MyStList.StList[MyStList.head].prior = ii+1;
            MyStList.StList[MyStList.head].data ++;
        }
        else
            InsertList(&MyStList, 0, x);
    }
    PrintList(&MyStList);

    length = LengthList(&MyStList);
    printf("\nThe length of the list is %d,", length);

    printf("\nPlease input the position to insert:\n");
    scanf("%d", &i);
    printf("Please input the data to insert:\n");
    scanf("%d", &x);
    InsertList(&MyStList, i, x);
    PrintList(&MyStList);
    length = LengthList(&MyStList);
    printf("\nThe length of the list is %d,", length);

    printf("\nPlease input the position of the data you want to get:\n");
    scanf("%d", &j);
    GetList(&MyStList, j, &x2);
    printf("\nThe data of NO.%d Node is %d.\n", j, x2);

    printf("Please input the position of the data you want to delete:\n");
    scanf("%d", &k);
    DeleteList(&MyStList, k, &x3);
    PrintList(&MyStList);

    Destroy(&MyStList);
    PrintList(&MyStList);
    /*length = LengthList(&MyStList);
    printf("\nThe length of the list is %d,", length);*/

    /*
    printf("\nThe Inversion is:\n");
    InverseList(&MyStList);
    PrintList(&MyStList);
    */

    return 0;
}

int IntialList(StLink *L)
{
    L->head = 0;
    L->StList->next = L->head;
    L->StList->prior = L->head;
    L->StList->data = 0;                    //头节点储存除头节点外的结点个数，初始化为0
    return 1;
}

/*
int CreatListH(StLink *L, int len)
{
    int i;
    DataType x;
    if (len > MaxSize)
    {
        printf("\nThe length is too long!\n");
        return 0;
    }
    for ( i = 0; i < len; i++)
    {
        printf("Please input the data of current node:\n");
        scanf("%d", &x);
        L->StList[i+1].data = x;
        L->StList[i+1].prior = i;
        L->StList[i].next = i + 1;
        L->StList->data ++;
    }
    L->StList[i].next = L->head;
    L->StList[L->head].prior = i;
    return 1;
}
*/

int LengthList(StLink *L)
{
    if(L->head == -1)
        return -1;
    int cur;
    int length = 0;
    cur = L->head;
    while (L->StList[cur].next != 0)
    {
        length ++;
        cur = L->StList[cur].next;
    }
    return length;
}

int InsertList(StLink *L, int i, DataType x)
{
    //按照双向循环链表的方式
    int j;
    int p, new, temp;
    p = L->StList[L->head].next;
    j = 0;
    while (L->StList[p].next != L->head && j<i)
    {
        p = L->StList[p].next;
        j ++;
    }
    if(j != i)
    {
        printf("Wrong position!\n");
        return 0;
    }

    new = L->StList[L->head].data + 1;      
    L->StList[new].data = x;
    L->StList[new].prior = L->StList[p].prior;
    temp = L->StList[p].prior;
    L->StList[temp].next = new;
    L->StList[new].next = p;
    L->StList[p].prior = new;

    L->StList[L->head].data ++;

    return 1;

    /*
    int new;
    int len;
    len = LengthList(L);
    if (i > len)
    {
        printf("The position to insert is wrong!");
        return 0;
    }
    new = L->StList[L->head].data + 1;      //分配一个新的节点
    L->StList[new].data = x;

    L->StList[i].prior = new;               //断开原有节点
    L->StList[i-1].next = new;

    L->StList[new].prior = i-1;             //插入新节点
    L->StList[new].next = i;

    L->StList[L->head].data ++;             //更新节点个数

    return 1;
    */
}

void PrintList(StLink *L)
{
    int i;
    int cur, len;
    len = LengthList(L);
    if (len == 0 )
    {
        printf("\nThe list is empty!\n");
    }
    else if (L->head == -1)
    {
        printf("\nThe list has been destroyed!\n");
    }
    
    else
    {
        cur = L->StList[L->head].next;
        printf("\n");
        for ( i = 0; i < len; i++)
        {
            printf("%4d", L->StList[cur].data);
            cur = L->StList[cur].next;
        }
    }
}

int GetList(StLink *L, int i, DataType *x)
{
    //按照双向循环链表的方式
    int j;
    int p;
    if (L->StList[L->head].next == L->head)
    {
        printf("\nThe list is empty, no element to get!\n");
        return 0;
    }
    p = L->StList[L->head].next;
    j = 0;
    while (L->StList[p].next != L->head && j<i)
    {
        p = L->StList[p].next;
        j ++;
    }
    if (j != i)
    {
        printf("Wrong position!\n");
        return 0;
    }
    *x = L->StList[p].data;
    return 1;
    
    /*
    int cur, len;
    int j;
    len = LengthList(L);
    if (i > len || i == 0)
    {
        printf("Wrong position!\n");
        return 0;
    }

    cur = L->head;
    for( j = 0; j < i; j++)
    {
        cur = L->StList[cur].next;
    }
    *x = L->StList[cur].data;
    return 1;
    */
}

int DeleteList(StLink *L, int i, DataType *x)
{
    //按照双向循环链表的方式
    int j;
    int p, temp1, temp2;
    if (L->StList[L->head].next == L->head)
    {
        printf("\nThe list is empty, no element to delete!\n");
        return 0;
    }
    p = L->StList[L->head].next;
    j = 0;
    while (L->StList[p].next != L->head && j<i)
    {
        p = L->StList[p].next;
        j ++;
    }
    if (j != i)
    {
        printf("Wrong position!\n");
        return 0;
    }
    
    temp1 = L->StList[p].prior;
    L->StList[temp1].next = L->StList[p].next;
    temp2 = L->StList[p].next;
    L->StList[temp2].prior = L->StList[p].prior;
    *x = L->StList[p].data;
    L->StList[p].data = -1; //删除后用-1表示已被删除

    L->StList[L->head].data --;

    return 1;
    /*
    int cur, cur_p, cur_n, len;
    int j;
    len = LengthList(L);
    if (i > len || i == 0)
    {
        printf("Wrong position!\n");
        return 0;
    }
    cur = L->head;
    for(j = 0; j<i; j++ )
    {
        cur = L->StList[cur].next;
    }
    *x = L->StList[cur].data;

    cur_p = L->StList[cur].prior;
    cur_n = L->StList[cur].next;

    L->StList[cur_p].next = cur_n;      //断开相应节点
    L->StList[cur_n].prior = cur_p;
    L->StList[cur].next = -1;           //第i个节点断开后令其前驱和后继都为-1;
    L->StList[cur].prior = -1;

    L->StList[L->head].data --;         //更新节点个数

    return 1;
    */
}

/*
void InverseList(StLink *L)
{   
    int i;
    int len;
    int cur, temp;
    cur = L->head;
    len = LengthList(L);

    for ( i = 0; i < len+1; i++)
    {   
        temp = L->StList[cur].prior;
        L->StList[cur].prior = L->StList[cur].next;
        L->StList[cur].next = temp;
        cur = L->StList[cur].prior;     //将游标移向原表的下一个节点
    }
}
*/

void Destroy(StLink *L)
{
    int x;
    int i, len;
    len = LengthList(L);
    for ( i = 0; i < len; i++)
    {
        DeleteList(L,0, &x);
    }
    L->head = -1;
}