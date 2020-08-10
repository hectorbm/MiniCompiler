#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int value;
    struct node * next;
}s_node;

s_node * addNode(int aValue, s_node * list){
    //Check for empty list
    if(list == NULL){
        s_node * head = NULL;
        head = (s_node *) malloc(sizeof(s_node));
        if(head==NULL){
            printf("Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        head->value = aValue;
        head->next = NULL;
        return head;
    }
    else{
        s_node * aux = list;
        for(;aux->next!=NULL;aux=aux->next){}
        //Create node
        s_node * aNode = NULL;
        aNode = (s_node *) malloc(sizeof(s_node));
        if(aNode==NULL){
            printf("Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        aNode->value = aValue;
        aNode->next = NULL;
        //Add to the list
        aux->next = aNode;
        return list;
    }
}

void showValues(s_node * list){
    s_node * aux = list;
    for(;aux!=NULL;aux=aux->next){
        printf("%d,",aux->value);
    }
    printf("\n");
}

// For testing purposes
int main(){

    s_node * list = NULL;
    list = addNode(5,list);
    list = addNode(4,list);
    list = addNode(3,list);
    list = addNode(2,list);
    list = addNode(1,list);
    list = addNode(4,list);

    showValues(list);

    return 0;
}
