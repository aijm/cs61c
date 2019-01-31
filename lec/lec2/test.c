#include <stdio.h>
#include <stdlib.h>

// char *foo(){
//     char string[32];
//     return string;
// }

struct point{
    char x;
    int y;
};

void foo(int array[],unsigned int size){
    printf("size of array:%d\n",sizeof(array));
}
void main(void){
    int ar[3];
    int *p = NULL;
    int n = 10;
    int *ptr = (int *) malloc(n*sizeof(int));
    int i =0;
    for(i=0;i<n;i++){
        ptr[i] = i;
    }
    for(i=0;i<n;i++){
        printf("%d\n",ptr[i]);
    }
    free(ptr);
    ptr = NULL; // avoid dangling pointer
    printf("%lu\n",sizeof(ar));
    printf("size of pointer: %lu\n",sizeof(p));
    
    printf("size of ar:%lu\n",sizeof(ar));
    foo(ar,3);

    printf("*ar:%u, ar:%u, &ar:%u\n",*ar,ar,&ar);


    struct point pp;
    printf("size of struct point:%lu\n",sizeof(pp));

    char str4[2];
    str4[0] = 'a';
    str4[1] = 'b';
    char *pstr = str4;
    // str4[3] = '\0';
    printf("length of str4: %d\n",strlen(str4));
    printf("length of pstr: %d\n",strlen(pstr));
    
    printf("str4:%s\n",str4);
    printf("pstr:%s\n",pstr);
}