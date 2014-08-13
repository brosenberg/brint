#include "bfunc.h"
#include "bbase.h"

/* Creates, initializes and returns a pointer to a bfunc */
/* This function will do checking to make sure that a function of the same name does not already exist */
struct bfunc *bfunc_create( char *name ) {
    struct bfunc *newfunc = xmalloc( sizeof(struct bfunc) );
    newfunc->name = name;
    newfunc->deque = bdeque_create();
    newfunc->args  = bdeque_create();
    return newfunc;
}

/* Adds the given bfunc to bfuncdb */
void bfuncddb_add( struct bfunc *func ) {
    return;
}

