#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define SIZE 10
/*
gcc -g -fsanitize=address hashTable.c
./a.out
These two lines of codes basically help us find where the SEG Fault has taken place.
*/
struct Ht_item{
    int *key;
    int *value;
};
typedef struct LinkedList Linkedlist;

struct LinkedList{
    struct Ht_item* item;
    struct LinkedList* next;
};
struct Ht{
    struct Ht_item** items; //contains an array of pointers to items
    int size;
    int count;
    Linkedlist** overflowBuckets;
};

int hash();
struct Ht_item* create_item();
struct Ht* create_table();
void display();
void ht_insert();
void deleteItem();
struct Ht_item* searchItem();
void handle_collision();
//These methods will be for the Overflow Bucket which are of Linked List type:
static Linkedlist* allocateList();
static Linkedlist** createOverflowBucket();
static Linkedlist* listInsert();
static struct Ht_item* dListItem(); //d here signifies delete.


int main(){
struct Ht* h1 = create_table(SIZE);
ht_insert(h1,1,40);
ht_insert(h1,2,99);
//display(h1);
//deleteItem(h1,1);
ht_insert(h1,21,22);
ht_insert(h1,31,33);
ht_insert(h1,41,40);
ht_insert(h1,51,20);
ht_insert(h1,61,6);
ht_insert(h1,21,7);
//deleteItem(h1,1);
display(h1);
//searchItem(h1,2);

//ht_insert(h1,21,7);
}

struct Ht_item* create_item(int key, int value){
struct Ht_item* item = (struct Ht_item*) malloc(sizeof(struct Ht_item));
item->key  = (int*)malloc(sizeof(int));
item->value = (int*)malloc(sizeof(int));
*(item->key) = key;
*(item-> value) = value;
return item;
}
int hash(int key, struct Ht* table){
    //printf("%d\n",key%SIZE);
return key%SIZE;
}

struct Ht* create_table(int size){
struct Ht* table = (struct Ht*)malloc(sizeof(struct Ht)); //creating a HashTable by dynamically giveing it the size of the Ht struct
table->size = size;
table->count = 0;
table->items = (struct Ht_item**)calloc(table->size,sizeof(struct Ht_item*));//we are making the "size" number of items of Ht_items inside of the hashtable table
for(int i = 0;i<table->size;i++){
    table->items[i] = NULL;  
}
table->overflowBuckets = createOverflowBucket(table);
return table;
}

static Linkedlist* allocateList(){
    Linkedlist* List = (Linkedlist*)malloc(sizeof(Linkedlist));
    return List;
} 

static Linkedlist** createOverflowBucket(struct Ht* table){
   //Here, we need to assign to the memory that we need  LinkedList** Buckets orelse we would get a SEG Fault as we weill be trying to access illegal memory.
   Linkedlist** Buckets = (Linkedlist**)calloc(table->size,sizeof(Linkedlist*));
    for(int i = 0;i<table->size;i++){
Buckets[i] = NULL;
    }
    return Buckets;
}

static Linkedlist* listInsert(Linkedlist* list, struct Ht_item* item){ 
    Linkedlist *temp = list;
    Linkedlist *temp2 = list;
    while(temp->next){
        temp = temp->next;
        //printf("The temp->key:%d\n",*temp->item->key);
    }
     while(temp2->next){
       if(*temp2->item->key == *item->key){
           *temp2->item->value = *item->value;
           return temp2;
       }
       temp2 = temp2->next;
       
   }
    Linkedlist * node = allocateList();
    node->item = item;
    node->next = NULL;
    temp->next = node; //Consider the temp pointer here as the head pointer of the Linked List
    //printf("The temp->next->item->key is: %d\n",*temp->next->item->key);
  
    return list;
}

static struct Ht_item* dListItem(struct Ht* table,int key){ //In here we will try to delete the last element of the list.
int index = key%SIZE;
if(table->overflowBuckets[index]){
Linkedlist* head = table->overflowBuckets[index];
if(head->next == NULL){
    free(head->item->key);
    free(head->item->value);
    free(head->item);
    free(head);
}
else if(head->next != NULL){
Linkedlist* temp2 = head;
Linkedlist* temp = temp2->next;

 do{
     temp = temp2->next;
     if(temp->next==NULL)
      break;
     temp2 = temp;
 } while(1);
 free(temp);
 temp2->next = NULL;
}
}
else{
    printf("The overflowbuckets' head does not exist\n");
}
return table->items[index];
}

void ht_insert(struct Ht* table, int key, int value){
    struct Ht_item* item = create_item(key,value);
    int index = hash(key,table);

    struct Ht_item* current = table->items[index];
    if(current == NULL){ //IF the Key does not exist
        if(table->count == table->size){
            printf("The table is full.\n");
            free(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    }
    else {
        if(*(table->items[index]->key)== key){
            table->items[index]->value = &value;
            return;
        }
        else{
            //printf("We need to handle collsion for the key:%d\n\n", key);
            handle_collision(table,index,item);
        }
    }
}

void display(struct Ht* table){
for(int i = 0;i<table->size;i++){
    if(table->items[i] != NULL){
    printf("Index:%d  Key:%d   Value:%d\n ",i,*(table->items[i]->key),*(table->items[i]->value));
    if(table->overflowBuckets[i]){
        Linkedlist* head = table->overflowBuckets[i];
        while(head){
            //printf("the table->OB exists\n");
            if(head->item->key == NULL){
                //printf("The head is null.\n");
                break;
            }else{
        printf("OB[Index]:%d  OB_Key:%d OB_Value: %d\n",i,*head->item->key,*head->item->value);
        head = head->next;
        }
        }
    }
} } }
void handle_collision(struct Ht* table, int index, struct Ht_item* item){
    Linkedlist* head = table->overflowBuckets[index];

    if(head == NULL){
        head = allocateList();
        head->item = item;
        table->overflowBuckets[index] = head;
        return;
    }
    else{
        
        table->overflowBuckets[index] = listInsert(head,item);
        return;
    }
   
}
void deleteItem(struct Ht* table,int key){
    int index = key%SIZE;
    struct Ht_item* item = table->items[index];
    Linkedlist* head = table->overflowBuckets[index];
    
    if((*(item->key)== key) && (head == NULL)){
        printf("The value to be deleted is:%d\n ",*(table->items[index]->value));
        free(table->items[index]->key);
        free(table->items[index]->value);
        table->items[index] = NULL;
    }else{
       if(head != NULL){ //If there exists the OverflowBucket
        free(table->items[index]->key);
        free(table->items[index]->value);
        table->items[index] = NULL;

        Linkedlist* node = head;
        head = head->next;
        node->next = NULL;
        table->items[index] = create_item(*node->item->key,*node->item->value);
        free(node->item->key);
        free(node->item->value);
        free(node->item);
        free(node);

        table->overflowBuckets[index] = head;
        return;
       }
       Linkedlist* curr = head;
       Linkedlist* prev = NULL;

       while(curr){
           if(*item->key == key){
               if(prev == NULL){
        free(head->item->key);
        free(head->item->value);
        free(head->item);
        free(head);  
        table->overflowBuckets[index] = NULL;
        return;
               }else{
                   prev->next = curr->next;
                   curr->next = NULL;
                   free(curr->item->key);
                   free(curr->item->value);
                   free(curr->item);
                   free(curr);
                   table->overflowBuckets[index] = head;
                   return; 
               }
           }
           curr = curr->next;
           prev = curr;
       }
    }
    
 }

struct Ht_item* searchItem(struct Ht* table, int key){
    struct Ht_item* searched_item = NULL;
for (int i = 0;i<table->size;i++){
    if(table->items[i] != NULL){
        if(*(table->items[i]->key) == key){
            printf("We have found the key, the value associated with the key, %d is %d\n ",*(table->items[i]->key),*(table->items[i]->value));
            searched_item = table->items[i];
        }
        else{
        printf("There is no such item in the hash table at index: %d\n",i);
        }
    }
}
return searched_item;
}
