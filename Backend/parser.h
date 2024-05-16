//if PARSER_H is not defined then then this header file has not been included before 
//and subsequent code block should be included 
//(This is typically used as an include guard, 
// preventing the contents of the header file from 
// being included multiple times in the same translation unit, 
// which could lead to symbol redefinition errors.)
#ifndef PARSER_H
#define PARSER_H//defines the macro 

#include "scanner.h" //struct token_s
#include "source.h" //struct source_s

struct node_s *parse_simple_command(struct token_s *tok);

#endif