#include "bvar.h"
#define ELEMSIZE 512

/*
  Deque element
    Data element in a deque
*/
struct d_elem {
    struct bvar *var;
    struct d_elem *next;
    struct d_elem *prev;
};

/*
  Brint deque container
    Contains metadata about the deque
*/
struct bdeque {
    struct d_elem *head;
    struct d_elem *tail;
    btype type; /* Every d_elem in the deque will be treated as this type. See bvar.h for more info */
    size_t size; /* Number of elements in the deque */
};

/* create a new deque and returns it */
struct bdeque* bdeque_create( void );
/* duplicates the given deque and returns in */
struct bdeque* bdeque_dup( struct bdeque* deque );
/* deletes a deque and all of its' elements */
void bdeque_destroy( struct bdeque* deque);
/* remove all elements from the deque */
void bdeque_clear( struct bdeque* deque);

/* returns the number of elements in the deque */
int bdeque_count( struct bdeque* deque ); // DEPRECATED
/* returns the number of elements in the deque, but counts from tail to head */
int bdeque_rcount( struct bdeque* deque ); // DEPRECATED

    ///////////////////////
    //  d_elem functions //
    ///////////////////////

/* appends a d_elem at the end of a deque */
void bdeque_npush( struct bdeque* deque, struct d_elem* newelem );
/* appends a d_elem at the front of a deque */
void bdeque_nunshift( struct bdeque* deque, struct d_elem* newelem );
/* inserts a d_elem at a given location */
/* FIXME: This doesn't work yet. */
void bdeque_ninsert( struct bdeque* deque, struct d_elem* newelem, unsigned int pos );

/* pops a d_elem off the end of a deque and returns it*/
struct d_elem* bdeque_npop( struct bdeque* deque );
/* shifts a d_elem off the front of a deque and returns it*/
struct d_elem* bdeque_nshift( struct bdeque* deque );

/* FIXME: These 'and discard' functions need to be tested */
/* pops a d_elem off the end of a deque and discards it*/
void bdeque_npop_ad( struct bdeque* deque );
/* shifts a d_elem off the front of a deque and discards it*/
void bdeque_nshift_ad( struct bdeque* deque );


/* creates a new element and appends it to the end of a deque */
void bdeque_push( struct bdeque* deque, char* value );
/* creates a new element and appends it to the front of a deque */
void bdeque_unshift( struct bdeque* deque, char* value );

/* prints all of the elements in a deque */
void bdeque_print( struct bdeque* deque );
/* prints all of the elements in a deque in reverse order */
void bdeque_rprint( struct bdeque* deque );

void bdeque_sort( struct bdeque* deque );

/* Creates and returns a new d_elem */
struct d_elem* d_elem_new( void );

/* Return a copy of a d_elem */
struct d_elem* d_elem_copy( struct d_elem *elem );

/* Destroys a d_elem, freeing all memory it owns */
void d_elem_destroy ( struct d_elem *elem );

/* Sets the meta data of dst to be the same as the meta data of src */
void d_elem_copy_meta( struct d_elem *src, struct d_elem *dst );
