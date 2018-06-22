#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define MAXSIZE 10

typedef struct CBT {
	string DATA;
	struct CBT * left;
	struct CBT * right;
}CBTType;

CBTType * initTree(){
	string input ;
	CBTType * node = new CBTType;
	if(node != NULL){
		cout<<"请输入一串字符串，初始化根节点:"<<endl;
		cin>>input;
		node->DATA = input;
		node->left = node->right = NULL;
		return node;
	}
	else{
		return NULL;
	}
}

CBTType * TreeFindNode(CBTType * treeNode,string data){
	CBTType * ptr;

	if(treeNode->DATA == data){
		return treeNode;
	}
	else{
		if(ptr = TreeFindNode(treeNode->left,data)){
			return ptr;
		}
		else if(ptr = TreeFindNode(treeNode->right,data)){
			return ptr;
		}
		else
			return NULL;
	}
}

void AddTreeNode(CBTType * treeNode){
	CBTType * pnode,*parentNode;
	
	string data,choice,parentData;
	
	cout<<"请输入父节点DATA"<<endl;
	cin>>parentData;

	parentNode = TreeFindNode(treeNode,parentData);
	if(parentNode){
		cout<<"请输入节点DATA"<<endl;
		cin>>data;
		cout<<"请输入节点方向"<<endl;
		cin>>choice;
		pnode = new CBTType;
		pnode->DATA = data;
		pnode->left = pnode->right = NULL;
		if(choice == "left"){
			if(parentNode->left){
				cout<<"左子树不为空"<<endl;
				delete pnode;
			}
			else
				parentNode->left = pnode;
		}
		else if(choice == "right"){
			if(parentNode->right){
				cout<<"右子树不为空"<<endl;
				delete pnode;
			}
			else
				parentNode->right = pnode;
		}
		else{
			cout<<"invalid choice:"<<choice<<endl;
			delete pnode;
		}
	}
	else
		cout<<"找不到父节点 node->DATA == "<<parentData<<endl;
}

int TreeDepth(CBTType * treeNode){
	int leftDepth,rightDepth;
	if(treeNode == NULL){
		return 0;
	}
	else{
		leftDepth = TreeDepth(treeNode->left);
		rightDepth = TreeDepth(treeNode->right);
		int depth = leftDepth > rightDepth ? leftDepth+1 : rightDepth+1;
		return depth;
	}
}

void ClearTree(CBTType * treeNode){
	if(treeNode){
		ClearTree(treeNode->left);
		ClearTree(treeNode->right);
		delete treeNode;
		treeNode = NULL;
	}
}

void TreeNodeData(CBTType * treeNode){
	cout<<"节点内容是:"<<treeNode->DATA<<endl;
}

void LevelTree(CBTType * treeNode,void (*TreeNodeData) (CBTType * p)){
	CBTType * p;
	CBTType * queue[MAXSIZE];
	int head,tail = MAXSIZE - 1;
	if(treeNode){
		tail = (tail + 1) % MAXSIZE;
		queue[tail] = treeNode;
	}
	while(head != tail){
		head = (head + 1)%MAXSIZE;
		p = queue[head];
		TreeNodeData(p);
		if(p->left){
			tail = (tail + 1)%MAXSIZE;
			queue[tail] = p->left;
		}
		if(p->right){
			tail = (tail + 1) % MAXSIZE;
			queue[tail] = p->right;
		}
	}
}

//前序遍历，先节点，再左子树，再右子树
void DLRTree(CBTType * treeNode,void (*TreeNodeData)(CBTType * p)){
	if(treeNode){
		TreeNodeData(treeNode);
		DLRTree(treeNode->left,TreeNodeData);
		DLRTree(treeNode->right,TreeNodeData);
	}
}

//中序遍历
void LDRTree(CBTType * treeNode,void (*TreeNodeData)(CBTType * p)){
	if(treeNode){
		LDRTree(treeNode->left,TreeNodeData);
		TreeNodeData(treeNode);
		LDRTree(treeNode->right,TreeNodeData);
	}
}

//后序遍历
void LRDTree(CBTType * treeNode,void (*TreeNodeData)(CBTType * p)){
	if(treeNode){
		LRDTree(treeNode->left,TreeNodeData);
		LRDTree(treeNode->right,TreeNodeData);
		TreeNodeData(treeNode);		
	}
}
/*
根据前序遍历访问的顺序，优先访问根结点，然后再分别访问左孩子和右孩子。即对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树；当访问其左子树时，再访问它的右子树。因此其处理过程如下：

对于任一结点P：

1)访问结点P，并将结点P入栈;

2)判断结点P的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点P，循环至1);若不为空，则将P的左孩子置为当前的结点P;

3)直到P为NULL并且栈为空，则遍历结束。
*/
void DLRTreeNoRecursion(CBTType * treeNode,void (*TreeNodeData)(CBTType * p)){
	stack<CBTType *> st;
	CBTType *ptr = treeNode;
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
void LDRTreeNoRecursion(CBTType * treeNode, void(*TreeNodeData)(CBTType*p)){
	stack<CBTType * > st;
	CBTType * ptr = treeNode;
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

void LRDTreeNoecursion(CBTType * treeNode,void(*TreeNodeData)(CBTType*p)){
	stack<CBTType * > st;
	CBTType * cur = NULL;
	CBTType * pre = NULL;
	st.push(treeNode);
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

int main(int argc,char *argv[]){
	CBTType * root = NULL;
	char input;
	void (*ptr)(CBTType * p);
	ptr = TreeNodeData;
	root = initTree();
	cout<<"请选择菜单添加二叉树的结点"<<endl;
	cout<<"0.退出 1.添加二叉树结点"<<endl;
	while(cin>>input){
		if(input == '0')
			break;
		else if(input == '1')
			AddTreeNode(root);
		else
			cout<<"wrong input!!!"<<endl;
	}
	cin.clear();
	cin.ignore(1024,'\n');

	cout<<"请选择菜单遍历二叉树结点"<<endl;
	cout<<"0.退出 1.先序遍历 2.中序遍历 3.后序遍历"<<endl;

	do{
		cin>>input;
		switch(input){
			case '0':
				break;
			case '1':
				cout<<"先序遍历:"<<endl;
				DLRTree(root,ptr);
				break;
			case '2':
				cout<<"中序遍历:"<<endl;
				LDRTree(root,ptr);
				break;
			case '3':
				cout<<"后序遍历:"<<endl;
				LRDTree(root,ptr);
				break;
			case '4':
				cout<<"非递归先序遍历"<<endl;
				DLRTreeNoRecursion(root,ptr);
				break;
			default:
				cout<<"invalid input"<<endl;
				break;
		}
	}while(input != '0');

	cout<<"二叉树深度:"<<TreeDepth(root);
	ClearTree(root);
	root = NULL;
	return 0;
}
