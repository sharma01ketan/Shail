// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
// #include "shell.h"

// int main(int argc, char **argv)
// {
//     char *cmd;

//     do
//     {
//         print_prompt1();

//         cmd = read_cmd();

//         if(!cmd)
//         {
//             exit(EXIT_SUCCESS);
//         }

//         if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
//         {
//             free(cmd);
//             continue;
//         }

//         if(strcmp(cmd, "exit\n") == 0)
//         {
//             free(cmd);
//             break;
//         }

//         printf("%s\n", cmd);

//         free(cmd);

//     } while(1);

//     exit(EXIT_SUCCESS);
// }

// char *read_cmd(void)
// {
//     char buf[1024];
//     char *ptr = NULL;
//     char ptrlen = 0;

//     while(fgets(buf, 1024, stdin))
//     {
//         int buflen = strlen(buf);

//         if(!ptr)
//         {
//             ptr = malloc(buflen+1);
//         }
//         else
//         {
//             char *ptr2 = realloc(ptr, ptrlen+buflen+1);

//             if(ptr2)
//             {
//                 ptr = ptr2;
//             }
//             else
//             {
//                 free(ptr);
//                 ptr = NULL;
//             }
//         }

//         if(!ptr)
//         {
//             fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
//             return NULL;
//         }

//         strcpy(ptr+ptrlen, buf);

//         if(buf[buflen-1] == '\n')
//         {
//             if(buflen == 1 || buf[buflen-2] != '\\')
//             {
//                 return ptr;
//             }

//             ptr[ptrlen+buflen-2] = '\0';
//             buflen -= 2;
//             print_prompt2();
//         }

//         ptrlen += buflen;
//     }

//     return ptr;
// }


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>//this provides errno and defines a lot of values for it, print it using fprintf
#include<string.h>
#include"shell.h"

int main(int argc, char** argv){
    char *cmd;
    do{
        print_prompt1();//print the prompt
        cmd = read_cmd();//read the command
        if(!cmd){//if command can't be read, there is some error
            exit(EXIT_SUCCESS);//EXIT_SUCCESS is from stdlib.h
        }
        if(cmd[0]!='\0' || strcmp(cmd,"\n")==0){//if no com
            free(cmd);
            continue;
        }
        if(strcmp(cmd,"exit\n")==0){//if exit command is ran, terminate the shell
            free(cmd);
            break;
        }
    } while(1);
    exit(EXIT_SUCCESS);//EXIT_SUCCESS is from stdlib.h
}