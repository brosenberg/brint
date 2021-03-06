#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bdeque.h"
#include "bbase.h"

/* returns the number of elements in the deque */
/* Use deque->size to get size. This is for testing purposes. */
int bdeque_count( struct bdeque* deque ) {
    struct d_elem *current = deque->head;
    int count = 0;
    while ( current != NULL ) {
        current = current->next;
        count++;
    }
    return count;
}

/* counts from tail to head */
/* Use deque->size to get size. This is for testing purposes. */
int bdeque_rcount( struct bdeque* deque ) {
    struct d_elem *current = deque->tail;
    int count = 0;
    while ( current != NULL ) {
        current = current->prev;
        count++;
    }
    return count;
}

/* create and initialize a new deque and return a pointer to the deque */
struct bdeque* bdeque_create( void ) {
    struct bdeque *newdeque = xmalloc(sizeof(*newdeque));
    newdeque->head = NULL;
    newdeque->tail = NULL;
    newdeque->type = BSTRING;
    newdeque->size = 0;
    return newdeque;
}

/* duplicates the given deque and returns it */
/* FIXME: This segfaults */
struct bdeque* bdeque_dup( struct bdeque* deque ) {
    struct bdeque *newdeque = xmalloc(sizeof(*newdeque));
    struct d_elem *current = deque->head,
                  *last = NULL,
                  *new = d_elem_new();
    /*
    *(new->var) = *(current->var);
    new->prev = last;
    last = new;
    newdeque->head=new;
    current = current->next;
    */
    while ( current != NULL ) {
        *(new->var) = *(current->var);
       // *new.var = *current.var;
        new->prev = last;
        last->next = new;
        last = new;   
        current = current->next;
    }
    newdeque->tail=last;
    /*fprintf(stderr,"Do not use bdeque_copy. It is not properly implemented yet!\n");*/
    return newdeque;
}

/* deletes a deque and all of its' elements */
void bdeque_destroy( struct bdeque* deque ) {
    struct d_elem *current = deque->head, *next;
    while ( current != NULL ) {
        next = current->next;
        d_elem_destroy( current );
        //xfree( current->var );
        //xfree( current );
        current = next;
    }
    xfree( deque );
    /* deque = NULL; */
}

/* remove all elements from the deque */
void bdeque_clear( struct bdeque* deque ) {
    struct d_elem *current = deque->head, *next;
    while ( current != NULL ) {
        next = current->next;
        xfree( current->var );
        xfree( current );
        current = next;
    }
    deque->head=NULL;
    deque->tail=NULL;
    deque->size=0;
}

/* pushes a element onto the end of the deque */
void bdeque_npush( struct bdeque* deque, struct d_elem* newelem ) {
    newelem->next = NULL;
    newelem->prev = deque->tail;
    if ( deque->tail != NULL )
        deque->tail->next = newelem;
    deque->tail = newelem;
    if ( deque->head == NULL )
        deque->head = newelem;
    (deque->size)++;
}

/* pushes a element onto the end of the deque */
void bdeque_nunshift( struct bdeque* deque, struct d_elem* newelem ) {
    newelem->next = deque->head;
    newelem->prev = NULL;
    if ( deque->head != NULL )
        deque->head->prev = newelem;
    deque->head = newelem;
    if ( deque->tail == NULL )
        deque->tail = newelem;
    (deque->size)++;
}

/* inserts a element at a given location
    If the location specified is greater than the length of the list, the element is appended to the list
    FIXME: This might not work yet
*/
void bdeque_ninsert( struct bdeque* deque, struct d_elem* newelem, unsigned int pos ) {
    struct d_elem *current = deque->head;
    unsigned int count = 0;
    while ( current->next != NULL && count != pos ) {
        current = current->next;
        count++;
    }
    newelem->prev = current;
    newelem->next = current->next;
    if ( current->next != NULL )
        current->next->prev = newelem;
    current->next = newelem;
}

/* pops a element off the end of the deque and returns it*/
struct d_elem* bdeque_npop( struct bdeque* deque ) {
    struct d_elem *retval = deque->tail;
    if ( retval != NULL ) {
        deque->tail = retval->prev;
        if ( deque->tail != NULL )
            deque->tail->next = NULL;
        else
            deque->head = NULL;
        /* Unlink from the rest of the deque */
        retval->prev = NULL;
        retval->next = NULL;
        (deque->size)--;
    }
    return retval;
}

/* shifts a element off the front of the deque and returns it*/
struct d_elem* bdeque_nshift( struct bdeque* deque ) {
    struct d_elem *retval = deque->head;
    if ( retval != NULL) {
        deque->head = retval->next;
        if ( deque->head != NULL )
            deque->head->prev = NULL;
        else
            deque->tail = NULL;
        /* Unlink from the rest of the deque */
        retval->prev = NULL;
        retval->next = NULL;
        (deque->size)--;
    }
    return retval;
}

/* pops a element off the end of the deque and discards it*/
void bdeque_npop_ad( struct bdeque* deque ) {
    if ( deque->tail != NULL ) {
        if ( deque->tail != NULL )
            deque->tail->next = NULL;
        else
            deque->head = NULL;
        (deque->size)--;
    }
    xfree(deque->tail->var);
    xfree(deque->tail);
}

/* shifts a element off the front of the deque and discards it*/
void bdeque_nshift_ad( struct bdeque* deque ) {
    if ( deque->head != NULL) {
        if ( deque->head != NULL )
            deque->head->prev = NULL;
        else
            deque->tail = NULL;
        (deque->size)--;
    }
    xfree(deque->head->var);
    xfree(deque->head);
}

/* places a value onto the end of a deque */
void bdeque_push( struct bdeque* deque, char* value ) {
    struct d_elem *newelem = d_elem_new();
    bvar_assign( newelem->var, value, BSTRING );
    bdeque_npush( deque, newelem );
}

/* places a value onto the front of a deque */
void bdeque_unshift( struct bdeque* deque, char* value ) {
    struct d_elem *newelem = d_elem_new();
    bvar_assign( newelem->var, value, BSTRING );
    bdeque_nunshift( deque, newelem );
}

/* prints all of the elements in the deque */
void bdeque_print( struct bdeque* deque ) {
    struct d_elem *current = deque->head;
    printf("{{ ");
    while ( current != NULL ) {
        printf("\"%s\" ",*current->var->value);
        current = current->next;
    }
    printf("}}\n");
}

/* prints all of the elements in the deque in reverse */
void bdeque_rprint( struct bdeque* deque ) {
    struct d_elem *current = deque->tail;
    printf("{{ ");
    while ( current != NULL ) {
        printf("\"%s\" ",*current->var->value);
        current = current->prev;
    }
    printf("}}\n");
}

/* FIXME: WRITEME 
    I'm thinking mergesort.
*/
void bdeque_sort( struct bdeque* deque ) {
    /* Zero or one elements are already sorted. */
    if ( deque->size == 0 || deque->size == 1 )
        return;
    

}

/* Create a new d_elem */
struct d_elem* d_elem_new( void ) {
    struct d_elem *newelem = xmalloc(sizeof(*newelem));
    newelem->var = bvar_new();
    newelem->next = NULL;
    newelem->prev = NULL;
    return newelem;
}

/* Destroys a d_elem, freeing all memory it owns */
void d_elem_destroy ( struct d_elem *elem ) {
    bvar_destroy( elem->var );
    xfree( elem );
}

/* Return a copy of a d_elem */
struct d_elem* d_elem_copy( struct d_elem *elem ) {
    struct d_elem *newelem = d_elem_new();
    //strncpy(*newelem->var->value,*elem->var->value,sizeof(*newelem->var->value));
    bvar_assign( newelem->var, *elem->var->value, elem->var->type );
    return newelem;
}

/* Sets the meta data of dst to be the same as the meta data of src */
void d_elem_copy_meta( struct d_elem *src, struct d_elem *dst ) {
    dst->next = src->next;
    dst->prev = src->prev;
}
