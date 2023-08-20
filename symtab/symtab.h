#ifndef SYMTAB_H
#define SYMTAB_H

#include "../node.h"

#define MAX_SYMTAB	256

/* the type of a symbol table entry's value */
enum symbol_type_e
{
    SYM_STR ,   //used to represent shell variables
    SYM_FUNC,   //represent functions
};

/* the symbol table entry structure */
struct symtab_entry_s
{
    char     *name;                     //name of the shell variable represented by this entry
    enum      symbol_type_e val_type;   //for shell variables and shell functions
    char     *val;                      //string value (for shell variables only)
    unsigned  int flags;                //the different properties we will assign to the variables and functions
    struct    symtab_entry_s *next;     //pointer to the next symbol table entry (because tables is singly linked list)
    struct    node_s *func_body;        //for shell functions, the Abstract Syntax Tree, or AST, of the function body, 
};

/* the symbol table structure */
//The struct symtab_s structure represents a single symbol table.
//For starters we'll use one symbol table, in which we'll define all our shell variables. 
//Later on, when we discuss shell functions and begin working 
//with script files we'll need more symbol tables

// Zeroth table = Global Table -> in this we define out local variables 
// (The ones that are only accessible to the shell function, and all functions and scripts executed by it)

// Symbol Table 1 and above = Local Tables -> we'll define our local variable 
// (The ones that are only accessible to the shell function or script in which they are declared )
// By cascading symbol tables int his way, we are effectively implementing variable scoping

struct symtab_s
{
    int    level;                           //0 for local, 1 and above for others
    struct symtab_entry_s *first, *last;    //pointers to the first and last entry of the linked list
};

/* values for the flags field of struct symtab_entry_s */                       
#define FLAG_EXPORT (1 << 0) /* export entry to forked commands */

/* the symbol table stack structure */
//For cascading symbol tables as we discussed above, we need to define and implement a symbol table stack
struct symtab_stack_s
{
    int    symtab_count;                                //number of symbol tables currently in the stack                              
    struct symtab_s *symtab_list[MAX_SYMTAB];           //array of pointers, to the stack symbol table 0=global & as so on
    struct symtab_s *global_symtab, *local_symtab;      //pointers to the global and local symbol table(for ease of access)
};


struct symtab_s       *new_symtab(int level);
struct symtab_s       *symtab_stack_push(void);
struct symtab_s       *symtab_stack_pop(void);
int rem_from_symtab(struct symtab_entry_s *entry, struct symtab_s *symtab);
struct symtab_entry_s *add_to_symtab(char *symbol);
struct symtab_entry_s *do_lookup(char *str, struct symtab_s *symtable);
struct symtab_entry_s *get_symtab_entry(char *str);
struct symtab_s       *get_local_symtab(void);
struct symtab_s       *get_global_symtab(void);
struct symtab_stack_s *get_symtab_stack(void);
void init_symtab(void);
void dump_local_symtab(void);
void free_symtab(struct symtab_s *symtab);
void symtab_entry_setval(struct symtab_entry_s *entry, char *val); 

#endif