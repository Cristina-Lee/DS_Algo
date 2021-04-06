
#define CHAR 0 //字符型
#if CHAR
	typedef char TElemType;
	TElemType Nil=' ';
#else
	typedef int TElemType;
	TElemType Nil=0;
#endif
#include "tree_sequence.h"

void visit(TElemType e)
{
	cout<<e<<' ';
}

int main()
{
	int i;
	int j;
	position p;
	TElemType e;
	SqBiTree T,s;

	InitBiTree(T);
	CreateBiTree(T);
	cout<<"建立二叉树后，树空否？(1：是  0：否)"<<BiTreeEmpty(T)<<" 树的深度= "<<BiTreeDepth(T)<<endl;

	i=Root(T,e);
	if(i)
		cout<<"二叉树的根为 "<<e<<endl;
	else
		cout<<"树空， 无根"<<endl;

	cout<<"层序遍历二叉树："<<endl;
	LevelOrderTraverse(T, visit);

	cout<<"中序遍历二叉树："<<endl;
	InOrderTraverse(T, visit);

	cout<<"后序遍历二叉树："<<endl;
	PostOrderTraverse(T, visit);

	cout<<"请输入待修改结点的层号 本层序号：";
	cin>>p.level>>p.order;
	e=Value(T,p);
	cout<<"待修改结点的原值为 "<<e<<" 请输入新值：";
	cin>>e;
	Assign(T, p, e);

	cout<<"先序遍历二叉树："<<endl;
	PreOrderTraverse(T, visit);

	cout<<"结点"<<e<<"的双亲为"<<Parent(T,e)<<", 左右孩子分别为";
	cout<<LeftChild(T,e)<<","<<RightChild(T,e)<<"; 左右兄弟分别为";
	cout<<LeftSibling(T,e)<<","<<RightSibling(T,e)<<endl;

	InitBiTree(s);
	cout<<"建立右子树为空的树s："<<endl;
	CreateBiTree(s);
	cout<<"树s插入到树T中，请输入树T中树s的双亲结点 s为左（0）或右（1）子树：";
	cin>>e>>j;
	InsertChild(T, e, j, s);
	Print(T);

	cout<<"删除子树，请输入待删除子树根结点的层号 本层序号 左（0）或右（1）子树：";
	cin>>p.level>>p.order>>j;
	DeleteChild(T,p,j);
	Print(T);
	ClearBiTree(T);
	cout<<"清除二叉树后，树空否？(1：是  0：否)"<<BiTreeEmpty(T)<<" 树的深度= "<<BiTreeDepth(T)<<endl;

	i=Root(T,e);
	if(i)
		cout<<"二叉树的根为"<<e<<endl;
	else
		cout<<"树空，无根"<<endl;

	return 0;

}