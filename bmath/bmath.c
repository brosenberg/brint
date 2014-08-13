#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmath.h"

char *badd(char *a, char *b) {
    char *retval, *big, *small;
    int i, s, c=0;
    size_t biglen, smalllen;
    if ( strlen(a) > strlen(b) ) {
        big = a;
        small = b;
        biglen = strlen(a);
        smalllen = strlen(b);
    } else {
        big = b;
        small = a;
        biglen = strlen(b);
        smalllen = strlen(a);
    }
    retval = malloc(biglen+2);
    memset(retval,0,biglen+2);
    for ( i=1; i<=(int)smalllen; i++ ) {
        s = (int)(big[biglen-i]) + (int)(small[smalllen-i]) - 96 + c;
        //printf("%c+%c+%d=%d\n",big[biglen-i],small[smalllen-i],c,s);
        c = s/10;
        s = s%10;
        retval[biglen-i+1] = (char) s + 48;
    }
    if ( biglen > smalllen ) {
        for ( ; i<=(int)biglen; i++ ) {
            s = big[biglen-i] + (char) c;
            c = s/10;
            s = s%10;
            retval[biglen-i+1] = s;
        }
        printf("$=%s\n",retval+1);
        if ( c )
            retval[0] = (char) c + 48;
        else
            retval = retval+1;
    }
    else if ( biglen == smalllen && c )
        retval[0] = (char) c + 48;
    else
        retval = retval+1;
    /*
    for ( i=0; i<(int)biglen; i++ )
        if ( retval[i] == '\0' )
            retval[i] = ' ';
    */
    return retval;
}
