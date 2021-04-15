#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct node{
    int value;
    struct node *next;
};

typedef struct node Node;
typedef Node *NodePtr;

void CreateList(NodePtr *head, int size);

void DeleteList(NodePtr *head);
void PrintList(NodePtr *head);

void InsertNode(NodePtr *head, int data, int position);
void DeleteNode(NodePtr *head, int data);

int GetNodePosition();
int ListIsEmpty(NodePtr *head);

int ListIsEmpty(NodePtr *head){
    return *head == NULL;
}

// Create a List with random value
void CreateList(NodePtr *head, int size){
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));

    assert(newNode != NULL);

    srand(time(NULL));
    int randomValue = rand()%100+1;

    //assign the attributes of the first node
    newNode->value = randomValue;
    newNode->next = NULL;

    //link the first node
    *head = newNode;

    //declared for traversal
    NodePtr currentNode = newNode;

    for(int i = 1; i < size; i++){
        currentNode->next = (Node*)malloc(sizeof(Node));
        currentNode = currentNode->next;

        randomValue = rand()%100+1;
        currentNode->value = randomValue;
        currentNode->next = NULL;
    }
}

void DeleteNode(NodePtr *head, int DeleteData){

    // first node is matched
    if ((*head)->value == DeleteData){
        *head = (*head)->next;
        printf("%d Deleted!\n", DeleteData);
    }
    else{
        NodePtr previousNode = (*head);
        NodePtr currentNode = (*head)->next;

        //traverse the list to find the fist DeteleData
        while(currentNode->value != DeleteData && currentNode->next != NULL){
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->value == DeleteData){
            previousNode->next = currentNode->next;
            free(currentNode);
            printf("%d Deleted!\n", DeleteData);
        }
        else{
            printf("%d not found!\n", DeleteData);
        }
    }
}

void PrintList(NodePtr *head){
    NodePtr currentNode = *head;

    assert(head != NULL);

    while(currentNode->next != NULL){
        printf("%d, ",currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");

}

void InsertNode(NodePtr *head, int data, int pos){

    NodePtr newNode = (NodePtr)malloc(sizeof(Node));

    assert(newNode != NULL);

    newNode->value = data;
    newNode->next = NULL;

    NodePtr currentNode = *head;
    NodePtr previousNode = NULL;

    int pos_now = 0;

    //traverse the list to the desired position
    while (currentNode != NULL && pos_now < pos){
        previousNode = currentNode;
        currentNode = currentNode->next;
        pos_now++;
    }

    //insert in the first position
    if (previousNode == NULL){
        newNode->next = *head;
        *head = newNode;
    }//other position
    else{
        previousNode->next = newNode;
        newNode->next = currentNode;
    }

}

int main(){

    NodePtr start = NULL;

    int size = 10;
    assert(ListIsEmpty(&start));

    CreateList(&start, size);
    PrintList(&start);

    int action = 0;
    int data = 0;
    int pos = 0;
    int continue_operation = 1;
    while(continue_operation){
        PrintList(&start);
        printf("Please Choose an Action:(1.Insert Node/ 2.Delete Node/ 3.Delete List/ 4.Exit)\n");
        scanf("%d",&action);
        switch(action){
            case 1:
                printf("Data:");
                scanf("%d", &data);
                printf("Position:");
                scanf("%d", &pos);
                InsertNode(&start, data, pos);
                break;
            case 2:
                printf("Data:");
                scanf("%d", &data);
                DeleteNode(&start, data);
                break;
            case 3:
                printf("Delete List!!\n");
                //DeleteList(&start);
                break;
            case 4:
                printf("Exit!!\n");
                continue_operation = 0;
                break;
            default:
                printf("Wrong Instruction\n");
                break;
        }
    }

    return 0;
};
