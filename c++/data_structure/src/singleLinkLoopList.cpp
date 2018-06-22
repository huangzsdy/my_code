/******
** 有环单链表
** 1.createLoopList 创建“环”，这是一个循环链表
** 2.createLinkList 创建单链表，需要先创建“环”
** 3.showLinkList 打印有环单链表
** 4.judgeRing 判断单链表是否有环
** 5.getRingLength 获得环长
** 6.getCircleStart 获得连接点位置
** 7.getListLength 获得链表总长度
*******/

#include <iostream>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

typedef struct ListNode{
	int value;
	ListNode * next;
	ListNode(int val):value(val){};
}ListNode,*ListNodePointer;



ListNode * createLoopList(){
	int value,n;
	cout<<"1.创建循环链表，并返回循环链表起始点。请输入环长度"<<endl;
	cin>>n;
	cout<<"请输入"<<n<<"个节点值"<<endl;

	cin>>value;
	ListNode * circleHead = new ListNode(value);
	if(NULL == circleHead){
		cout<<"创建循环链表失败，节点value:"<<value<<endl;
		exit(-1);
	}

	ListNode * temp = circleHead;
	temp->next = circleHead;
	for(int i = 1;i < n;++i){
		cin>>value;
		ListNode * node = new ListNode(value);
		if(NULL == node){
			cout<<"创建循环链表失败，节点value:"<<value<<endl;
			exit(-1);
		}
		temp->next = node;
		node->next = circleHead;
		temp = node;
	}

	return circleHead;
}

ListNode * createLinkList(){
	cout<<"创建单链表，需要1.先创建循环链表 2.创建甩尾"<<endl;
	ListNode * startCircle = createLoopList();
	ListNode * temp(startCircle),*head(NULL);
	cout<<"2.倒着输入甩尾部分节点"<<endl;
	int value;
	while(cin>>value){
		ListNode* node = new ListNode(value);
		node->next = temp;
		temp = node;
	}
	head = temp;
	return head;
}

void showLinkList(ListNode* head){
	if(NULL == head)
		return;
	cout<<"打印单链表"<<endl;
	set<ListNode*> nodeSet;
	while(head != NULL && nodeSet.count(head) == 0){
		nodeSet.insert(head);
		cout<<head->value<<" ";
		head = head->next;
	}
	cout<<endl;
}

bool judgeRing(ListNode* head){
	ListNode* slow(head),*fast(head);
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast)
			return true;
	}
	return false;
}

int getRingLength(ListNode* head){
	ListNode* slow(head),*fast(head);
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast){
			slow = slow->next;
			int length = 1;
			while(slow != fast){
				slow = slow->next;
				length++;
			}
			return length;
		}
	}
	return 0;
}

ListNode * getCircleStart(ListNode* head){
	ListNode* slow(head),*fast(head);
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast){
			ListNode* meet = slow;
			while(head != meet){
				head = head->next;
				meet = meet->next;
			}
			return meet;
		}
	}
	return NULL;
}

int getListLength(ListNode* head){
	if(NULL == head) return 0;
	ListNode* meetNode = getCircleStart(head);
	int extraLength = 0;
	while(meetNode != head){
		head = head->next;
		extraLength++;
	}
	int ringLength = getRingLength(head);
	return extraLength + ringLength;
}

int main(int argc,char ** argv){
	ListNode * head = createLinkList();
	showLinkList(head);
	cout<<"链表"<<(judgeRing(head)?"含有":"不含有")<<"环，环长度为"<<getRingLength(head);
	ListNode * meetNode = getCircleStart(head);
	cout<<"。环连接点值为"<<meetNode->value<<",链表总长度为"<<getListLength(head)<<endl;
	return 0;
}