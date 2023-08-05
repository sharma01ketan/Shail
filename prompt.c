#include <stdio.h>
#include "shell.h"


//there are 5 types of prompt string: p0 p1 p2 p3 p4
//ps0 used by bash, hence not used
//ps1 to ps4 are used to communicate with the user, hence are not used 

//this prints ps1 for single line input
void print_prompt1(void){
    fprintf(stderr, "$ ");//stderr is used, because unlike stdout, it is not buffered
}

//this prints ps2 for multi line input
void print_prompt2(void){
    fprintf(stderr, "> ");//also helps in distinuishing prompt streams and stdout
}