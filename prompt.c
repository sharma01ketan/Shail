#include <stdio.h>
#include "shell.h"
#include "symtab/symtab.h"

//there are 5 types of prompt string: p0 p1 p2 p3 p4
//ps0 used by bash, hence not used
//ps1 to ps4 are used to communicate with the user, hence are not used 

//this prints ps1 for single line input
void print_prompt1(void)
{   
    struct symtab_entry_s *entry = get_symtab_entry("PS1");

    if(entry && entry->val){
        fprintf(stderr, "%s", entry->val);
    }
    else
    {
        fprintf(stderr, "$ ");
    }
}

//this prints ps2 for multi line input
void print_prompt2(void)
{
    struct symtab_entry_s *entry = get_symtab_entry("PS2");

    if(entry && entry->val)
    {
        fprintf(stderr, "%s", entry->val);
    }
    else
    {
        fprintf(stderr, "> ");
    }
}