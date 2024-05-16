#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include"shell.h"
#include"scanner.h"
#include"source.h"

char *tok_buf = NULL; //current token pointer (stored in buffer)
int   tok_bufsize = 0; //no of bytes we allocate to the buffer
int   tok_bufindex = -1; //current buffer index (tells us where to 
//add the next input character in buffer)

//special token to indicate end of input 
struct token_s eof_token = {
    .text_len = 0,
};

//adds a single character to the token buffer
//if buffer is full extents it to twice the size
void add_to_buf(char c){
    tok_buf[tok_bufindex++] = c;
    if(tok_bufindex >= tok_bufsize){
        char *tmp = realloc(tok_buf,tok_bufsize*2);
        if(!tmp){
            errno = ENOMEM;
            return ;
        }
        tok_buf = tmp;
        tok_bufsize *= 2;
    }
}

//string to struct token_s
//allocates memory for the token's structure and text
//fills int hte structure's member fields
struct token_s *create_token(char *str){
    struct token_s *tok = malloc(sizeof(struct token_s));//memory allocation to token
    if(!tok){//if memory could not be allocated properly
        return NULL;
    }
    memset(tok,0,sizeof(struct token_s));//memset that 
    tok->text_len = strlen(str);//saving the length of the token in it's struct

    char *nstr = malloc(tok->text_len + 1);//the actual text that we'll save in token

    if(!nstr){
        free(tok);
        return NULL;
    }
    strcpy(nstr,str);
    tok->text = nstr;//save the text in token
    return tok;
}

//frees the memory used by a token, as well as its text
void free_token(struct token_s *tok){
    if(tok->text){
        free(tok->text);
    }
    free(tok);
}

//heart and soul of our lexical scanner
//allocating memory to our token buffer(if not already done)
//initialize our token buffer and source pointers
//next_char() to reterive the next input caharacter 
//when we reach the end of input, tokenize() returns the special eof_token
//which marks the end of input
struct token_s *tokenize(struct source_s *src){
    int endloop = 0;
    if(!src || !src-> buffer || !src-> bufsize){//input ka string hee galat hai
        errno = ENODATA;
        return &eof_token;
    }
    if(!tok_buf){//merae token exist hee nhi krta hai
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if(!tok_buf){
            errno = ENOMEM;
            return &eof_token;
        }
    }
    tok_bufindex = 0;//struct ko kind of construct kara
    tok_buf[0] = '\0';//null string bana diya maine apne token ko initially
    char nc = next_char(src);//maine next_char se string ka pehla char nikala hai

    if(nc == ERRCHAR || nc == EOF){//agar toh string hee null tha 
        return &eof_token;
    }
    do{
        switch(nc){//agar empty space mile toh kuch nhi karne ka
            case ' ':

            case '\t'://agar pehle hee tab mil giya, toh kya hee krr skta hain
            if(tok_bufindex>0){
                endloop = 1;//yeh aa gya toh matlab ABB BSS
            }
            break;

            case '\n'://this is considered as a part of the next token 
            if(tok_bufindex>0){//this is specific to the implementations of parsers
                unget_char(src);
            }
            else{
                add_to_buf(nc);//agar pehla hee yehi hai, toh mera token hee yehi hai
            }
            endloop = 1;//yeh aa gya toh matlab ABB BSS
            break;

            default: 
            add_to_buf(nc);
            break;
        }
        if(endloop){
            break;
        }
    } while( (nc=next_char(src)) != EOF );//take input till you can

    if(tok_bufindex == 0){//is i did not encounter anything at all then
        return &eof_token;
    }

    if(tok_bufindex >= tok_bufsize){//why does this not result in the loss of data?
        tok_bufindex--;//maybe because the last byte is '\n' or something like that
    }

    tok_buf[tok_bufindex] = '\0';

    struct token_s *tok = create_token(tok_buf);

    if(!tok){
        fprintf(stderr,"error: failed to alloc buffer: %s\n",strerror(errno));
        return &eof_token;
    }

    tok->src = src;
    return tok;
} 
