#include "bparse.h"
#include "bbase.h"
#include "bdef.h"
#include "bops.h"
#include "bio.h"

const char comment_chars[ ] = "#";

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



/*
 Given the list of operators in the string array 'ops', parse string 's' looking for operators.
 For each operator found, put that operator, and its' preceding operand if applicable, into a bdeque
*/
struct bedeque *b_parse_ops( char *s, char **ops ) {
    struct bdeque *retval = xmalloc(sizeof(*retval));
    size_t ops_sz = sizeof(ops)/sizeof(*ops); // Number of elements in ops
    
    
}

/* 
    input: char *s, char **ops
    out: struct bdeque *retval

    ops is assumed to be sorted by length

    For each le*tter in s, compare to the first letter of each element of ops until there is a match, or until end of list.
    If there is a match, continue checking the subsequent letters of the ops match to the letter of s.
        If all letters in the ops match are found, then push that operator and, if applicable, the operand prepending to the operator, onto retval. Move the pointer being used to iterate through s to the character after the final character matched by the ops element.
        If not all letters are matched, return to the previous step.
    If the end of line is reached, push the last unmatched portion of line onto retval.
    Return retval
*/
