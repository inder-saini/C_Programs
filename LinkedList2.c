#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//This is another way a Linked List can be implemented which by the usage of the nodes and chaining them.
typedef struct Node Node;

struct Node{
    int data;
    Node* next;
};
Node* head = NULL;
Node* createNode();
void addNode();
Node* pop();
void printList();

int main(){
addNode(1);
addNode(3);
addNode(4);
addNode(5);
addNode(6);

pop(head);
pop(head);
pop(head);
pop(head);
pop(head);
printList(head);

}

Node* createNode(int data){
Node *x;
x = (Node*)malloc(sizeof(Node));
x->data = data;
x->next = NULL;

return x;
}

void addNode(int data){

if (head == NULL){
    head = createNode(data);
    head->next = NULL;
}
else if(head->next == NULL){
Node* temp = createNode(data);
head->next = temp;
}
else{
     Node* temp = head;
    while((temp->next) != NULL){
     temp = temp->next;
    }
    temp->next = createNode(data);
    
    }
}

Node* pop(){
    Node* node = head;
    if(node == NULL){
        printf("There is no head node;\n");
    }
    else if(node->next == NULL){
       head = NULL;
       free(node);
    }
    else if(node->next->next == NULL){
        free(node->next);
        node->next = NULL;
    }
    else if(node->next->next != NULL){
while(node->next->next != NULL){
    node = node->next;
}
free(node->next);
node->next = NULL;
}
return node;
}

void printList(Node* node){
    if(node == NULL){
printf("Linked List is empty\n");
    }
    else{
while(node != NULL){
    printf("%d -> ",node->data);
    node = node->next;
}
}
}
