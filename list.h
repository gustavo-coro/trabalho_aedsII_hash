#ifndef list_h
#define list_h

typedef struct node {
    int data;
    struct node* next;
    struct node* before;
} node;

typedef struct pointer {
    node* first;
    node* last;
    int size;
} list;

void startList (list*);
void addItem (list*, node);
void deleteItem (list*, int);
int sizeList (list*);
node* getItem (list*, int);
void updateItem (list*, int, node*);
void clearList (list*);
int isListEmpty(list*);

#endif
