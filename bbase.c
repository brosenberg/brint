#include <stdlib.h>
#include <stdio.h>
#include "bbase.h"

void *xmalloc( size_t size ) {
    void *retval = malloc(size);
    if ( retval == NULL ) {
        fprintf(stderr,"malloc failed!\n");
        abort();
    }
    return retval;
}

void *xcalloc( size_t count, size_t size ) {
    void *retval = calloc(count,size);
    if ( retval == NULL ) {
        fprintf(stderr,"calloc failed!\n");
        abort();
    }
    return retval;
}

void *xrealloc( void *ptr, size_t size ) {
    void *retval = realloc(ptr, size);
    if ( retval == NULL ) {
        fprintf(stderr,"realloc failed!\n");
        abort();
    }
    return retval;
}

void xfree( void *ptr ) { 
    free(ptr);
    ptr=NULL;
}
