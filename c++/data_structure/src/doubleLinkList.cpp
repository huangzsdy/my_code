/*
* 1.createList创建双向不循环链表
* 2.showLinkList 打印链表
*/

#include <iostream>
#include <set>
using namespace std;

typedef struct ListNode
{   
    int value;
    ListNode * next;
    ListNode * prior;
    ListNode (int val):value(val){next = NULL;prior = NULL;};
}ListNode,* ListNodePointer;

ListNode* createList(int len){
    cout<<"请输入双向不循环链表，长度为"<<len<<"个"<<endl;
    ListNode* head = NULL;
    ListNode* temp,* now;
    int value;
    for(int i = 0;i < len;++i){
        cin>>value;
        temp = new ListNode(value);
        if(NULL == temp){
            cout<<"创建双向链表失败，节点为"<<value<<endl;
            exit(-1);
        }
        if(NULL == head){
            head = temp;
            temp->next = head;
            temp->prior = head;
        }
        else{
            temp->prior = now;
            now->next = temp;
        }
        now = temp;
    }
    return head;
}


void showLinkList(ListNode* head){
    if(NULL == head)
        return;
    cout<<"打印双向不循环链表:";
    ListNode * temp = head;
    while(temp != NULL){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void deleteLinkList(ListNode * head){
    if(NULL == head){
        return;
    }
    else{
        deleteLinkList(head->next);
        cout<<"删除节点:"<<head->value<<endl;
    }
        
}

void deleteNode(ListNode** head,int n){
    if(NULL == (*head))return;
    ListNode* node = *head,*temp = NULL;
    bool matched = false;
    while(node != NULL){
        temp = node;
        node = node->next;
        if(n == temp->value){
            cout<<"匹配到节点:"<<temp->value<<"并删除节点"<<endl;
            if(temp == (*head)){
                *head = temp->next;
            }
            if(temp->next != NULL)
                temp->next->prior = temp->prior;
            if(temp->prior != NULL)
                temp->prior->next = temp->next;
            delete temp;
            matched = true;
        }
    }
    cout<<endl;
    if(!matched) cout<<"未匹配到节点值:"<<n<<endl;
}

int getLinkListLength(ListNode* head){
    int length = 0;
    while(head != NULL){
        length++;
        head = head->next;
    }
    return length;
}

int main(int argc,char ** argv){
    int length,toDelete;
    cout<<"usage:dcList \n \
    argv[1]:length (链表总长度)\n\
    Please Input these parameters in turn\n";
    cin>>length;
    cout<<"双向链表共有"<<length<<"个元素"<<endl;
    
    ListNode * head = createList(length);
    showLinkList(head);
    if(getLinkListLength(head) == 0){
        cout<<"链表长度为0，退出程序"<<endl;
        exit(0);
    }
    cout<<"请输入要删除的节点值"<<endl;
    cin>>toDelete;
    ListNode ** newHead = &head;
    deleteNode(newHead,toDelete);
    showLinkList(*newHead);
    
    deleteLinkList(*newHead);
    return 0;
}
