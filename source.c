#include<errno.h>
#include"shell.h"
#include"source.h"

//returns last character from input
//updates the pointer
//by maipulating the source_s struct
void unget_char(struct source_s *src){
    if(src->curpos<0){
        return ;
    }
    src->curpos--;
}

//return next character
//update the souce pointer
//so the next call returns the appropriate value
//returns EOF(-1 in source.h) when last line is reached
char next_char(struct source_s *src){
    if(!src || !src->buffer){
        errno = ENODATA;
        return ERRCHAR;
    }
    char c1 = 0;
    if(src->curpos == INIT_SRC_POS){
        src->curpos = -1;
    }
    else{
        c1 = src->buffer[src->curpos];
    }
    if(++src->curpos >= src->bufsize){
        src->curpos = src->bufsize;//it has gone outside
        return EOF;
    }
    return src->buffer[src->curpos];
}


//like next_char, but does not update the source pointer
//
char peek_char(struct source_s *src){
    if(!src || !src->buffer){
        errno = ENODATA;
        return ERRCHAR;
    }
    long pos = src->curpos;

    if(pos == INIT_SRC_POS){
        pos++;
    }
    if(pos >= src->bufsize){
        return EOF;
    }
    return src->buffer[pos];
}

//skips whitespaces 
//helps when we have finished reading a token
//we want to skip delimiter whitespaces before we read next token
void skip_white_spaces(struct source_s *src){
    char c;
    if(!src || !src->buffer){
        return;
    }
    while(( c = peek_char(src)  != EOF) && (c==' '|| c=='\t') ){
        next_char(src);
    }
}