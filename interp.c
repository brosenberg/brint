#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bbase.h"
#include "bio.h"
#include "bparse.h"
#define BLOCKSIZE 20
#define WHITESPACE " \t"

struct b_trans {
    char *orig;
    char *trans;
};

struct b_operat {
    char *op; /* The operator, ex: '+' or 'while' */
};

const char comment_chars[ ] = "#";
struct b_trans trans_table[ ] = {
    { "@", "+" },
    { "%", "-" },
    { "\n", " " },
};


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

struct bdeque *build_defdeque(void) {
    struct bdeque *defdeque = xmalloc(sizeof(*defdeque));
    
    return defdeque;   
}

/* Do this later
char* bparse_translate( char* s ) {
    int i;
    for ( i=1; i < trans_count; i++ ) {
        i++;
    }   
    
}
*/

/* Remove a trailing newline character */
void chomp(char *str) {
    if ( str[strlen(str)-1] == '\n' )
        str[strlen(str)-1] = '\0';
}

char* strtrunc(char *str,const char *delim) {
    char *retval=str;
    unsigned int i,j,k=0;
    if ( str != NULL && delim != NULL ) {
        for ( i=0; i<strlen(str) && !k; i++ )
            for ( j=0; j<strlen(delim) && !k; j++ )
                if ( str[i] == delim[j] )
                    k=1;
        retval=malloc((i-k)*sizeof(char));
        strncpy(retval,str,i-k);
    }
    return retval;
}

/* Returns the length of the longest def in defs_table */
size_t defs_max_length( void ) {
    unsigned int i, retval=0;
    for ( i=0; i < sizeof(defs_table)/sizeof(*defs_table); i++ ) {
        if ( strlen(defs_table[i]) > retval )
            retval = strlen(defs_table[i]);
    }
    return retval;
}

/* For each character in s, compare it against the first character in
    defs_table. If it matches, continue checking the remaining characters
    of the defs_table element and see if there is a complete match. If 
    there is, print the matching def and the preceding operand, where 
    applicable. */
/* This really needs more comments */
/* FIXME: Rewrite to use strstr() instead of three nested for loops. */
struct bdeque *b_split_ops ( char *s ) {
    struct bdeque *retval = xmalloc(sizeof(*retval));
    unsigned int i,j,k,m;
    size_t len = strlen(s), def_table_elems = sizeof(defs_table)/sizeof(*defs_table);
    for ( i=0,m=i; i<len; i++ )
        for ( j=0; j<def_table_elems; j++ )
            for ( k=0; i+k<len && defs_table[j][k] == s[i+k]; k++ ) {
                if ( k == strlen(defs_table[j])-1 ) {
                    if (m<i) {
                        char *tmp = xmalloc(sizeof(*tmp));
                        strncpy(tmp, s+m, i-m);
                        tmp=b_strcrm(tmp,WHITESPACE);
                        if ( strlen(tmp) > 0 )
                            bdeque_push(retval,tmp);
                    }
                    bdeque_push(retval,defs_table[j]);
                    i+=k+1;
                    m=i;
                }
            }
    return retval;
}

void b_translate ( char *s ) {
    char *temp;
    int i,j;
    size_t trans_count = sizeof(trans_table)/sizeof(*trans_table);
}

int main ( int argc, char **argv ) {
    FILE *FH;
    char *s;
    if ( argc < 2 ) {
        fprintf(stderr,"Error: Please specify a source file\n");
        return 1;
    }
    if ( ( FH = fopen(argv[1], "r") ) == NULL ) {
        fprintf(stderr,"Error: Can not read from file: %s\n",argv[1]);
        return 1;
    }


    while ( !feof(FH) ) {
        struct bdeque *deque;
        /* Get a line from the file */
        s=b_gets(FH,BLOCKSIZE);
        /* Remove comments */
        s=strtrunc(s,comment_chars);
        /* Remove trailing new line */
        chomp(s);
        /* Tokenize line and load into a deque */
        deque = b_split_ops(s);
        /*bdeque_print(b_split_ops(s));*/
        if ( bdeque_count( deque ) > 0 )
            bdeque_print(deque);
    }
    fclose(FH);
    b_translate("a");
    return 0;
}

