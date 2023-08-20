#ifndef NODE_H
#define NODE_H

enum node_type_e{
    NODE_COMMAND,//command wala node pehla hota hai
    NODE_VAR,//uske baad ke node var ke hote hain
};

enum val_type_e{
    
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,           /* unsigned int */
    VAL_SLLONG,         /* signed long long */
    VAL_ULLONG,         /* unsigned long long */
    VAL_FLOAT,          /* floating point */
    VAL_LDOUBLE,        /* long double */
    VAL_CHR,            /* char */
    VAL_STR,            /* str (char pointer) */
};

union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};

struct node_s{

    enum   node_type_e type;    /* type of this node */
    enum   val_type_e val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s *first_child; /* first child node */
    struct node_s *next_sibling, *prev_sibling; /*
                                                 * if this is a child node, keep
                                                 * pointers to prev/next siblings
                                                 */
};

struct node_s *new_node(enum node_type_e type);
void add_child_node(struct node_s *parent, struct node_s *child);
void free_node_tree(struct node_s *node);
void set_node_val_str(struct node_s *node, char *val);

#endif



/*
node_type_e:
enumeration defines the types of our AST nodes. Fow now, we only
need two types. The first types represenst the root nodes of a simple command's
AST, while the secoond type represents the simple command's child nodes(which
contain the command name and arguments). In the next parts of this tutorial,
we'll add mode node types to this enumeration. 

val_type_e: 
enumeration represents the types of values we can store in a given node
structure. For simple commands, we'll only use strings(VAL_STR enum type)
Later int this series, we'll use other types when we handle types of 
complex commands

symval_u: 
union represents the value we can store in a given node structure. 
Each node can have one only one type of value, such as a character string
or a numeric value. We access the node's value by referencing the appropriate
union member (sint for signed long integers, str for strings etc)

struct node_s: 
structure represents an AST node. It contains fields that tell us about 
the node's types, the type of the node's value, as well as the value itself.
If this is a root node, the children field contains the number of child nodes
and first_child points to the first child node(otherwise it will be NULL)
If this is a child node, we can traverse the AST nodes by following the 
next_sibling and prev_sibling points. 

If we want to retrieve the node's value, we need to check the val_type
field and, according to what we find there, access the appropriate member
of the val field. For simple commands, all nodes, will have the 
following attributes 

type => NODE_COMMAND (root node) or NODE_VAR (command name and arguments list)
val_type => VAL_STR
val.str => pointer to the string value
*/