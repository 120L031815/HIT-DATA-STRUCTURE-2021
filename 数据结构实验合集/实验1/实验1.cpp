#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <queue>
using namespace std;

struct node        //�������Ķ������� 
{
    node *lchild;
    char data;
    node *rchild;
};
typedef node *BTREE;
BTREE CreatBT()   //����һ���������Ĵ��� 
{
    BTREE T;
    char ch;
    scanf(" %c",&ch);
    if(ch=='#')   //������#����ý��Ϊ�� 
        T = NULL;
    else
    {
        T = (BTREE)malloc(sizeof(node));
        T->data = ch;
        T->lchild = CreatBT();   //���õݹ飬ʹ������˳����д��� 
        T->rchild = CreatBT();
    }
    return T;
}
void PreOrder(BTREE BT)  //��������ĵݹ�ʵ�� 
{
    if(BT!=NULL)
    {
        printf("%c ",BT->data);  //�ȷ��ʸ��ڵ� 
        PreOrder(BT->lchild);    //�ٷ��������� 
        PreOrder(BT->rchild);    //�ٷ��������� 
    }
}
void InOrder(BTREE BT)   //��������ĵݹ�ʵ�� 
{
    if(BT!=NULL)
    {
        InOrder(BT->lchild);    //�ȷ��������� 
        printf("%c ",BT->data); //�ٷ��ʸ��ڵ� 
        InOrder(BT->rchild);    //�ٷ��������� 
    }
}
void PostOrder(BTREE BT)
{
    if(BT!=NULL)
    {
        PostOrder(BT->lchild);   //�ȷ��������� 
        PostOrder(BT->rchild);   //�ٷ��������� 
        printf("%c ",BT->data);  //�ٷ��ʸ��ڵ� 
    }
}
void PreOrderfei(BTREE T)   //��������ǵݹ�ʵ�� 
{
    stack <BTREE> S;
    BTREE p = T;
    while(p!=NULL||!S.empty())
    {                          //����������� ���ڵ㣬�������������� ��˳���Ž���ջ�����
        while(p!=NULL)    
        {
            printf("%c ",p->data);
            S.push(p);
            p = p->lchild;
        }

        if(!S.empty())  
        {
            p = S.top();
            S.pop();
            p = p->rchild;
        }
    }

}
void InOrderfei(BTREE T)  //��������ķǵݹ�ʵ�� 
{
    stack <BTREE> S;
    BTREE root = T;
    while(root!=NULL||!S.empty())
    {                            //����������� �����������ڵ㣬������ ��˳���Ž���ջ�����
        while(root!=NULL)   
        {
            S.push(root);
            root = root->lchild;
        }
        if(!S.empty())   
        {
            root = S.top();
            S.pop();
            printf("%c ",root->data);
            root = root->rchild;
        }
    }
}
void PostOrderfei(BTREE T)  //��������ķǵݹ�ʵ�� 
{
    BTREE p,pr;
    stack <BTREE> S;
    p = T;
    while(p!=NULL||!S.empty())
    {                           //���պ������ ��������������������� ��˳���Ž���ջ�����
        while(p!=NULL)  
        {
            S.push(p);
            pr = p->rchild;
            p = p->lchild;
            if(p==NULL)
                p = pr;
        }
        p = S.top();  //pָ��ջ�� 
        S.pop();      //��ջ���� 
        printf("%c ",p->data);  //���������� 
        if(!S.empty()&&S.top()->lchild==p)  //��ջ�ǿ���ջ�����ӽ��Ϊp 
            p = S.top()->rchild;    //pָ�����ֵܽ�� 
        else
            p = NULL;
    }
}
void LevelOrder(BTREE root)  //������� 
{
    queue <BTREE> Q;  
    if(root==NULL)
        return;
    Q.push(root);
    while(!Q.empty())
    {
        BTREE q = Q.front();     //pָ����� 
        Q.pop();
        printf("%c ",q->data);   //�����������ֵ 
        if(q->lchild!=NULL)
            Q.push(q->lchild);   //�������������� 
        if(q->rchild!=NULL)
            Q.push(q->rchild);   //�������������� 
    }

}
bool IsComleteTree(BTREE root)  //�ж��Ƿ�Ϊ��ȫ������ 
{
    if(root == NULL)
    {
        return false;
    }
    queue<BTREE>q;
    q.push(root);
    BTREE p = q.front();
    while(p != NULL)   //���ղ�������Ĵ������ֱ�����ʵ��ս�� 
    {
        q.pop();
        q.push(p->lchild);
        q.push(p->rchild);
        p = q.front();
    }
    q.pop();  //���׵Ŀս����� 
    while(!q.empty())   //����ʱ����ȫΪ�ս��˵��Ϊ��ȫ����������֮���� 
    {
        if(q.front()!=NULL)
            return false;
        q.pop();
    }
    return true;
}
int main()
{
    BTREE T;
    T = CreatBT();
    printf("����ݹ飺");
    PreOrder(T);
    printf("\n");
    printf("����ݹ飺");
    InOrder(T);
    printf("\n");
    printf("����ݹ飺");
    PostOrder(T);
    printf("\n");
    printf("����ǵݹ飺");
    PreOrderfei(T);
    printf("\n");
    printf("����ǵݹ飺");
    InOrderfei(T);
    printf("\n");
    printf("����ǵݹ飺");
    PostOrderfei(T);
    printf("\n");
    printf("���������");
    LevelOrder(T);
    printf("\n");
    printf("�Ƿ�Ϊ��ȫ��������");
    if(IsComleteTree(T)==false)
        printf("FALSE\n");
    else
        printf("TRUE\n");
    return 0;
}
