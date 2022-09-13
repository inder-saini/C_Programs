#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Node Node;
struct Node{
    int value;
    Node* next;
};

typedef struct LinkedList LinkedList;
struct LinkedList{
    Node* head;
    Node* last;
};

Node* createNode();
Node* searchNode();
int addNode();
LinkedList* createList();
void displayList();
void deleteNode();

int main(){
LinkedList* h1 = createList();
addNode(h1,2); //We are adding the node inside of the linked list object which is defined by h1;
addNode(h1,1);
addNode(h1,3);

deleteNode(h1);

displayList(h1);
}

Node* createNode(int data){
Node *x;
    x = (Node*)malloc(sizeof(Node));
    (x->value) = data;
     x->next =NULL;
return x;
}

int addNode(LinkedList* list, int data){// Node with the data to be added in the list
 Node* x = createNode(data);
 if(!x) return 1;

 if(!list->head){
     list->head = x;
     list->last = x;
 }
 else{
     list->last->next = x;
     list->last = x;
 }
return 0;
} 

 void displayList(LinkedList* list){
Node* nextNode;
int i ;

nextNode = list->head;
do{
    printf("%d->",nextNode->value);
}while((nextNode = nextNode->next) != NULL);
} 
Node* searchNode(LinkedList* list,int data){
    Node* nextNode;
   for(nextNode = list->head;nextNode!=NULL;nextNode = nextNode->next){ //here in the for loop. the nextNode != NULL is given because we increment the nextNode in the next statement which is 'nextNode->next'. Now, in the loop after this if nextNode == NULL, it will terminate the for loop.
       if(nextNode->value == data)
        printf("We have found the node with data: %d\n",nextNode->value);
       else printf("This node is not that we are looking for. \n");
   }
    return nextNode;
}

void deleteNode(LinkedList *list){
  
	Node *last;
  Node *sndLast;
  
  if (list->head == NULL)
    return;
  
	sndLast = list->head;
  if (sndLast->next == NULL) {
    // one element
    free(sndLast);
    list->head = NULL;
    list->last = NULL;
    return;
  }
  do {
    last = sndLast->next;
    if (last->next == NULL)
      break;
    sndLast = last;
  } while (1);
  free(last);
  sndLast->next = NULL;
  list->last = sndLast;
}
LinkedList* createList(){
    LinkedList* table = (LinkedList*)malloc(sizeof(LinkedList));
    table->head = NULL;
    table->last = NULL;
    return table;
}
