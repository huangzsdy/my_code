/*
* 1.createList创建单向循环链表
* 2.showLinkList 打印链表
* 3.deleteLinkList 删除链表
*/

#include <iostream>
#include <set>
using namespace std;

typedef struct ListNode
{   
    int value;
    ListNode * next;
    ListNode (int val):value(val){next = NULL;};
}ListNode,* ListNodePointer;

ListNode* createList(int len){
    cout<<"请输入单向循环链表，长度为"<<len<<"个"<<endl;
    ListNode* head = NULL;
    ListNode* temp,* now;
    int value;
    for(int i = 0;i < len;++i){
        cin>>value;
        temp = new ListNode(value);
        if(NULL == temp){
            cout<<"创建单向链表失败，节点为"<<value<<endl;
            exit(-1);
        }
        if(NULL == head){
            head = temp;
            temp->next = head;
        }
        else{
            temp->next = now->next;
            now->next = temp;
        }
        now = temp;
    }
    return head;
}

int getLinkListLength(ListNode* head){
    if(head == NULL) return 0;

    ListNode* temp = head->next;
    int length = 1;
    while(temp != head){
        length++;
        temp = temp->next;
    }
    return length;
}

void showLinkList(ListNode* head){
    if(NULL == head)
        return;
    cout<<"打印单向循环链表:";
    ListNode * temp = head;
    while(temp->next != head){
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<temp->value<<endl;
}

void deleteLinkList(ListNode * head){
    cout<<"清空链表"<<endl;
    if(NULL == head)return;
    ListNode* temp(NULL);
    int listLength = getLinkListLength(head);
    for(int i = 0;i < listLength;++i){
        temp = head;
        cout<<"删除节点:"<<temp->value<<" ";
        head = head->next;
        delete temp;
    }
    cout<<endl;
}


void deleteNode(ListNode** head,int n){
    if(NULL == (*head))return;
    ListNode* node = *head,*temp = NULL,*priorNode = *head;
    bool matched = false;
    int listLength = getLinkListLength(*head);
    cout<<"链表长度:"<<listLength<<endl;
    //先找到头指针的前一个结点
    while(priorNode->next != *head)
        priorNode = priorNode->next;

    for(int i = 0;i < listLength;++i){
        temp = node;
        node = node->next;
        if(n == temp->value){
            cout<<"匹配到节点:"<<temp->value<<"并删除节点"<<endl;
            if(temp == (*head)){
                *head = temp->next;
                if(temp == temp->next){
                    cout<<"链表全部匹配"<<n<<"，链表清空"<<endl;
                    *head = NULL;
                }
            }
            priorNode->next = temp->next;
            delete temp;
            matched = true;
        }
        else
            priorNode = temp;
    }
    cout<<endl;
    if(!matched) cout<<"未匹配到节点值:"<<n<<endl;
}


int main(int argc,char ** argv){
    int length,toDelete;
    cout<<"usage:dcList \n \
    argv[1]:length (链表总长度)\n\
    Please Input these parameters in turn\n";
    cin>>length;
    cout<<"单向链表共有"<<length<<"个元素"<<endl;
    
    ListNode * head = createList(length);
    showLinkList(head);
    
//    deleteLinkList(head);
    cout<<"请输入要删除的节点值"<<endl;
    cin>>toDelete;
    ListNode ** newHead = &head;
    deleteNode(newHead,toDelete);
    showLinkList(*newHead);
    // exit(0);
    deleteLinkList(*newHead);
    return 0;
}
