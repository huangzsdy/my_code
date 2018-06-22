#include <iostream>
#include <cstring>
using namespace std;

typedef struct {
	char key[10];
}DATA;

typedef struct Node {
	DATA data;
	struct Node * nextNode = NULL;
}CLType;

CLType * CLAddEnd(CLType * head,DATA nodeData){
	CLType * node;
	if(!(node = new CLType)){
		cerr<<"CLAddEnd new CLType error"<<endl;
		return NULL;
	}
	node->data = nodeData;
	node->nextNode = NULL;
	if(head == NULL){
		head = node;
	}
	else{
		CLType * htemp = head;
		while((htemp->nextNode)!=NULL){
			htemp = htemp->nextNode;
		}
		htemp->nextNode = node;
	}
	return head;
}

CLType * CLAddFirst(CLType * head ,DATA nodeData){
	CLType * node;
	if(!(node = new CLType)){
		cerr<<"CLAddFirst new CLType error"<<endl;
		return NULL;
	}
	node->data = nodeData;
	node->nextNode = head;
	head = node;
	return head;
}

CLType * CLFindNode(CLType * head,char *key){
	CLType * htemp = head;
	while(htemp){
		if(strcmp(htemp->data.key,key) == 0){
			return htemp;
		}
		htemp = htemp->nextNode	;
	}
	return NULL;
}

CLType * CLInsertNode(CLType * head,char * findkey,DATA nodeData){
	CLType * node = new CLType;
	if(!node){
		cerr<<"CLInsertNode new node error"<<endl;
		return NULL;
	}
	node->data = nodeData;
	node->nextNode = NULL;

	CLType	* findNode = CLFindNode(head,findkey);
	if(findNode){
		node->nextNode = findNode->nextNode;
		findNode->nextNode = node;
	}
	else{
		cerr<<"CLInsertNode find no node with key == "<<findkey<<endl;
		delete findNode	;
	}
	return head;
}

CLType* CLDeleteNode(CLType	* head , char * findkey){
	CLType *node1,*node2;
	node1 = node2 = head;
	while(node2){
		if(strcmp(node2->data.key,findkey) == 0){
			if(node2 == head){
				clog<<"CLDeleteNode findkey == head->data"<<endl;
				head = head->nextNode;
				delete node2;
				break;
			}
			else{
				node1->nextNode	= node2->nextNode;
				delete node2;
				break;
			}
		}
		else{
			node1 = node2;
			node2 = node2->nextNode;
		}
	}

	return	head;
}

int CLLength(CLType	* head){
	int count = 0;
	CLType * node = head;
	while(node){
		++count;
		node = node->nextNode;
	}
	return	count;
}

void CLAllNode(CLType * head){
	CLType * node = head;
	int i = 1;
	if(head == NULL){
		cout<<"该链表没有任何节点"<<endl;
		return;
	}
	while(node){
		cout<<"第"<<i<<"个节点的key是"<<node->data.key<<endl;
		node = node->nextNode;
		++i;
	}
}

void ReleaseCL(CLType * head){
	CLType * node = head;
	while(node->nextNode != NULL){
		CLType * toDelete = node->nextNode;
		node->nextNode = node->nextNode->nextNode;
		delete toDelete;
	}
	delete node;
}

void ReleaseCL_2(CLType * head){
	CLType * node = head;
	while(node != NULL){
		CLType * toDelete = node;
		node = node->nextNode;
		delete node;
	}
}

int main(int argc,char * argv[]){
	char input[1024];
	int inputLength; 
	CLType *node, *head = NULL;
	DATA data;

	cout<<"Pls input DATA.key"<<endl;
	while(cin>>input){
		inputLength = strlen(input);
		char key[inputLength];
		strncpy(key,input,inputLength);
		memcpy(data.key,key,inputLength);
		head = CLAddFirst(head,data);
		memset(&data,0,sizeof(data));
	}

	cout<<"end"<<endl;
	CLAllNode(head);

	cin.clear();
	cout<<"演示插入节点，输入插入位置的关键字: "<<endl;
	memset(input,0,1024);
	cin>>input;
	char findKey[strlen(input)];
	memcpy(findKey,input,strlen(input));

	memset(input,0,sizeof(input));

	cout<<"演示插入节点，输入插入的data"<<endl;
	cin>>input;
	memcpy(data.key,input,strlen(input));
	head = CLInsertNode(head,findKey,data);
	CLAllNode(head);

	memset(input,0,sizeof(input));

	cout<<"演示删除节点，输入要删除的关键字"<<endl;
	cin>>input;
	head = CLDeleteNode(head,input);
	CLAllNode(head);

	memset(input,0,sizeof(input));

	cout<<"演示查找节点，输入要查找的关键字"<<endl;
	cin>>input;
	node = CLFindNode(head,input);
	if(node){
		cout<<"找到节点:"<<node->data.key<<endl;
	}
	else
		cout<<"未找到节点:"<<input<<endl;
	CLAllNode(head);

	cout<<"释放所有节点"<<endl;
	ReleaseCL_2(head);		//释放不了?!
	// delete head;
	// cout<<(head->data.key)<<endl;
	CLAllNode(head);
	return 0;
}