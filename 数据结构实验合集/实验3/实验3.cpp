#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
int cnt1 = 0;
int cnt2 = 0;
//����������Ĵ洢�ṹ
typedef struct celltype
{
    int data;
    struct celltype *lchild,*rchild;
}BSTNode;

//�Զ��������������������������
void Recur_InOrder(BSTNode *F)
{
	if(F)
    {
		Recur_InOrder(F->lchild);
        cout << F->data<<" ";
		Recur_InOrder(F->rchild);
	}
}
//�������ĸ߶�
int Height(BSTNode *F)
{
	int n,m;
	if(F == NULL)
		return 0;
	else
    {
		m = Height(F->lchild);
		n = Height(F->rchild);
	}
	if(m>n)
	return m+1;
	else
	return n+1;
}

//����������Ĳ��Ҳ���:����F�в��ҹؼ�ֵk������k���ڵĽ��p
BSTNode *Search(int k,BSTNode *F)
{
	if(k%2 == 1)       //��kΪ��������������ٴλ���ҳɹ� 
     cnt1++;
    if(k%2 == 0)  //��kΪż������������ٴλ����ʧ�� 
	 cnt2++;
	BSTNode *p = F;
	if(p == NULL)
    {
        cout <<"����ʧ��"<<endl;
        return NULL;
    }
    if(k == p->data)      //��ֹ�������ҵ���Ŀ��
    {
        cout <<"���ҳɹ�"<<endl;
        return p;
    }
    else if(k < p->data)
        return Search(k,p->lchild); //k<��ǰ���Ĺؼ���ֵ��ȥp���������еݹ����
    else if(k > p->data)
        return Search(k,p->rchild); //k>��ǰ���Ĺؼ���ֵ��ȥp���������еݹ����
}

//����������Ĳ������������F�в����¼key
void InsertBST(int key,BSTNode * &F)
{
    if(F == NULL)            //�����ǰ��F�գ����²���Ľ��Ϊ���ĸ����
    {
        F = new BSTNode;
        F->data = key;
        F->lchild = NULL;
        F->rchild = NULL;
    }
    else if(key < F->data)   //���������Ԫ��С�ڵ�ǰ���ؼ���ֵ����ݹ齫����뵱ǰ����������
        InsertBST(key,F->lchild);
    else if(key > F->data)   //���������Ԫ�ش��ڵ�ǰ���ؼ���ֵ����ݹ齫����뵱ǰ����������
        InsertBST(key,F->rchild);
}
//ɾ��F����С���
int deletemin(BSTNode * &F)
{
    int tmp;
    BSTNode *p;
    //��F������Ϊ�գ���F��Ϊ����������С��㣬�ݹ����
    if(F->lchild == NULL)
    {
        p = F;
        tmp = F->data;
        F = F->rchild;
        delete p;
        return tmp;    //��С���Ĺؼ���ֵ��Ϊtmp
    }
    else          //���������գ���С�������������
        return deletemin(F->lchild);
}
//�����������ɾ��������
void DeleteB(int k,BSTNode * &F)
{
    if(!F)
        cout <<"ɾ��ʧ�ܣ�δ���ҵ��ùؼ���ֵ"<<endl;
    if(k < F->data)
        DeleteB(k,F->lchild);
    else if(k > F->data)
        DeleteB(k,F->rchild);
    else if(k ==  F->data)            //�ҵ��˴�ɾ���Ľ��F
    {
        if((F->rchild == NULL) && (F->lchild == NULL))  //1.��ɾ�������Ҷ�ӽ�㣬ֱ��ɾ��
            F = NULL;
        else if((F->rchild == NULL)  && (F->lchild != NULL))   //2.1��ɾ�����ֻ������������ֱ�����������̳б�ɾ���
            F = F->lchild;
        else if((F->lchild == NULL)  && (F->rchild != NULL))  //2.2��ɾ�����ֻ������������ֱ�����������̳б�ɾ���
            F = F->rchild;
        /* ��ɾ���Ľ�������������У��ü̳н�㣨��ɾ�ڵ�����������С��㣩�����ɾ��㣬
        ���ڼ̳н�㣨ֻ�������ҽ���ֱ����Ҷ�ӽ�㣩�ٰ���1,2���� */
        else if((F->lchild != NULL) && (F->rchild != NULL))
            F->data = deletemin(F->rchild);
    }
}
//������������� 
BSTNode* CreatBST()
{
    BSTNode *F =NULL;
    int key;                //�ؼ���ֵ
    for(key = 1; key < 2048; key += 2) //˳����� 
    {
    	cout<<key<<" ";
        InsertBST(key,F);  //�����¼key
    }
    cout<<endl;
    return F;
}


//������н�������������㷨
BSTNode *CreatBSTrandom()
{
    BSTNode *F = NULL;
    int key,cnt = 0;
	int rep,i,j,k;
    int K[1024] = {0};
    srand((unsigned int)time(NULL));
    key = rand()%2048;
    while(1)              //�õ���һ����
    {
        if((key%2) == 1) //keyΪ���� 
        {
            InsertBST(key,F);                //�����¼key
            cout<<key<<" ";
            K[cnt] = key;
            cnt++;
            break;
        }
        key = rand()%2048;
    }
    while(cnt<1024)
    {
        key = rand()%2048;
        if((key%2) == 1)  //��keyΪ���� 
        {
            rep = 0;
            for(i = 0; i <= cnt; i++)
            {
                if(key == K[i])               //���õ���ÿ���������ŵ�K[]�У����ڼ���Ƿ��ظ�
                    rep = 1;
            }
            if(!rep)
            {
                 InsertBST(key,F);                //�����¼key
                 cout<<key<<" ";
                 K[cnt] = key;
                 cnt++;
            }
        }
    }
    cout<<endl;
    return F;
}

//���ҳɹ���ʧ�ܵ�ƽ�����ҳ���
void ASLB(BSTNode *F)
{
    int i;
    int sum1 = 0,sum2 = 0;
    double ASLS,ASLF;
    int height = Height(F);
    cout<<"BST�ĸ߶�Ϊ:"<<height<<endl;
    for(i = 0; i <= 2048; i++)
    {
        cnt1 = 0;
        cnt2 = 0;
        Search(i,F);
        sum1+= cnt1;
        sum2+= cnt2;
    }
    ASLS = sum1/1024.0;
    ASLF = sum2/1025.0;
    cout <<"BST���ҳɹ���ƽ�����ҳ���Ϊ"<<ASLS<<endl;
    cout <<"BST����ʧ�ܵ�ƽ�����ҳ���Ϊ"<<ASLF<<endl;
}

//�۰�����㷨��
int cnt3 = 0;
int cnt4 = 0;
int BF[1024];
int BinSearch(int key)
{
    int i;
    int low,up,mid;
    low = 0;
    up = 1023;
    for(i = 1; i < 2048; i += 2)  //���������� 
    {
        BF[i/2] = i;
    }
    while(low <= up)
    {
        if(key%2)   //kΪ���� 
          cnt3++;
        else       //kΪż�� 
		  cnt4++;
        mid = (low + up)/2;
        if(BF[mid] == key)
        {
            cout <<"���ҳɹ�"<<endl;
            return mid;
        }
        else if(BF[mid] > key)
              up = mid -1;
        else  low = mid +1;
    }
    cout <<"����ʧ��"<<endl;
    return 0;
}
//�۰���ҵĲ��ҳɹ���ʧ�ܵ�ƽ�����ҳ���
void BinASL()
{
    int i;
    int sum3 = 0,sum4 = 0;
    float  ASLBS,ASLBF;
    for(i = 0; i <= 2048; i++)
    {
        cnt3 = 0;
        cnt4 = 0;
        BinSearch(i);
        sum3 += cnt3;
        sum4 += cnt4;
    }
    ASLBS = sum3/1024.0;
    ASLBF = sum4/1025.0;
    cout <<"�۰���ҳɹ���ƽ�����ҳ���Ϊ"<<ASLBS<<endl;
    cout <<"�۰����ʧ�ܵ�ƽ�����ҳ���Ϊ"<<ASLBF<<endl;
}

int main()
{
	BSTNode *p;
	BSTNode *find;
	int key;
	int cho;
	int yrc;
	while(1)
  { 
  	cout <<"��ѡ����:"<<endl;
	cout <<"0.˳�����뽨��BST"<<endl;
    cout <<"1.������뽨��BST"<<endl;
    cout <<"2.BST����һ��Ԫ��"<<endl;
    cout <<"3.����һ��Ԫ��"<<endl;
    cout <<"4.ɾ��һ��Ԫ��"<<endl;
    cout <<"5.�۰����"<<endl;
    cout <<"6.BST���ҳɹ���ʧ��ƽ�����ҳ���"<<endl;
    cout <<"7.�۰���ҳɹ���ʧ��ƽ�����ҳ���"<<endl;
    cout <<"8.�����˳�"<<endl; 
    cin>>cho;
    switch(cho)
   {
	  case 0:
      	cout<<"�����������£�"<<endl;
      	p = CreatBST();
      	cout<<"����BST���������������£�"<<endl; 
      	Recur_InOrder(p);
      	cout<<endl;
        break;
      case 1:
      	cout<<"�����������£�"<<endl;
      	p = CreatBSTrandom();
      	cout<<"����BST���������������£�"<<endl; 
      	Recur_InOrder(p);
      	cout<<endl;
        break;
      case 2:
      	cout<<"��������Ҫ���ҵĹؼ���"<<endl;
		cin>>key;
	    cnt1=0; 
	    cnt2=0;
		find=Search(key,p);
		if(key%2 == 0)  
		cout<<"�Ƚϴ�����"<<cnt2<<endl;
		else
		cout<<"�Ƚϴ�����"<<cnt1<<endl; 
		break;
	  case 3:
	  	cout<<"��ѡ����Ҫ����Ĺؼ���"<<endl;
		cin>>key; 
		InsertBST(key,p);
		cout<<"������BST����������Ϊ��"<<endl;
		Recur_InOrder(p);
		break;
	  case 4:
	  	cout<<"��ѡ����Ҫɾ���Ĺؼ���"<<endl;
		cin>>key;
		DeleteB(key,p);
		cout<<"ɾ�����BST����������Ϊ��"<<endl;
		Recur_InOrder(p);
		break;
	  case 5:
	  	cout <<"������Ҫ���ҵĹؼ���ֵ��";
        cin >>key;
        cnt3=0; 
	    cnt4=0;
        yrc = BinSearch(key);
        if(yrc!=0 || key==1 ) 
        cout<<"�±�Ϊ��"<<yrc<<endl;
        if(key%2 == 0)  
		cout<<"�Ƚϴ�����"<<cnt4<<endl;
		else
		cout<<"�Ƚϴ�����"<<cnt3<<endl; 
        break;
      case 6:
      	ASLB(p);
      	break;
      case 7:
      	BinASL();
      	break;
      case 8:
        exit(0);
      default:
        cout <<"�����������������:";
        cin >> cho;
    }
  }	
 } 
