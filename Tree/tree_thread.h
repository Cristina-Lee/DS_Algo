#ifndef TREE_THREAD_H
#define TREE_THREAD_H

#include<iostream>
using namespace std;
//在由n个结点组成的二叉树中，有n+1个指针是空指针
//利用空指针指向结点的前驱或后继

//二叉树的二叉线索存储结构
enum PointerTag
{
	Link, Thread
};//Link(0):指针  Thread(1): 线索
typedef struct BiThrNode
{
	TElemType data;
	BiThrNode *lchild, *rchild;//
	PointerTag LTag, RTag;//左右标志	
}*BiThrTree;

void CreateBiThrTree(BiThrTree &T)
{//先序输入线索二叉树中结点的值
	TElemType ch;
	cin>>ch;
	if(ch==Nil)
		T=NULL;
	else
	{
		T=new BiThrNode;
		if(!T)
			exit(-1);
		T->data=ch;
		CreateBiThrTree(T->lchild);
		if(T->lchild)
			T->LTag=Link;//
		CreateBiThrTree(T->rchild);
		if(T->rchild)
			T->RTag=Link;
	}
}

BiThrTree pre;//全局变量，始终指向刚刚访问过的结点
void InThreading(BiThrTree p)
{//通过中序遍历进行中序线索化，线索化之后pre指向最后一个结点
	if(p)
	{
		InThreading(p->lchild);
		if(! p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(! pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
	Thrt=new BiThrNode; //建立头结点
	if(!Thrt)
		exit(-1);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;//右指针回指
	if(!T)
		Thrt->lchild=Thrt;//若T为空二叉树，头结点左指针回指
	else
	{
		Thrt->lchild=T;
		pre=Thrt;//
		InThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
}
void InOrderTraverse(BiThrTree T, void(*Visit)(TElemType))
{//中序遍历线索二叉树的非递归算法
	BiThrTree p;
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link)
			p=p->lchild;
		Visit(p->data);
		while(p->RTag==Thread && p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data);
		}
		p=p->rchild;
	}
}
void PreThreading(BiThrTree p)
{    //There is a bug!!!
	if(!pre->rchild)
	{
		pre->rchild=p;
		pre->RTag=Thread;
	}
	if(!p->lchild)
	{
		p->LTag=Thread;
		p->lchild=pre;
	}
	pre=p;
	if(p->LTag==Link)
		PreThreading(p->lchild);
	if(p->RTag==Link)
		PreThreading(p->rchild);
}
void PreOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	Thrt=new BiThrNode;
	if(!T)
		exit(-1);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T)
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		PreThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
}

void PreOrderTraverse(BiThrTree T, void(*Visit)(TElemType))
{
	BiThrTree p=T->lchild;
	while(p!=T)
	{
		Visit(p->data);
		if(p->LTag==Link)
			p=p->lchild;
		else
			p=p->rchild;
	}
}
void PostThreading(BiThrTree p)
{
	if(p)
	{
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if(!p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
	}
}
void PostOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	Thrt=new BiThrNode;
	if(!T)
		exit(-1);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	if(!T)
		Thrt->lchild=Thrt->rchild=Thrt;
	else
	{
		Thrt->lchild=Thrt->rchild=T;
		pre=Thrt;
		PostThreading(T);
		if(pre->RTag!=Link)
		{
			pre->rchild=Thrt;
			pre->RTag=Thread;
		}
	}
}

void DestroyBiTree(BiThrTree &T)
{
	if(T)
	{
		if(T->LTag==0)
			DestroyBiTree(T->lchild);
		if(T->RTag==0)
			DestroyBiTree(T->rchild);
		delete T;
		T=NULL;
	}
}
void DestroyBiThrTree(BiThrTree &Thrt)
{
	if(Thrt)
	{
		if(Thrt->lchild)
			DestroyBiTree(Thrt->lchild);
		delete Thrt;
		Thrt=NULL;
	}
}

#endif