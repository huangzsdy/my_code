#include<iostream>
#include<stack>
using namespace std;
/*
 * 单向不循环链表
 */
typedef struct Node{
    Node(int nodeValue): value(nodeValue){};
    int value;
    Node * next;
}Node,*NodePointer;

void insertNode(Node* p,int value){
    Node* node = new Node(value);
    node->next = p->next;
    p->next = node;
}

void printLinkList(Node* head){
    Node * temp = head;
    while(temp!= NULL){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void deleteLinkList(Node* head){
    if(head->next != NULL)
        deleteLinkList(head->next);
    cout<<"remove node value:"<<head->value<<endl;
    delete head;    
}

//反向遍历链表(walk backwards through a single link list
//method 1 stack 
void printLinkedListReversinglyByStack(Node * head){
    stack<Node*> nodeStack;
    Node* temp = head;
    while(temp){
        nodeStack.push(temp);
        temp = temp->next;
    }
    
    while(!nodeStack.empty()){
        temp = nodeStack.top();
        cout<<temp->value<<" ";
        nodeStack.pop();
    }
}
//method 2 recursively
void printLinkedListReversinglyRecursively(Node * head){
    if(head){
        if(head->next)
            printLinkedListReversinglyRecursively(head->next);
        cout<<head->value<<" ";
    }
}

void findMidNode(Node * head){
    Node * slow = head;
    Node * fast = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    cout<<"中间节点是 "<<slow->value<<endl;
}

//找出倒数第k个节点
//1.先判断k和head是否合理
//2.temp1从head开始，temp2为temp1 + k - 1.易知，当temp2走到最后一节点时，temp1刚好是倒数第k个节点
void findKNode(Node* head,int k){
    if(k <= 0){
        cout<<"无效的k:"<<k<<endl;
        return;
    }
    if(head == NULL){
        cout<<"head 为空节点"<<endl;
        return;
    }
    cout<<"倒数第"<<k<<"个元素:";
    Node *temp1 = head;
    Node *temp2 = head;
    while(k-- > 1){
        if(temp2 == NULL||temp2->next == NULL){//需要注意!这里有个边界情况，设链表长度为length,当k = length+1时，只能循环k-2次
            cout<<"链表长度不够长"<<endl;//麻烦的主要是需要处理链表长度过短的情况
            return;
        }
        temp2 = temp2->next;
    }
    while(temp2->next != NULL){
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
   cout<<temp1->value<<endl;
}

NodePointer reverseLinkList(Node* head){
    if(head == NULL ||head->next == NULL)
        return head;
    NodePointer first(NULL),second(head),third(NULL);
    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    return first;
}

int main(int argc,char ** argv){
    cout<<"Input head node"<<endl;
    int value;
    cin>>value;
    NodePointer head = new Node(value);
    NodePointer toInsert = head;
    while(cin>>value){
        insertNode(toInsert,value);
        toInsert = toInsert->next;
    } 
    cout<<"链表为:";printLinkList(head);cout<<endl;
    cout<<"利用栈来反向遍历链表:";printLinkedListReversinglyByStack(head);cout<<endl;
    cout<<"利用递归来反向遍历链表:";printLinkedListReversinglyRecursively(head);cout<<endl;
    findMidNode(head);
    cin.clear();
    cin>>value;
    findKNode(head,value);
    NodePointer newHead = reverseLinkList(head);
    cout<<"反转链表后:";printLinkList(newHead);
    cout<<"删除链表" <<endl;
    deleteLinkList(newHead);
}
