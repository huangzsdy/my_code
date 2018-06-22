/*
利用双向链表解决约瑟夫环问题（也可以使用循环链表）
问题描述：
    将n个人围成一圈开始报数，每次报到m的人出列，它的下一个
    人从1开始重新报数，直到所有玩家出列。 
解决思路，使用一个双向循环链表模拟整个游戏成员，每一个节点
代表一玩家。 
*
* 1.createDcList创建双向循环链表
* 2.Josephus 约瑟夫问题
*/

#include <iostream>
using namespace std;

typedef struct ListNode
{   
    int value;
    ListNode * next;
    ListNode * prior;
    ListNode (int val):value(val){};
}ListNode,* ListNodePointer;

ListNode* createDcList(int len){
    cout<<"请输入循环链表，长度为"<<len<<"个"<<endl;
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


// 在长度为n的双向循环链表上，从第k个人开始数数，报数为m的玩家出列
void Josephus(ListNode* head,int m,int k){
    ListNode* now(head),* temp(NULL);
    for(int i = 1;i< k;++i)
        now = now->next;
    
    while(now->next != now){
        for(int j = 1;j < m;++j)
            now = now->next;
        temp = now->prior;
        temp->next = now->next;
        now->next->prior = temp;
        cout<<"出列的玩家value为:"<<now->value<<endl;
        delete now;
        now = temp->next;
    }
    cout<<"出列的玩家value为:"<<now->value<<endl;
    delete now;
    return ;
}

void showLinkList(ListNode* head){
    if(NULL == head)
        return;
    cout<<"逆序打印双向链表:";
    ListNode* temp = head;
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

int main(int argc,char ** argv){
    int length,m,k;
    cout<<"usage:dcList \n \
    argv[1]:length (链表总长度)\n \
    argv[2]:k      (从第k个人开始计数)\n \
    argv[3]:m      (每次数到m的人出列)\n \
    Please Input these parameters in turn\n";
    cin>>length>>k>>m;
    cout<<"双向链表共有"<<length<<"个元素，从"<<k<<"开始，每次数到"<<m<<"的人出列"<<endl;
    
    ListNode * head = createDcList(length);
    showLinkList(head);
    Josephus(head,m,k);
    
    return 0;
}
