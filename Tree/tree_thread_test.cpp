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

#include "tree_thread.h"
void visit(TElemType e)
{
	cout<<e<<" ";
}

int main()
{

	BiThrTree H, T;
	/*#ifdef CHAR 
		cout<<"请先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）"<<endl;
	#endif
	#ifdef INT
		cout<<"请先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）"<<endl;
	#endif
	CreateBiThrTree(T);
	InOrderThreading(H,T);
	cout<<"中序遍历线索二叉树："<<endl;
	InOrderTraverse(H, visit);
	cout<<endl;
	DestroyBiThrTree(H);*/

	#ifdef CHAR 
		cout<<"请先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）"<<endl;
	#endif
	#ifdef INT
		cout<<"请先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）"<<endl;
	#endif
	CreateBiThrTree(T);
	PreOrderThreading(H,T);
	cout<<"先序遍历线索二叉树："<<endl;
	PreOrderTraverse(H, visit);
	cout<<endl;
	DestroyBiThrTree(H);



	return 0;
}