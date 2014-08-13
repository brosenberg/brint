#include <stdio.h>
#include <string.h>
#include "bdeque.h"
//#include "bops.h"
#define WHITESPACE " \t"

/*
const char comment_chars[ ] = "#%";

char *defs_table[ ] = {
    "+",
    "-",
    "*",
    "/",
    "==",
    "=",
    ">>",
    "<<",
    ">",
    "<",
    "(",
    ")",
    "{",
    "}",
    ";",
    //"if",
    //"for",
    //"do",
    //"while",
    //"\n",
};
*/

int is_trans ( char *in );
int is_def ( char *in );

int check_syntax ( FILE *FH );
int check_block_syntax ( struct bdeque* block );

/* remove characters in *c from *s and returns the result */
char *b_strcrm( char *s, char *c );

/* Reads a block of code and returns the code deque for that block */
struct bdeque* read_code_block ( FILE *FH );
struct bdeque* read_code_block2 ( FILE *FH );

/* Remove a trailing newline character */
void chomp(char *str);

/* Finds the first occurence of a char from delim in str and truncates str to that point */
//char* strtrunc(char *str,const char *delim);
void strtrunc(char *str,const char *delim);

/* Non-destructively reads in a string s, searches for every instance of elements of defs_table within th
e string. The string is broken up into elements of defs_table and non-elements and then loaded into a bdeque in the order in which they appeared in s 

NOTES: This function assumes defs_table is sorted by size, largest to smallest.
       This function also assumes s has been checked for syntax errors
*/
struct bdeque *blex ( char *s );
void bparse_test( FILE *FH );
