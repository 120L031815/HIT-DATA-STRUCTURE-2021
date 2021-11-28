#include <iostream>
#include <cstdio>
#include<stack>
#include<queue>
#include<fstream>
using namespace std;
#define Maxnum 100     //������󶥵���Ϊ100 
int visited[Maxnum];   //���ڱ���Ƿ���ʹ� 

void visitedto0()              //��Ƿ�����պ��� 
{
	int i=Maxnum;
	for(i=0;i<Maxnum;i++)
	{
		visited[i]=0;
	}
}


//�ڽӱ�Ľ���
typedef struct node    //�߱��㽨�� 
{
	int adjvex;       //����±꣨��ţ� 
	struct node* next;
}Edgenode;            

typedef struct {      //������㽨�� 
	char element;
	Edgenode *firstedge;
}VertexNode;

typedef struct{                    //�ڽӱ��� 
	VertexNode vexlist[Maxnum];   //����� 
	int n,e;                     //ͼ�Ķ���������� 
}AdjGraph;

void creatAdj(AdjGraph *p)  //���벢��ʾ�ڽӱ� 
{
	int i,j,k;
    ifstream in("file.txt");
    in>>p->n>>p->e;
	for (k=0; k<p->n; k++)      //�ڽӱ�ĳ�ʼ��
    {
        in>>p->vexlist[k].element;
        p->vexlist[k].firstedge=NULL; 
    }
    for(k=0; k<p->e; k++)
    {
        in>>j>>i;
        Edgenode* q=new Edgenode;
        q->adjvex=i;
        q->next=p->vexlist[j].firstedge;
        p->vexlist[j].firstedge=q;//ͷ�巨 
       /* q=new Edgenode;//��������ͼ�����Ի�Ҫ����������
        q->adjvex=j;
        q->next=p->vexlist[i].firstedge;
        p->vexlist[i].firstedge=q;*/
    }
    in.close();
    cout<<"�ڽӱ���������"<<endl; 
    for(i=0;i<p->n;i++)    //��ӡ�����õ��ڽӱ� 
    {
        cout<<i<<" "<<p->vexlist[i].element;
        Edgenode *m=p->vexlist[i].firstedge;
        while(m!=NULL)
        {
            cout<<"->"<<m->adjvex;
            m=m->next;
        }
        cout<<"->NULL"<<endl;
    }
}

//�ڽӾ���Ľ��� 
typedef struct {
	int mat[Maxnum][Maxnum];    //�ڽӾ���һ�߱� 
	char element[Maxnum];       //����� 
	int n,e;                    //����������� 
}MTGraph;

void creatMTG(MTGraph *p)     //���벢���뽨������ 
{
	int i,j,x,y;
    ifstream in("file.txt");
    in>>p->n>>p->e;
	for(i=0; i<p->n; i++)        //���붥��� 
    {
	  in>>p->element[i];
    }
    for(i=0; i<p->n; i++)       //���ڽӾ����ʼΪ0 
    {
	   for(j=0; j<p->n; j++)
            p->mat[i][j]=0;
    }
    for(i=0; i<p->e; i++)    //��д�ڽӾ��� 
    {
        in>>x>>y;
        p->mat[x][y]=1;
    }
    cout<<"�����ڽӾ�������:"<<endl;   //��ӡ�����õ��ڽӾ��� 
    for(i=0; i<p->n; i++)
    {
    	cout<<p->element[i]<<" ";
      for(j=0; j<p->n; j++)
        cout << p->mat[i][j] << " ";
        cout << endl;
    }
}

//�ڽӾ���ת�ڽӱ�
void MTGtoAdjG(AdjGraph *G,MTGraph M) 
{               
    G->n=M.n;    //���ڽӾ����еĶ�����������ڽӱ�
    G->e=M.e;     //���ڽӾ����еı���������ڽӱ�
    int i,j,k;
    for(k=0;k<G->n;k++)  //��ʼ��
   {   
      G->vexlist[k].element=M.element[k];
      G->vexlist[k].firstedge=NULL;
   }

    for(i=0;i<M.n;i++)  //��������
{   	
        for(j=0;j<=M.n-1;j++)
        {
           if(M.mat[i][j]==1)
           {   	
              Edgenode *p=new Edgenode;
              p->adjvex=j;                      //��¼�ڽӵ����
              p->next=G->vexlist[i].firstedge;    //ͷ�巨����i������
              G->vexlist[i].firstedge=p;        
           }
        }
    }
}

//�ڽӱ�ת�ڽӾ���
void AdjGtoMTG(AdjGraph G,MTGraph *M) 
{
	M->n=G.n;    //���ڽӾ����еĶ�����������ڽӱ�
    M->e=G.e;     //���ڽӾ����еı���������ڽӱ�
    int i,j;
    for(i=0;i<M->n;i++)  //������ʼ��
   {   
      M->element[i]=G.vexlist[i].element;
   }
   for(i=0;i<M->n;i++)  //�ڽӾ����ʼ�� 
   {
   	 for(j=0;j<M->n;j++)
   	 {
   	 	M->mat[i][j]=0;
	 }
   }
   for(i=0;i<M->n;i++)  //���ڽ���Ϣ���ڽӱ�ת�뵽�ڽӾ��� 
   {
   	   Edgenode *p=G.vexlist[i].firstedge;
   	   p=p->next;
       while(p != NULL)
   	  {
   		int x=p->adjvex;
   		M->mat[x][i]=1;
   		M->mat[i][x]=1;
   		p=p->next;
	  }
	}
}

void DFSAdj(AdjGraph* G,int v)  //�ݹ�ʵ���ڽӱ������������� ,���±�Ϊv�Ľ�㿪ʼ 
{
    Edgenode *p; 
    cout << G->vexlist[v].element << " ";
    visited[v]=1;
    p=G->vexlist[v].firstedge;
    while(p!=NULL)
    {
        if(!visited[p->adjvex])   //����δ���������Ľ�� 
		DFSAdj(G,p->adjvex);
        p=p->next;
    }
}

void DFSAdjfei(AdjGraph* G,int v)  //�ڽӱ�������������ķǵݹ�ʵ�� 
{
    int STACK[Maxnum],top=Maxnum;
    Edgenode *p=NULL;
    STACK[--top]=v;//��һ��ѹջ
    while(top!=Maxnum)
    {
        int w=STACK[top++];
        if(!visited[w])
        {
            cout <<  G->vexlist[w].element << " ";
            visited[w]=1;
        }
        for(p=G->vexlist[w].firstedge; p!=NULL; p=p->next)
        {
		    if(!visited[p->adjvex])
            STACK[--top]=p->adjvex;//����һ��û�з��ʵģ�ѹջ,��������
        }
    }
}

void DFSMTG(MTGraph *G,int v)//�ڽӾ���������ȣ��ݹ飩
{
    int j;
    cout << G->element[v] << " ";
    visited[v]=1;
    for(j=G->n-1; j>=0; j--)
	{
	  if(G->mat[v][j]==1&&!visited[j])  
	  DFSMTG(G,j);
    }
}

void DFSMTGfei(MTGraph *G,int v)//�ڽӾ���������ȣ��ǵݹ飩
{
    int STACK[Maxnum];
    int top=Maxnum;
    STACK[--top]=v;//��һ��ѹջ
    while(top!=Maxnum)
    {
        int w=STACK[top++];
        if(!visited[w])
        {
            cout <<  G->element[w] <<  " ";
            visited[w]=1;
        }//ȡջ���ж�
        for(int i=0; i<G->n; i++)
		{ 
		   if(!visited[i]&&G->mat[w][i])
           STACK[--top]=i;//����һ��û�з��ʵģ�ѹջ,��������
        }
    }
}

void BFSMTG(MTGraph *G,int v)//�ڽӾ���Ĺ������
{
    int Queue[Maxnum],front=0,rear=0,w;
    visited[v]=1;
    Queue[rear++]=v;
    cout << G->element[v] << " ";
    while(front!=rear)
    {
        v=Queue[front++];
        for(w=0; w<G->n; w++)
        {
            if(!visited[w]&&G->mat[v][w])
            {
                cout <<G->element[w] << " ";
                visited[w]=1;
                Queue[rear++]=w;
            }
        }
    }
}

void BFSAdj(AdjGraph* G,int v)    //�ڽӾ���Ĺ�����ȱ��� 
{
    int Queue[Maxnum],front=0,rear=0;
    Edgenode *p=NULL;
    visited[v]=1;
    Queue[rear++]=v;
    cout << G->vexlist[v].element << " ";
    while(front!=rear)
    {
        v=Queue[front++];
        p=G->vexlist[v].firstedge;
        while(p!=NULL)
        {
        	if(!visited[p->adjvex]) 
            {
			   cout <<G->vexlist[p->adjvex].element << " ";
               visited[p->adjvex]=1;
               Queue[rear++]=p->adjvex;
            }
            p=p->next;
        }
    }
}

main()
{
	int n;
	AdjGraph G;
	MTGraph  M;
	int p1=0;
	int i,j;
	int count;
	while(p1==0)
	{
	   int yrc1;
	   int p2=0;
	   int num1;
       int yrc2;
	   int p3=0;
	   int num2;
	   cout<<"��ѡ����Ҫ���еĲ�����"<<endl;
	   cout<<"1.�����ڽӱ�                      2.�����ڽӾ���                  3.�˳�����"<<endl; 
       cin>>n;
       switch(n)
      {
    	  case 1:
    	      creatAdj(&G);
			  while(p2==0)
			  {
			    cout<<"��ѡ����Ҫ���еĲ���:\n1.�����������     2.��������������ǵݹ飩   3.�����������  4.תΪ�ڽӾ���    5.���س�ʼ����"<<endl;
			    cin>>yrc1;
			    switch(yrc1)
			   {
			  	  case 1:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num1;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					DFSAdj(&G,num1);
					cout<<endl; 
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"������"<<count++<<":"; 
                            DFSAdj(&G,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 2:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num1;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					DFSAdjfei(&G,num1);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"������"<<count++<<":"; 
                          DFSAdjfei(&G,i);
                          cout<<endl; 
				        }
			       }
					cout<<endl;
			  	    break;
			  	  case 3:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num1;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					BFSAdj(&G,num1);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"������"<<count++<<":"; 
                          BFSAdj(&G,i);
                          cout<<endl; 
				        }
			       }
					cout<<endl;
					break;
				  case 4:
				  	AdjGtoMTG(G,&M);
					cout<<"ת���ɹ��������ڽӾ������£�"<<endl; 
					for(i=0; i<M.n; i++)
                   {
                   	     cout<<M.element[i]<<" ";
                         for(j=0; j<M.n; j++)
                         cout <<M.mat[i][j] << " ";
                         cout << endl;
                   }
					break;
				  case 5:
				    p2=1;
					break; 
			   }
		      }
		      break;
    	  case 2:
    		  creatMTG(&M);
			  while(p3==0)
			  {
			    cout<<"��ѡ����Ҫ���еĲ�����\n1.�����������     2.��������������ǵݹ飩   3.�����������    4.תΪ�ڽӱ�     5.���س�ʼ����"<<endl;
			    cin>>yrc2;
			    switch(yrc2)
			   {
			  	  case 1:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num2;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					DFSMTG(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"������"<<count++<<":"; 
                          DFSMTG(&M,i);
                          cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 2:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num2;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					DFSMTGfei(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"������"<<count++<<":"; 
                            DFSMTGfei(&M,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
			  	    break;
			  	  case 3:
			  	  	cout<<"��������������ʼ��"<<endl;
					cin>>num2;
					cout<<"�����������"<<endl;
					visitedto0();
					cout<<"������1:";
					BFSMTG(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"������"<<count++<<":"; 
                            BFSMTG(&M,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 4:
				  	MTGtoAdjG(&G,M); 
					cout<<"ת���ɹ��������ڽӱ�����"<<endl; 
					for(i=0;i<G.n;i++)    //��ӡ�����õ��ڽӱ� 
                   {
                       cout<<i<<" "<<G.vexlist[i].element;
                       Edgenode *m=G.vexlist[i].firstedge;
                       while(m!=NULL)
                     {
                         cout<<"->"<<m->adjvex;
                         m=m->next;
                     }
                         cout<<"->NULL"<<endl;
                    }
					break;
				  case 5:
				    p3=1;
					break; 
			   }
		      }
		      break;
    	  case 3:
    	  	p1=1;
    	    break;
	  }
    }
	
	
}
