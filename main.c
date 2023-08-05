#include<stdio.h>
#include<stdlib.h>
#include<errno.h>//this provides errno and defines a lot of values for it, print it using fprintf
#include<string.h>
#include"shell.h"

int main(int argc, char** argv){//main needs to implement the REPL loop
    char *cmd;
    do{
        print_prompt1();//prints the prompt string
        cmd = read_cmd();//reads the next line of input
        if(!cmd){//if command can't be read, there is some error
            exit(EXIT_SUCCESS);//EXIT_SUCCESS is from stdlib.h
        }
        if(cmd[0]=='\0' || strcmp(cmd,"\n")==0){//if no string is input, then do nothing
            free(cmd);
            continue;
        }
        if(strcmp(cmd,"exit\n")==0){//if exit command is ran, terminate the shell
            free(cmd);
            break;
        }
        printf("%s",cmd);
        free(cmd);
    } while(1);
    exit(EXIT_SUCCESS);//EXIT_SUCCESS is from stdlib.h
}

char *read_cmd(void){
    //the input is read in 1024 byte chunks 
    char buf[1024];// this is the length of the buffer that i have
    char *ptr = NULL;//this is the ptr to the string that i have
    char ptrlen = 0;//this is the length of that string

    while(fgets(buf,1024,stdin)){//
        int buflen = strlen(buf); //so that we know the length of the input string
        
        if(!ptr){
            ptr = malloc(buflen + 1);// for the first chunk we using buflen
        }
        else{
            char *ptr2 = realloc(ptr,ptrlen+buflen+1);//for subsequent chunks we use realloc
            if(ptr2){
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }
        if(!ptr){
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }
        strcpy(ptr+ptrlen,buf);
        if(buf[buflen-1] == '\n'){
            if(buflen==1||buf[buflen-2]!='\\'){
                return ptr;
            }
            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_prompt2();
        }
        ptrlen += buflen;
    }
    return ptr;
}