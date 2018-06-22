#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define MAXSIZE 100
/*
非递归版本的二叉树遍历
*/
struct treeNode{
	char data;
	treeNode * left;
	treeNode * right;
	treeNode():left(NULL),right(NULL){};
};

typedef treeNode CBTType;

// 按先序遍历构建二叉树
void CreateBiTree(treeNode *&root){
	char c;
	cin>>c;
	if(c == '#') root = NULL;
	else{
		root = new treeNode;
		root->data = c;
		CreateBiTree(root->left);
		CreateBiTree(root->right);
	}
}

/*
根据前序遍历访问的顺序，优先访问根结点，然后再分别访问左孩子和右孩子。即对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树；当访问完其左子树时，再访问它的右子树。因此其处理过程如下：

对于任一结点P：

1)访问结点P，并将结点P入栈;

2)判断结点P的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点P，循环至1);若不为空，则将P的左孩子置为当前的结点P;

3)直到P为NULL并且栈为空，则遍历结束。
*/
void DLRTreeNoRecursion(CBTType * root,void (*TreeNodeData)(CBTType * p)){
	stack<CBTType *> st;
	CBTType *ptr = root;
	while(!st.empty() || ptr != NULL){
		while(ptr){
			st.push(ptr);
			TreeNodeData(ptr);
			ptr = ptr->left;
		}
		if(!st.empty()){
			ptr = st.top();
			st.pop();
			ptr = ptr->right;
		}
	}
}

/*
根据中序遍历的顺序，对于任一结点，优先访问其左孩子，而左孩子结点又可以看做一根结点，然后继续访问其左孩子结点，直到遇到左孩子结点为空的结点才进行访问，然后按相同的规则访问其右子树。因此其处理过程如下：

   对于任一结点P，

  1)若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对当前结点P再进行相同的处理；

  2)若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的P置为栈顶结点的右孩子；
  3)直到P为NULL并且栈为空则遍历结束
*/
void LDRTreeNoRecursion(CBTType * root, void(*TreeNodeData)(CBTType*p)){
	stack<CBTType * > st;
	CBTType * ptr = root;
	while(!st.empty() || ptr!= NULL){
		while(ptr!=NULL){
			st.push(ptr);
			ptr = ptr->left;
		}
		if(!st.empty()){
			ptr = st.top();
			st.pop();
			TreeNodeData(ptr);
			ptr = ptr->right;
		}
	}
}

/*
要保证根结点在左孩子和右孩子访问之后才能访问，
因此对于任一结点P，先将其入栈。
如果P不存在左孩子和右孩子，则可以直接访问它；或者P 存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
若非上述两种情况，则将P的右孩子和左孩子依次入栈.
这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。
*/

void LRDTreeNoecursion(CBTType * root,void(*TreeNodeData)(CBTType*p)){
	stack<CBTType * > st;
	CBTType * cur = NULL;
	CBTType * pre = NULL;
	st.push(root);
	while(!st.empty()){
		cur = st.top();
		if((!cur->left && !cur->right)||(pre != NULL && (pre == cur->left|| pre == cur->right))){
			st.pop();
			TreeNodeData(cur);
			pre = cur;
		}
		else{
			if(cur->right){
				st.push(cur->right);
			}
			if(cur->left)
				st.push(cur->left);
		}
	}
}

// 层序遍历
void LevelTravelers(CBTType * root,void(*TreeNodeData)(CBTType*p)){
	queue<CBTType*> Queue;
	Queue.push(root);
	while(!Queue.empty()){
		CBTType * cur = Queue.front();
		Queue.pop();
		TreeNodeData(cur);
		if(cur->left)
			Queue.push(cur->left);
		if(cur->right)
			Queue.push(cur->right);
	}
}

void TreeNodeData (treeNode * p){
	cout<<p->data<<endl;
}

void PreOrder(treeNode * root){
	if(root == NULL)
		return;
	treeNode * st[MAXSIZE];
	treeNode * cur = root;
	int top = -1;
	while(cur != NULL||top >= 0){
		if(cur != NULL){
			st[++top] = cur;
			cout<<cur->data<<endl;
			cur = cur->left;
		}
		else{
			cur = st[top--];
			cur = cur->right;
		}
	}
}


int main(int argc,char ** argv){
	cout<<"按先序遍历构建二叉树，# 表示输入为空"<<endl;
	treeNode * root = NULL;
	CreateBiTree(root);
	void (*ptr)(treeNode * p) = TreeNodeData;
	cout<<"请选择遍历方法"<<endl;
	char input;

	while(cin>>input){
		switch(input){
			case '1':
				cout<<"先序遍历"<<endl;
				DLRTreeNoRecursion(root,ptr);
				break;
			case '2':
				cout<<"中序遍历"<<endl;
				LDRTreeNoRecursion(root,ptr);
				break;
			case '3':
				cout<<"后序遍历"<<endl;
				LRDTreeNoecursion(root,ptr);
				break;
			case '4':
				cout<<"层序遍历"<<endl;
				LevelTravelers(root,ptr);
				break;
			case '5':
				cout<<"数组栈，先序遍历"<<endl;
				PreOrder(root);
				break;
			default:
				cout<<"Invalid input!"<<endl;
		}
	}
	return 0;
}