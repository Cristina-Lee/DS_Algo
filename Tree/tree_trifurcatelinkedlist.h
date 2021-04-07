//Trifurcate linked list
//二叉树的三叉链表存储结构比二叉链表多一个指向双亲结点的指针
#ifndef TREE_TRIFURCATE_LINKEDLIST_H
#define TREE_TRIFURCATE_LINKEDLIST_H

#include<iostream>
#include<queue>

using namespace std;
typedef struct BiTPNode
{
	TElemType data;
	BiTPNode *parent, *lchild, *rchild;
}BiTPNode, *BiPTree;

#define ClearBiTree DestroyBiTree //清空二叉树和销毁二叉树的操作是一样的
void InitBiTree(BiPTree &T)
{
	T=NULL;
}
void DestroyBiTree(BiPTree &T)
{
	if(T)
	{
		if(T->lchild)
			DestroyBiTree(T->lchild);
		if(T->rchild)
			DestroyBiTree(T->rchild);

		delete T;//释放根结点
		T=NULL;
	}
}
void CreateBiTree(BiPTree &T)
{
	//按先序次序输入
	TElemType ch;
	cin>>ch;
	if(ch==Nil)
		T=NULL;
	else
	{
		T=new BiTPNode;
		if(!T)
		{
			cout<<"memory allocation failed"<<endl;
			exit(-1);
		}
		T->data=ch;
		T->parent=NULL;
		CreateBiTree(T->lchild);
		if(T->lchild)
			T->lchild->parent=T;
		CreateBiTree(T->rchild);
		if(T->rchild)
			T->rchild->parent=T;
	}
}

bool BiTreeEmpty(BiPTree T)
{
	if(T)
		return false;
	else
		return true;
}
int BiTreeDepth(BiPTree T)
{
	int i=0, j=0;
	if(!T)
		return 0;
	if(T->lchild)
		i=BiTreeDepth(T->lchild);
	if(T->rchild)
		j=BiTreeDepth(T->rchild);

	return i>j?i+1:j+1;
}

TElemType Root(BiPTree T)
{
	if(T)
		return T->data;
	else
		return Nil;
}
TElemType Value(BiPTree p)
{
	return p->data;
}
void Assign(BiPTree p, TElemType value)
{
	p->data=value;
}
BiPTree Point(BiPTree T, TElemType e)
{
	queue<BiPTree> q;
	BiPTree a;
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
TElemType Parent(BiPTree T, TElemType e)
{
	BiPTree a;
	if(T)
	{
		a=Point(T,e);
		if(a && a!=T)
			return a->parent->data;
	}
	return Nil;
}
TElemType LeftChild(BiPTree T, TElemType e)
{
	//返回e的左孩子
	BiPTree a;
	if(T)
	{
		a=Point(T, e);
		if(a&& a->lchild)
			return a->lchild->data;
	}
	return Nil;
}
TElemType RightChild(BiPTree T, TElemType e)
{
	//返回e的右孩子
	BiPTree a;
	if(T)
	{
		a=Point(T, e);
		if(a&& a->rchild)
			return a->rchild->data;
	}
	return Nil;
}
TElemType LeftSibling(BiPTree T, TElemType e)
{
	BiPTree a;
	if(T)
	{
		a=Point(T,e);
		if(a && a!=T && a->parent->lchild && a->parent->lchild!=a)
			return a->parent->lchild->data;
	}
	return Nil;
}
TElemType RightSibling(BiPTree T, TElemType e)
{
	BiPTree a;
	if(T)
	{
		a=Point(T,e);
		if(a && a!=T && a->parent->rchild && a->parent->rchild!=a)
			return a->parent->rchild->data;
	}
	return Nil;
}
bool InsertChild(BiPTree p, int LR, BiPTree c)
{
	if(p)
	{
		if(LR==0)
		{
			c->rchild=p->lchild;
			if(c->rchild)
				c->rchild->parent=c;
			p->lchild=c;
			c->parent=p;
		}
		else
		{
			c->rchild=p->rchild;
			if(c->rchild)
				c->rchild->parent=c;
			p->rchild=c;
			c->parent=p;
		}
		return true;
	}
	return false;
}
bool DeleteChild(BiPTree p, int LR)
{
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
void PreOrderTraverse(BiPTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild,Visit);
	}
}
void InOrderTraverse(BiPTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T->data);
		InOrderTraverse(T->rchild,Visit);
	}
}
void PostOrderTraverse(BiPTree T, void(*Visit)(TElemType))
{
	if(T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild,Visit);
		Visit(T->data);
	}
}
void LevelOrderTraverse(BiPTree T, void(*Visit)(TElemType))
{
	queue<BiPTree> q;
	BiPTree a;
	if(T)
	{
		q.push(T);
		while(!q.empty())
		{
			a=q.front();
			q.pop();
			Visit(a->data);
			if(a->lchild)
				q.push(a->lchild);
			if(a->rchild)
				q.push(a->rchild);
		}
	}
}
#endif