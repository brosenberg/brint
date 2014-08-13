#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc( size_t size ) {
    void *retval = malloc(size);
    if ( retval == NULL ) {
        fprintf(stderr,"malloc failed!\n");
        abort();
    }
    return retval;
}

/* remove characters in *c from *s */
char *b_strcrem( char *s, char *c ) {
    int i,j,k=0;
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


int main (void) {
    char *a = "   a bcde fg\th  ij 	kl	mnopqrstuvwxyz",
         *v = " \t";
    printf("%s\n",b_strcrem(a,v));
    return 0;
}
    
