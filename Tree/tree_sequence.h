#ifndef TREE_SEQUENCE_H
#define TREE_SEQUENCE_H
//二叉树的顺序存储结构适合存储完全二叉树或近似完全二叉树
//此程序以完全二叉树形式输入
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

#define MAX_TREE_SIZE  100 //二叉树的最大结点树
//typedef char TElemType; //树元素类型
typedef  TElemType SqBiTree[MAX_TREE_SIZE];  //0号单元存储根结点
struct position
{
      int level, order;//结点的层， 本层序号（按满二叉树计算）
};

#define ClearBiTree InitBiTree
#define DestroyBiTree InitBiTree

void InitBiTree(SqBiTree  T)
{//构造空二叉树T。因为T是数组名，所i不需要&
      for(int i=0; i<MAX_TREE_SIZE; i++)
            T[i]=Nil;
}

void CreateBiTree(SqBiTree T)
{//按层序次序输入二叉树结点的值，构造顺序存储的二叉树T
      InitBiTree(T);
      #if TypeFLag //结点类型为字符时TypeFLag=1
      char s[MAX_TREE_SIZE];
      cout<<"请按层序输入结点的值（字符），空格表示空结点， 结点数<="<<MAX_TREE_SIZE<<" : "<<endl;
      gets(s);//输入字符串，头文件cstdio
      len=strlen(s);//Header: cstring
      for(int i=0; i<len; i++)
            T[i]=s[i];

      #else
      cout<<"请按层序输入结点的值（整型），0表示空结点，输999结束。结点数<="<<MAX_TREE_SIZE<<": "<<endl;
      int i=0;
      while(1)
      {
            cin>>T[i];
            if(T[i]==999)
            {
                  T[i]=Nil;
                  break;
            }
            i++;
      }
      #endif
      //序号为i的结点，其双亲序号为(i+1)/2-1, 其左右孩子序号分别为2i+1, 2i+2;序号从0开始
      for(int i=1; i<MAX_TREE_SIZE; i++)
            if(i!=0 && T[(i+1)/2 -1]==Nil && T[i]!=Nil)//此结点不空无双亲且不是根
            {
                  cerr<<"出现无双亲的非根结点 : "<<T[i]<<endl;
                  exit(-1);
            }
}

bool BiTreeEmpty(SqBiTree T)
{//判断二叉树是否为空
      if(T[0]==Nil)
            return true;
      else
            return false;

}

int BiTreeDepth(SqBiTree T)
{//若二叉树存在，返回T的深度：二叉树叶子结点的最大层次数
     int i, j=-1;
     for(i=MAX_TREE_SIZE-1; i>=0; i--)
      if(T[i]!=Nil)
            break;//找到最后一个结点
      i++;//利用求深度公式
      
      do{
            j++;
      }while(i>=pow(2, j)); //存疑
      return j;
}

bool Root(SqBiTree T, TElemType &e)
{//当T不空时，用e返回T的根
      if(BiTreeEmpty(T))
            return false;
      else
      {
            e=T[0];
            return true;
      }
}

TElemType Value(SqBiTree T, position e)
{//二叉树T存在，e是T中某个结点的位置,返回处于位置e的结点的值
      return T[int(pow(2, e.level-1)+e.order-2)];
}

bool Assign(SqBiTree T, position e, TElemType value)
{//赋值
      int i=int(pow(2, e.level-1)+e.order-2);
      if(value!=Nil && T[(i+1)/2-1]==Nil)//给叶子结点赋非空值但双亲为空
            return false;
      else if(value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil))//给双亲赋空值但有孩子结点不为空
            return false;
      T[i]=value;
      return true;
}

TElemType Parent(SqBiTree T, TElemType e)
{//二叉树T存在，e中T中某个结点，返回其双亲
      int i=0;
      if(BiTreeEmpty(T))
            return Nil;
      for(i=1; i<MAX_TREE_SIZE-1; i++)
            if(T[i]==e)
                  return T[(i+1)/2-1];
      return Nil;
}

TElemType LeftChild(SqBiTree T, TElemType e)
{//返回e的左孩子
      if(T[0]==Nil)
            return Nil;
      for(int i=0; i<=MAX_TREE_SIZE-1; i++)
            if(T[i]==e)
                  return T[i*2+1];
      return Nil;
}

TElemType RightChild(SqBiTree T, TElemType e)
{//返回e的右孩子
      if(T[0]==Nil)
            return Nil;
      for(int i=0; i<=MAX_TREE_SIZE-1; i++)
            if(T[i]==e)
                  return T[i*2+2];
      return Nil;
}

TElemType LeftSibling(SqBiTree T, TElemType e)
{//返回e的左兄弟，若e是T的左孩子或无左兄弟，返回“空”
      if(T[0]==Nil)
            return Nil;
      for(int i=0; i<=MAX_TREE_SIZE-1; i++)
            if(T[i]==e && i%2==0)  //找到e且其序号为偶数是右孩子
                  return T[i-1];
      return Nil;
}
TElemType RightSibling(SqBiTree T, TElemType e)
{//返回e的右兄弟，若e是T的右孩子或无右兄弟，返回“空”
      if(T[0]==Nil)
            return Nil;
      for(int i=0; i<=MAX_TREE_SIZE-1; i++)
            if(T[i]==e && i%2)  //找到e且其序号为偶数是右孩子
                  return T[i+1];
      return Nil;
}

void Move(SqBiTree q, int j, SqBiTree T, int i)
{
      if(q[2*j+1]!=Nil)
            Move(q, (2*j+1), T, (2*i+1));
      if(q[2*j+2]!=Nil)
            Move(q, (2*j+2), T, (2*i+2));

      T[i]=q[j];
      q[j]=Nil;
}

void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree C)
{
      int j, k, i=0;
      for(j=0; j<int(pow(2, BiTreeDepth(T)))-1; j++)
            if(T[j]==p)
                  break;
      k=2*j+1+LR;//k为p的左孩子或右孩子的序号
      if(T[k]!=Nil)
            Move(T, k, T, 2*k+2);
      Move(C,i, T, k);
}//？？？


bool DeleteChild(SqBiTree T, position p, int LR)
{//根据LR为0或1，删除T中p所指结点的左或右子树
      queue<int> q;//容器:队列
      int i=(int)pow(2, p.level-1)+p.order-2;//将层、本层序号转化为矩阵的序号
      if(T[i]==Nil)
            return false;

      i=i*2+1+LR;//待删除子树的根结点在树中的序号
      while(1)
      {
            if(T[2*i+1]!=Nil)
                  q.push(2*i+1);
            if(T[2*i+2]!=Nil)
                  q.push(2*i+2);
            T[i]=Nil;

            if(!q.empty())
            {
                  i=q.front();
                  q.pop();
            }
            else
                  break;
      }
      return true;
}

void (*VisitFunc)(TElemType e);

void PreTraverse(SqBiTree T, int i)
{
      VisitFunc(T[i]);
      if(T[2*i+1]!=Nil)
            PreTraverse(T, 2*i+1);
      if(T[2*i+2]!=Nil)
            PreTraverse(T, 2*i+2);
}
void PreOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{//先序遍历T，对每个结点调用函数Visit一次且仅一次
      VisitFunc=Visit;
      if(!BiTreeEmpty(T))
            PreTraverse(T, 0);
      cout<<endl;
}
void InTraverse(SqBiTree T, int i)
{
      if(T[2*i+1]!=Nil)
            InTraverse(T, 2*i+1);
      VisitFunc(T[i]);
      if(T[2*i+2]!=Nil)
            InTraverse(T, 2*i+2);
}
void InOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{//先序遍历T，对每个结点调用函数Visit一次且仅一次
      VisitFunc=Visit;
      if(!BiTreeEmpty(T))
            InTraverse(T, 0);
      cout<<endl;
}
void PostTraverse(SqBiTree T, int i)
{
      if(T[2*i+1]!=Nil)
            PostTraverse(T, 2*i+1);
      if(T[2*i+2]!=Nil)
            PostTraverse(T, 2*i+2);
      VisitFunc(T[i]);
}
void PostOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{//先序遍历T，对每个结点调用函数Visit一次且仅一次
      VisitFunc=Visit;
      if(!BiTreeEmpty(T))
            PostTraverse(T, 0);
      cout<<endl;
}
void LevelOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
{
      int i=MAX_TREE_SIZE-1, j;
      while(T[i]==Nil)
            i--;
      for(j=0; j<=i; j++)
            if(T[j]!=Nil)
                  Visit(T[j]);
      cout<<endl;
}
void Print(SqBiTree T)
{//逐层、按本层序号输出二叉树
      int j, k;
      position p;
      TElemType e;
      for(j=1; j<=BiTreeDepth(T); j++)
      {
            cout<<"第"<<j<<"层：";
            for(k=1; k<=pow(2, j-1); k++)
            {
                  p.level=j;
                  p.order=k;
                  e=Value(T,p);
                  if(e!=Nil)
                        cout<<k<<": "<<e<<' ';
            }
            cout<<endl;
      }
}

#endif