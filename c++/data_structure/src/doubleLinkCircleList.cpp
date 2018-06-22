/*
* 1.createList创建双向循环链表
* 2.showLinkList 打印链表
* 3.deleteLinkList 删除链表
* 4.deleteNode 删除链表的某个节点
* 5.getLinkListLength 获得链表长度
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
    cout<<"请输入双向循环链表，长度为"<<len<<"个"<<endl;
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
            temp->next = now->next;
            temp->prior = now;
            now->next->prior = temp;
            now->next = temp;
        }
        now = temp;
    }
    return head;
}



void showLinkList(ListNode* head){
    if(NULL == head)
        return;
    cout<<"逆序打印双向循环链表:";
    ListNode * temp = head;
    while(temp->prior != head){
        cout<<temp->value<<" ";
        temp = temp->prior;
    }
    cout<<temp->value<<endl;
}

void deleteLinkList(ListNode * head){
    if(NULL == head)return;
    ListNode* temp(NULL);
    while(head != NULL){
        temp = head;
        cout<<"删除节点:"<<temp->value<<" ";
        head->prior->next = NULL;//这一句必须的。双向链表删除节点时，需要把前一个节点的next指向空，否则会访问非法内存
        head = head->next;
        delete temp;
    }
    cout<<endl;
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

void deleteNode(ListNode** head,int n){
    if(NULL == (*head))return;
    ListNode* node = *head,*temp = NULL;
    bool matched = false;
    int listLength = getLinkListLength(*head);
    cout<<"链表长度:"<<listLength<<endl;
    for(int i = 0;i < listLength;++i){
        temp = node;
        node = node->next;
        if(n == temp->value){
            cout<<"匹配到节点:"<<temp->value<<"并删除节点"<<endl;
            if(temp == (*head)){
                *head = temp->next;
                if(temp == temp->next){//对于循环链表，如果全部删光，需要手动将*head = NULL
                    cout<<"链表全部匹配"<<n<<"，链表清空"<<endl;
                    *head = NULL;
                }
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




int main(int argc,char ** argv){
    int length,toDelete;
    cout<<"usage:dcList \n \
    argv[1]:length (链表总长度)\n\
    Please Input these parameters in turn\n";
    cin>>length;
    cout<<"双向链表共有"<<length<<"个元素"<<endl;
    
    ListNode * head = createList(length);
    showLinkList(head);
    
//    deleteLinkList(head);
    cout<<"请输入要删除的节点值"<<endl;
    cin>>toDelete;
    ListNode ** newHead = &head;
    deleteNode(newHead,toDelete);
    showLinkList(*newHead);

    deleteLinkList(*newHead);
    return 0;
}
