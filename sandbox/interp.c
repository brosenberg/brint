#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 128

struct b_trans {
    char *orig;
    char *trans;
};

int trans_count = 1;
struct b_trans trans_table[ ] = {
    { "\n", " " },
};

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
    "if",
    "for",
    "do",
    "while",
    "\n",
};

/* Do this later
char* bparse_translate( char* s ) {
    int i;
    for ( i=1; i < trans_count; i++ ) {
        i++;
    }   
    
}
*/

void drop_nl(char *str) {
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
    applicable.

    FIXME: This should really use strsep or something like that.
*/
void split_ops ( char *s ) {
    unsigned int i,j,k,m, len = strlen(s);
    /*
    for ( i=0,m=i; i<strlen(s); i++ )
        for ( j=0; j<sizeof(defs_table)/sizeof(*defs_table); j++ )
            for ( k=0; i+k<strlen(s) && defs_table[j][k] == s[i+k]; k++ ) {
    */
    for ( i=0,m=i; i<len; i++ )
        for ( j=0; j<sizeof(defs_table)/sizeof(*defs_table); j++ )
            for ( k=0; i+k<strlen(s) && defs_table[j][k] == s[i+k]; k++ ) {
                if ( k == strlen(defs_table[j])-1 ) {
                    /* This is really lame */
                    if (m<i) {
                        printf("\"");
                        for (;m<i;m++)
                            if ( s[m] != ' ' && s[m] != '\t' )
                                printf("%c",s[m]);
                        printf("\",");
                    }
                    /* strsep should go in this commented section. */
                    /*
                    char *operand = s+m;
                    operand[i] = '\0';
                    printf("\"%s\",",operand);
                    */
                    printf("\"%s\",",defs_table[j]);
                    i+=k+1;
                    m=i;
                }
            }
}

int main ( void ) {
    char *file="testfile.bd";
    FILE *FH;
    size_t size = LINESIZE;
    char *s = malloc(size);
    if ( ( FH = fopen(file, "r") ) == NULL ) {
        fprintf(stderr,"Error: Can not read from file: %s\n",file);
        return 1;
    }

    while (fgets(s,size,FH) != NULL ) {
        int i;
        char *tmp;
        if ( s[strlen(s)-1] != '\n' ) {
        // FIXME: You were working here ->
        //while ( s[strlen(s)-1] != '\n' ) {
            int mult = 2;
            printf("#");
            tmp = realloc(s,size);
            fgets(tmp,size*mult,FH);
            snprintf(s,size*(++mult),"%s%s",s,tmp);
        }
        tmp = malloc(size);
        drop_nl(s);
        tmp=strtrunc(s,comment_chars);
        memset(s,0,LINESIZE);
        s=tmp;
        split_ops(s);
        printf("\n");
    }
    fclose(FH);
    return 0;
}

