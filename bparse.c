#include "bparse.h"
#include "bbase.h"
#include "bdef.h"
#include "bops.h"
#include "bio.h"
#define LINESIZE 128

const char comment_chars[ ] = "#";
const char whitespace_chars[ ] = " 	";

/* List of encapsulator pairs. Left encapsulator opens the encapsulation, right closes it. */
char encap[ ] = {
    '"','"',
    '\'','\'',
};

/* List of defined operators */
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
    "print",
    //"if",
    //"for",
    //"do",
    //"while",
    //"\n",
};

/* operator as it appears in code, operation performed, number of operands, precedence level */
struct b_op defs[ ] = {
    { "+", b_ADD, 2, 4 },
    { "-", b_SUB, 2, 4 },
    { "*", b_MULT, 2, 6 },
    { "print", b_PRINT, 1, 8 },
    { ";", b_NOP, 0, 0 },
};


/*
int is_def( char *in ) {
    unsigned int i;
    int retval=0;
    for ( i=0; i < sizeof(def_table)/sizeof(*def_table); i++ ) {
        if ( strncmp( in, def_table[i], sizeof(in) ) == 0 ) {
            retval = 1;
            break;
        }
    }
    return retval;
}
*/

/* Returns the defs table element number if it exists, or -1 if not found */
int is_def( char *in ) {
    unsigned int i;
    int retval=-1;
    for ( i=0; i < sizeof(defs)/sizeof(*defs); i++ ) {
        if ( strncmp( in, defs[i].name, sizeof(in) ) == 0 ) {
            retval = i;
            break;
        }
    }
    return retval;
}

//int check_syntax( FILE *FH );

//int check_block_syntax ( struct bdeque* block );

 /* remove characters in *c from *s and returns the result */
/* String Character Remove */
char *b_strcrm( char *s, char *c ) {
    unsigned int i,j,k=0;
    size_t slen = strlen(s), clen = strlen(c);
    char *retval = xmalloc(slen+1);
    /* Check each character in s against each char of c.
        If a char in c matches one in s, go to the next char is s.
        If the char doesn't match and we just checked the last char in c, then
        there isn't a match and we append it to the return value. */
    for ( i=0; i<slen; i++ )
        for ( j=0; j<clen; j++ ) {
            if ( s[i] == c[j] )
                break;
            else if ( j==clen-1 )
                retval[k++] = s[i];
        }   
    return retval;
}


/* Reads a block of code and returns the code deque for that block */
/* FIXME: Don't use fgetc, use fgets and pop the chars off that */
/*
struct bdeque* read_code_block ( FILE *FH ) {
    struct bdeque* retval = bdeque_create();
    size_t size = 1;
    char c, 
         *string = xmalloc(sizeof(char));
    while ( !feof(FH) ) {
        char *cs = xmalloc(sizeof(*cs));
        c = fgetc(FH);
        snprintf(cs, sizeof(cs), "%c", c);
        if ( ! is_def(cs) ) {
            size++;
            char *tmp = xrealloc( string, sizeof(char)*size );
            string = tmp;
            snprintf( string, sizeof(char)*size, "%s%c",string,c);
        } else {
            char *tmp = xrealloc( string, sizeof(char) );
            size = 1;
            if ( strcmp(string,"") != 0 )
                bdeque_push(retval, string);
            bdeque_push(retval, cs);
            string = tmp;
            strncpy( string, "", sizeof(char)*size );
        }
    }
    return retval;    
}
*/

/* Reads a block of code and returns the code deque for that block */
/* FIXME: Don't use fgetc, use fgets and pop the chars off that */
/*
struct bdeque* read_code_block2 ( FILE *FH ) {
    struct bdeque* retval = bdeque_create();
    size_t size = 1;
    char c, 
         *string = xmalloc(sizeof(char)*5);
    while ( !feof(FH) ) {
        char *cs = xmalloc(sizeof(*cs));
        c = fgetc(FH);
        snprintf(cs, sizeof(cs), "%c", c);
        if ( ! is_def(cs) ) {
            size++;
            char *tmp = xrealloc( string, sizeof(char)*size );
            string = tmp;
            snprintf( string, sizeof(char)*size, "%s%c",string,c);
        } else {
            char *tmp = xrealloc( string, sizeof(char) );
            size = 1;
            if ( strcmp(string,"") != 0 )
                bdeque_push(retval, string);
            bdeque_push(retval, cs);
            string = tmp;
            strncpy( string, "", sizeof(char)*size );
        }
    }
    return retval;    
}
*/

/* Remove a trailing newline character */
void chomp(char *str) {
    if ( str[strlen(str)-1] == '\n' )
        str[strlen(str)-1] = '\0';
}

/* Finds the first occurence of a char from delim in str and truncates str to that point */
void strtrunc(char *s, const char *delim) {
    unsigned int i,j;
    for ( i=0; i<strlen(s); i++ ) 
        for ( j=0; j<strlen(delim); j++ ) 
            if ( s[i] == delim[j] ) {
                s[i] = '\0';
#if MEMORY_OPTIMIZE
                    xrealloc(s,i);
#endif
                break;
            }
}

/* Finds the first occurence of a char from delim in str and truncates str to that point */
/*
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
*/

/* For each character in s, compare it against the first character in
    defs_table. If it matches, continue checking the remaining characters
    of the defs_table element and see if there is a complete match. If 
    there is, print the matching def and the preceding operand, where 
    applicable. */
/* This really needs more comments */
/* FIXME: Rewrite to use strstr() instead of three nested for loops. */
/* FIXME: Rewrite this function since it doesn't work on all input
    Ex: A line consisting of "aaaaaaa" has a length of 11 characters and contains the BEL char */
/*
struct bdeque *b_split_ops ( char *s ) {
    struct bdeque *retval = xmalloc(sizeof(*retval));
    unsigned int i,j,k,m;
    size_t len = strlen(s), def_table_elems = sizeof(defs_table)/sizeof(*defs_table);
    for ( i=0,m=i; i<len; i++ )
        for ( j=0; j<def_table_elems; j++ )
            for ( k=0; i+k<len && defs_table[j][k] == s[i+k]; k++ )
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
    if (m<i) {
        char *tmp = xmalloc(sizeof(*tmp));
        strncpy(tmp, s+m, i-m);
        tmp=b_strcrm(tmp,WHITESPACE);
        //printf("(%c %lu %u %lu)\n",tmp[9],strlen(tmp), i-m, strlen(s+m));
        if ( strlen(tmp) > 0 )
            bdeque_push(retval,tmp);
    }
    return retval;
}
*/

/* Non-destructively reads in a string s, searches for every instance of elements of defs_table within the string. The string is broken up into elements of defs_table and non-elements and then loaded into a bdeque in the order in which they appeared in s 

NOTES: This function assumes defs_table is sorted by size, largest to smallest.
       This function also assumes s has been checked for syntax errors
*/
struct bdeque *blex ( char *s ) {
    struct bdeque *retval = bdeque_create();
    size_t def_sz = sizeof(defs_table)/sizeof(*defs_table); // Number of elements in defs_table
    unsigned int i,j,last=0;
    for ( i=0; i<strlen(s); i++ ) {
        /* Stage 1: Look for encapsulators */
        for ( j=0; j<sizeof(encap); j+=2 ) {
            if ( s[i] == encap[j] ) {
                unsigned int match = i; // Store location of open encapsulator
                char *found;
                if ( last != i ) {
                    char *prev=malloc(i-last);
                    strncpy(prev,s+last,(i-last));
                    bdeque_push(retval,prev);
                }
                /* Once an open encapsulator is found, look for the closing counterpart. Skip escape encapsulator. */
                do { i++; } while ( s[i] != encap[j+1] || ( s[i] == encap[j+1] && s[i-1] == '\\' ) );
                i++; // Need one more increment to line everything up.
                /* Copy the portion of s matched above and load it into the deque */
                found=xmalloc(i-match);
                strncpy(found,s+match,i-match);
                bdeque_push(retval,found);
                last=i;
                /* Reset this loop to start over on the new value of i */
                j=0;
            }
        }
        /* Stage 2: Look for defined operators */
        for ( j=0; j<def_sz; j++ ) {
            /* See if we have an instance from defs_table */
            if ( !strncmp(s+i,defs_table[j],strlen(defs_table[j])) ) {
                char *found=xmalloc(strlen(defs_table[j]));
                /* If the last previously matched character does not precede the first matched character, grab the characters in between and push them onto the deque as their own element */
                if ( last != i ) {
                    char *prev=malloc(i-last);
                    strncpy(prev,s+last,(i-last));
                    bdeque_push(retval,prev);
                }
                strncpy(found,s+i,strlen(defs_table[j]));
                bdeque_push(retval,found);
                i+=strlen(defs_table[j]);
                last=i;
            }
        }
    }
    if ( last != strlen(s) ) {
        char *prev=malloc(strlen(s)-last);
        strncpy(prev,s+last,(strlen(s)-last));
        bdeque_push(retval,prev);
    }
    return retval;
}


void bparse_test( FILE *FH ) {
    char *s;
    size_t bd_sz = 0, i;
    struct bdeque **bd=xmalloc(bd_sz), /* Array of bdeque pointers */
                  *deque;

    while ( !feof(FH) ) {
        /* Get a line from the file */
        s=b_gets(FH,INPUT_BLOCKSIZE);
        /* Remove comments */
        strtrunc(s,comment_chars);
        /* Remove trailing new line */
        chomp(s);
        /* Tokenize line and load into a deque */
        deque = blex(s);

        if ( bdeque_count( deque ) > 0 ) {
            /* Grow the bdeque pointer array by one and append the new deque to the end */
            struct bdeque **temp = xrealloc(bd,sizeof(*bd)*(++bd_sz));
            bd = temp;
            bd[bd_sz-1] = deque;
        }
    }
    printf("<<DEQUE PRINT>>\n");
    /* Print the bdeques */
    for (i=0; i<bd_sz; i++)
        bdeque_print(bd[i]);
    printf("<<END DEQUE PRINT>>\n");
    for (i=0; i<bd_sz; i++) {
        struct bdeque *deque = bd[i], *dupdeque = bdeque_create();
        struct d_elem *node = deque->head;
        /* Keep track of operation count. If the line isn't 'done' and we can't do operations on it, we don't want to loop on it forever */
        unsigned int ops = 0;
        while ( node != NULL ) {
            struct d_elem *retnode = NULL; // Node returned by the current operation
            int def = is_def(*node->var->value);
            if ( def != -1 ) {
                if ( defs[def].operands == 2 ) {
                    retnode = defs[def].op( node->prev, node->next ); // Perform the binary operation of the current defined operator and place the result into retnode.
                    //bdeque_npush( dupdeque, defs[def].op( node->prev, node->next ) );
                // FIXME: I don't put my return value back into the deque.
                } else if ( defs[def].operands == 1 ) {
                    //struct d_elem *retval = defs[def].op( node->next );
                    retnode = defs[def].op( node->next ); // Perform the unary operation of the current defined operator and place the result into retnode.
                    //defs[def].op( node->next );
                    //if ( retval != NULL ) 
                    //    bdeque_npush( dupdeque, retval );
                } else if ( defs[def].operands == 0 ) {
                    defs[def].op( node->next );
                } else {
                    bdeque_npush( dupdeque, d_elem_copy(node) );
                }
            } //else {
                //bdeque_npush( dupdeque, d_elem_copy(node) );
            //}
            /*
            int def = is_def(*node->var->value);
            if ( def != -1 ) {
                if ( defs[def].operands == 1 )
                    b_PRINT( defs[def].op( node->next ) );
                else if ( defs[def].operands == 2 )
                    b_PRINT( defs[def].op( node->prev, node->next ) );
            }
            */
            if ( node->next == NULL )
                break;
            //else if ( node->next->prev == node )
            if ( retnode != NULL ) {
                
            }
            node = node->next;
        }
        bdeque_print( dupdeque );

    }
}
