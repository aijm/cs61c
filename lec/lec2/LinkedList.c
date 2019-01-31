#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char *value;
    struct Node *next;
};

typedef struct Node *List;

struct Node* NewNode(char *string){
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node->next = NULL;
    node->value = (char*)malloc(strlen(string)+1);
    strcpy(node->value,string);
    return node;
}


List list_add(List list, char *string){
    struct Node *p = list;
    if(!list){
        list = NewNode(string);
    }else{
        while(p->next){
            p = p->next;
        }
        p->next = NewNode(string);
    }

    return list;
}

void list_print(List list){
    struct Node *p = list;
    if(!p){
        printf("Empty list!\n");
    }
    while(p){
        printf("%s\n",p->value);
        p = p->next;
    }
}

void list_free(List list){
    
}
int main(){
    char str1[] = "hello";
    printf("length of str1: %d\n",strlen(str1));
    printf("size of str1: %d\n",sizeof(str1));
    char str2[] = "Ai";
    char str3[] = "Jiaming";
    List list=NULL;
    list_print(list);
    list=list_add(list,str1);
    list_print(list);
    list=list_add(list,str2);
    list_print(list);
    list=list_add(list,str3);
    list_print(list);
}

