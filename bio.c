#include <stdio.h>
#include <string.h>
#include "bio.h"
#include "bbase.h"
/* Gets an entire line from a filehandle, regardless of line length, safely */
/* blocksize must be >1 */
char *b_gets( FILE *FH, size_t blocksize ) {
    char *tmp,*s = xmalloc(blocksize);
    size_t b=blocksize; /* Current size in memory of s */
    unsigned int c=1; /* Count of iterations of the while loop */
    fgets(s,blocksize,FH);
    /* Until we have the whole line, grow s by blocksize and retrieve next block */
    while ( *(s+strlen(s)-1) != '\n' && !feof(FH) ) {
        tmp = xrealloc(s,b+blocksize);
        s=tmp;
        fgets(s+b-c++,blocksize,FH);
        b+=blocksize;
    }
#if MEMORY_OPTIMIZATION
    tmp = xrealloc(s,strlen(s)+1);
    s=tmp;
#endif
    return s;
}

