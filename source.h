#ifndef SOURCE_H
#define SOURCE_H
// #define SOURCE_H
// The header guards (#ifndef, #define, #endif) are used to prevent the header file 
// from being included multiple times in the same source code file
#define EOF             (-1)
#define ERRCHAR         (0)
#define INIT_SRC_POS    (-2)

struct source_s{
    char* buffer ; //the input text
    long bufsize ; //size of the input text
    long curpos  ; //absolute char position in source
                   //where i wil get the next character form
};

char next_char(struct source_s *src);
void unget_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);

#endif

// The first time the header file is included in a source code file, 
// the macro specified in #ifndef is not defined. 
// So, the #define directive is executed, and the header's contents are included.

// If the same header file is included again in the same source code file 
// (or in other source code files), the #ifndef check is performed again. 
// However, this time, the macro is already defined from the first inclusion. 
// Therefore, the preprocessor skips over the contents of the header file.

// As a result, the contents of the header file are included only once, 
// ensuring that there are no duplicate declarations or definitions.