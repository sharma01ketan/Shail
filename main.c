#include<stdio.h>
#include<stdlib.h>
#include<errno.h>//this provides errno and defines a lot of values for it, print it using fprintf
#include<string.h>
#include"shell.h"
#include"source.h"
#include"parser.h"
#include"executor.h"
int main(int argc, char** argv){//main needs to implement the REPL loop
    char *cmd;
    initsh();
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
        struct source_s src;
        src.buffer = cmd;
        src.bufsize = strlen(cmd);
        src.curpos = INIT_SRC_POS;
        parse_and_execute(&src);
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
            //additional byte for the null terminator
        }
        else{
            char *ptr2 = realloc(ptr,ptrlen+buflen+1);//for subsequent chunks we use realloc
                                                      //because they are supposed to be in continuation of the previously
                                                      //allocated memory
            if(ptr2){
                ptr = ptr2;//if the memory was successfully allocated, then good
            } else {//otherwise we have to free the pointer 
                free(ptr);
                ptr = NULL;
            }
        }
        if(!ptr){//if the memory was not allocated properly, in the first OR subsequent events, we provide an error
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

// ptr is a pointer that points to the dynamically allocated memory where the user's input is being stored.
// ptrlen is an integer variable that keeps track of the length of the input that has already been stored in the ptr buffer.
// buf is an array that holds the most recent input read from the user.

        strcpy(ptr+ptrlen,buf);//from ptr, move ptrlen bytes ahead, and then copy the contents of buffer there
        if(buf[buflen-1] == '\n'){//if my user presses enter
            //len 1 means line character hai & last mein \ shows ki agli line bhi io hai, iske NOT check kra hamne
            //if both conditions are met means ki input itna hee tha, return kardo
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


// This function takes the Eval-Print part of our Read-Eval-Print-Loop (REPL) away from the main()function. 
// It starts by skipping any leading whitespace characters, then it parses and executes simple commands, 
// one command at a time, until the input is consumed, before it returns control to the REPL loop in the
// main() function.

int parse_and_execute(struct source_s *src){
    skip_white_spaces(src);
    struct token_s *tok = tokenize(src);
    if(tok == &eof_token){
        return 0;
    }
    while(tok &&  tok!=&eof_token){
        struct node_s *cmd = parse_simple_command(tok);
        if(!cmd){
            break;
        }
        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }
    return 1;
}