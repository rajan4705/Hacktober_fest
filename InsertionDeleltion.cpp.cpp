#include<iostream>
using namespace std;

class Node{
    public:
    int block;
    Node *next;
};

Node *insertAtBeggining(Node *head, int data){
    Node *temp = new Node();
    temp->block = data;
    temp->next = head;
    head = temp;
    return head;
}

Node *insertAtEnd(Node *head, int data){
    Node *temp = new Node();
    temp->block = data;
    Node *trav = head;
    while(trav->next != nullptr){
        trav = trav->next;
    }
    trav->next = temp;
    return head;
}

Node *insertInMiddle(Node *head, int data, int position){
    position--;
    Node *temp = new Node();
    temp->block = data;
    Node *trav = head; 
    while(--position){
        trav = trav->next;
    }
    temp->next = trav->next;
    trav->next = temp;
    return head;
}

Node *deleteAtBeggining(Node *head){
    Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node *deleteAtEnd(Node *head){
    Node *temp = new Node();
    Node *trav = head;
    while(trav->next){
        temp = trav;
        trav = trav->next;
    }
    temp->next = nullptr;
    free(trav);
    return head;
}

Node *deleteInMiddle(Node *head, int position){
    position--;
    Node *temp = new Node();
    Node *trav = head;
    while(--position){
        trav = trav->next;
    }
    temp = trav;
    trav = trav->next;
    temp->next = trav->next;
    free(trav);
    return head;
}

Node *deleteLinkedList(Node *head){
    Node *trav = head;
    Node *temp = new Node();
    while(trav){
        temp = trav->next;
        free(trav);
        trav = temp;
    }
    head = nullptr;
    return head;
}

void traverse(Node *head){
    Node *trav = head;
    int len = 0;
    for(;trav != nullptr;trav = trav->next){
        cout<<trav->block<<endl;
        len++;
    }
    cout<<"length of the linked list is : "<<len<<endl;
}

int main(){
    Node *head = new Node();
    Node *second = new Node();
    Node *third = new Node();
    Node *fourth = new Node();

    head->block = 4;
    head->next = second;

    second->block = 15;
    second->next = third;

    third->block = 7;
    third->next = fourth;

    fourth->block = 40;
    fourth->next = nullptr;

    traverse(head);

    head = insertAtBeggining(head, 30);

    traverse(head);

    head = insertAtEnd(head, 80);

    traverse(head);

    head = insertInMiddle(head, 37, 3);

    traverse(head);

    head = deleteAtBeggining(head);

    traverse(head);

    head = deleteAtEnd(head);

    traverse(head);

    head = deleteInMiddle(head,3);

    traverse(head);

    head = deleteLinkedList(head);

    traverse(head);

    return 0;
}