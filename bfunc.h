/*
    bfunc overview:
        In theory... 
        All bfuncs will be tracked by a container structure that holds all bfuncs.
        bfuncs must be created with the bfunc_create function so that they can be tracked.
*/
#include "bdeque.h"

struct bfunc {
    char* name;
    struct bdeque *deque; /* TODO: Decide whether this is a bdeque of bdeques or if it is going to be a variable array of bdeques. */
    struct bdeque *args;
};

struct bfunc **bfuncdb; /* Tracks all bfuncs */

/* Creates, initializes and returns a pointer to a bfunc */
/* This function will do checking to make sure that a function of the same name does not already exist */
struct bfunc *bfunc_create( char *name );

/* Adds the given bfunc to bfuncdb */
void bfuncddb_add( struct bfunc *func );
