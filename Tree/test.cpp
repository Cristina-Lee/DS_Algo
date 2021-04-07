#define CHAR 
//#define INT
#ifdef CHAR
	typedef char TElemType;
	TElemType Nil='#';
#endif
#ifdef INT
	typedef int TElemType;
	TElemType Nil=0;//整型以0为空
#endif

#include "tree_trifurcatelinkedlist.h"
void visit(TElemType e)
{
	cout<<e<<" ";
}

int main()
{
	int i;
	BiPTree T, p, c;
	TElemType e1, e2;

	InitBiTree(T);
	cout<<"构造空二叉树后，树空否？（1：是 0：否）"<<BiTreeEmpty(T)<<"  树的深度为"<<BiTreeDepth(T)<<endl;

	e1=Root(T);
	if(e1!=Nil)
		cout<<"二叉树的根为 "<<e1<<endl;
	else
		cout<<"树空，无根"<<endl;
	#ifdef CHAR 
		cout<<"请先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）"<<endl;
	#endif
	#ifdef INT
		cout<<"请先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）"<<endl;
	#endif
	CreateBiTree(T);
	cout<<"建立二叉树后，树空否？（1：是 0：否）"<<BiTreeEmpty(T)<<"  树的深度为"<<BiTreeDepth(T)<<endl;
	e1=Root(T);
	if(e1!=Nil)
		cout<<"二叉树的根为 "<<e1<<endl;
	else
		cout<<"树空，无根"<<endl;

	cout<<"中序递归遍历二叉树："<<endl;
	InOrderTraverse(T, visit);
	cout<<endl;
	cout<<"后序递归遍历二叉树："<<endl;
	PostOrderTraverse(T, visit);
	cout<<endl;
	cout<<"层序遍历二叉树："<<endl;
	LevelOrderTraverse(T, visit);
	cout<<endl;

	cout<<"请输入一个结点的值: ";
	cin>>e1;
	p=Point(T, e1);
	cout<<"结点的值为"<<Value(p)<<endl;
	cout<<"欲改变此结点的值，请输入新值：";
	cin>>e2;
	Assign(p, e2);
	cout<<"层序递归遍历二叉树："<<endl;
	LevelOrderTraverse(T, visit);
	cout<<endl;
	e1=Parent(T, e2);
	if(e1!=Nil)
		cout<<e2<<"的双亲是"<<e1<<endl;
	else
		cout<<e2<<"没有双亲"<<endl;

	e1=LeftChild(T, e2);
	if(e1!=Nil)
		cout<<e2<<"的左孩子是"<<e1<<endl;
	else
		cout<<e2<<"没有左孩子"<<endl;

	e1=RightChild(T, e2);
	if(e1!=Nil)
		cout<<e2<<"的右孩子是"<<e1<<endl;
	else
		cout<<e2<<"没有右孩子"<<endl;

	e1=LeftSibling(T, e2);
	if(e1!=Nil)
		cout<<e2<<"的左兄弟是"<<e1<<endl;
	else
		cout<<e2<<"没有左兄弟"<<endl;

	e1=RightSibling(T, e2);
	if(e1!=Nil)
		cout<<e2<<"的右兄弟是"<<e1<<endl;
	else
		cout<<e2<<"没有右兄弟"<<endl;

	cout<<"构造一个右子树为空的二叉树c: "<<endl;
	#ifdef CHAR 
		cout<<"请先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）"<<endl;
	#endif
	#ifdef INT
		cout<<"请先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）"<<endl;
	#endif
	CreateBiTree(c);
	cout<<"先序递归遍历二叉树c："<<endl;
	PreOrderTraverse(c,visit);
	cout<<endl;

	cout<<"树c插入到树T中，请输入树T中树c的双亲结点 c为左(0)或右(1)子树：";
	cin>>e1>>i;
	p=Point(T,e1);//p是T中树c的双亲结点指针
	InsertChild(p, i, c);
	cout<<"先序递归遍历二叉树："<<endl;
	PreOrderTraverse(T,visit);
	cout<<endl;

	cout<<"删除子树，请输入待删除子树的双亲结点 左(0)或右(1)子树：";
	cin>>e1>>i;
	p=Point(T, e1);
	DeleteChild(p,i);
	cout<<"先序递归遍历二叉树："<<endl;
	PreOrderTraverse(T,visit);
	cout<<endl;
	
	DestroyBiTree(T);

	return 0;
}