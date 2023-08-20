#ifndef SCANNER_H
#define SCANNER_H

struct token_s{
    struct source_s *src;   //source of input (a pointer to the input) we are making tokens out of this 
    int    text_len;        //length of token text, to avoid strlen frquently 
    char   *text;           //token text, to reduce calling strlen() time and again
};
//the special EOF token, which indicates the end of input

extern struct token_s eof_token;//extern to tell the compiler that the eof_token variable is defined 
//in another source file

//receives the next token from the input 
struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);

#endif