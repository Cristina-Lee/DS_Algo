#ifndef TREE_BINARY_LinkedList_H
#define TREE_BINARY_LinkedList_H
#include<iostream>
#include<queue>
using namespace std;

#define ClearBiTree DestroyBiTree

typedef struct BiTNode
{
	TElemType data;//存储数据
	BiTNode *lchild, *rchild;//左右孩子指针
}BiTNode, *BiTree;

void InitBiTree(BiTree &T)
{//构造空二叉树
	T=NULL;
}
void DestroyBiTree(BiTree &T)
{
	if(T)
	{
		if(T->lchild)
			DestroyBiTree(T->lchild);
		if(T->rchild)
			DestroyBiTree(T->rchild);
		delete T;
		T=NULL;
	}
}
void CreateBiTree(BiTree &T)
{//按先序次序输入二叉树中结点的值
	TElemType ch;
	cin>>ch;
	if(ch==Nil)
		T=NULL;
	else
	{
		T=new BiTNode;
		if(!T)
		{
			cerr<<"分配内存失败"<<endl;
			exit(-1);
		}
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}

}
bool BiTreeEmpty(BiTree T)
{
	if(T)
		return false;
	else
		return true;
}

int BiTreeDepth(BiTree T)
{
	int i, j;
	if(!T)
		return 0;
	if(T->lchild)
		i=BiTreeDepth(T->lchild);
	else
		i=0;

	if(T->rchild)
		j=BiTreeDepth(T->rchild);
	else
		j=0;

	return i>j?i+1:j+1;//T的深度为其左右子树的深度中的大者+1
}
TElemType Root(BiTree T)
{
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}
TElemType Value(BiTree p)
{
	//返回p所指结点的值
	return p->data;
}

void Assign(BiTree p, TElemType value)
{
	p->data=value;
}

TElemType Parent(BiTree T, TElemType e)
{
	//返回e的双亲
	queue<BiTree> q;
	BiTree temp;
	if(T)
	{
		q.push(T);//树根指针入队列
		while(!q.empty())
		{
			temp=q.front();
			q.pop();
			if(temp->lchild && temp->lchild->data==e || temp->rchild&& temp->rchild->data==e)
				return temp->data;
			else
			{
				if(temp->lchild)
					q.push(temp->lchild);
				if(temp->rchild)
					q.push(temp->rchild);
			}

		}
	}
	return Nil;
}

BiTree Point(BiTree T, TElemType e)
{//返回二叉树T中指向元素值为e的结点的指针
	queue<BiTree> q;
	BiTree a;
	if(T)
	{
		q.push(T);
		while(!q.empty())
		{
			a=q.front();
			q.pop();
			if(a->data==e)
				return a;
			if(a->lchild)
				q.push(a->lchild);
			if(a->rchild)
				q.push(a->rchild);
		}
	}
	return NULL;
}
TElemType LeftChild(BiTree T, TElemType e)
{
	//返回e的左孩子
	BiTree a;
	if(T)
	{
		a=Point(T, e);
		if(a&& a->lchild)
			return a->lchild->data;
	}
	return Nil;
}

TElemType RightChild(BiTree T, TElemType e)
{
	//返回e的右孩子
	BiTree a;
	if(T)
	{
		a=Point(T, e);
		if(a&& a->rchild)
			return a->rchild->data;
	}
	return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if(T)
	{
		a=Parent(T,e);
		if(a!=Nil)
		{
			p=Point(T,a);
			if(p->lchild && p->rchild && p->rchild->data==e)
				return p->lchild->data;
		}
	}
	return Nil;
}

TElemType RightSibling(BiTree T, TElemType e)
{
	TElemType a;
	BiTree p;
	if(T)
	{
		a=Parent(T,e);
		if(a!=Nil)
		{
			p=Point(T,a);
			if(p->lchild && p->rchild && p->lchild->data==e)
				return p->rchild->data;
		}
	}
	return Nil;
}
bool InsertChild(BiTree p, int LR, BiTree c)
{
	//非空树c与T不相交且其右子树为空
	//根据LR为0或1， 插入c为T中p所指结点的左或右子树，p所指结点的原有左或右子树成为c的右子树
	if(p)
	{
		if(LR==0)
		{
			c->rchild=p->lchild;
			p->lchild=c;
		}
		else
		{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return true;
	}
	return false;
}
bool DeleteChild(BiTree p, int LR)
{
	//根据LR为0或1，删除p所指结点的左或右子树
	if(p)
	{
		if(LR==0)
			ClearBiTree(p->lchild);
		else
			ClearBiTree(p->rchild);
		return true;
	}
	return false;
}
//顺序栈








void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild, Visit);
	}
}


#endif