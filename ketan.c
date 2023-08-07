#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    // int a = 10;
    // if(a++ > 12){
    //     printf("%d",a);
    // }
    // printf("%d\n",a);
    // char* name = "ketan";
    // printf("%lu\n",strlen(name));
    // printf("%lu\n",sizeof(&name));
    int* a = (int*)malloc(4*sizeof(int));
    for(int i=0;i<4;i++)a[i] = i;
    int *p = &a[2];
    printf("%d\n",p[-1]);
    return 0;
}