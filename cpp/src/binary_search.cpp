#include <iostream>
#include <cstring>

// 根据前序遍历和中序遍历还原回二叉树，然后后序遍历
using namespace std;

struct TreeNode{
	struct TreeNode * left;
	struct TreeNode * right;
	char elem;
};

TreeNode* BinaryTreeFromOrderings(char * inOrder,char * preOrder,char length){
	if(length <= 0)
		return NULL;
	int rootIndex = 0;
	char node_value = *preOrder;
	for(;rootIndex < length;rootIndex++){
		if(inOrder[rootIndex] == preOrder[0])
			break;
	}
	TreeNode * node = new TreeNode;
	node->elem = node_value;
	//left
	node->left = BinaryTreeFromOrderings(inOrder,preOrder+1,rootIndex);
	//right
	node->right = BinaryTreeFromOrderings(inOrder + rootIndex + 1,preOrder + rootIndex + 1,length - (rootIndex + 1));
	cout<<node->elem<<endl;
	return node;
};

void preOrderTravels(TreeNode * root){
	if(root != NULL)
		cout<<root->elem<<" ";
	if(root->left)
		preOrderTravels(root->left);
	if(root->right)
		preOrderTravels(root->right);
}

void MemoryRecovery(TreeNode * root){
	if(root == NULL)
		return;
	if(root->left)
		MemoryRecovery(root->left);
	if(root->right)
		MemoryRecovery(root->right);
	cout<<"recover "<<root->elem<<endl;
	delete root;
}

int main(int argc,char ** argv){
	char* pre = "GDAFEMHZ";
	char* in = "ADEFGHMZ";

	TreeNode * rootNode = BinaryTreeFromOrderings(in,pre,strlen(in));
	preOrderTravels(rootNode);
	cout<<endl;
	MemoryRecovery(rootNode);
	return 0;
}
