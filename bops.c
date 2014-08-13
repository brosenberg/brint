/*
    TODO: Make math operations work on floats.
*/
#include <stdio.h>
#include <string.h>
#include "bops.h"
#include "bdeque.h"
#include "bbase.h"

/*
struct b_op {
    char *name;
    struct d_elem (*op)();
};
*/

/* Adds a and b */
struct d_elem *b_ADD( struct d_elem *a, struct d_elem *b ) {
    struct d_elem *retval;
    size_t size;
    char *interim;
    if ( a == NULL || b == NULL ) {
        fprintf(stderr,"Error: Attempting to operate on NULLs in %s()!\n",__func__);
        return NULL;
    }
    retval = d_elem_new();
    /* Figure out which has more digits, a or b. Worst case, the sum a+b will be one digit longer than the bigger of the two */
    size = (strlen(*(a->var->value)) > strlen(*(b->var->value))) ?
              strlen(*(a->var->value))+1 : strlen(*(b->var->value))+1;
    interim = xmalloc(sizeof(size+2)); 
    snprintf(interim,size+1,"%lld",atoll(*(a->var->value)) + atoll(*(b->var->value)));
/* Normally this function assumes the sum of a and b will be an order of magnitude larger than a or b, whichever is larger. This is not always the case, so we can save one byte when this doesn't happen by shortening the sum. */
#if MEMORY_OPTIMIZE
    if ( strlen(interim)+1 < size+2 ) {
        xrealloc( interim, strlen(interim)+1 );
    }
#endif
    bvar_assign( retval->var, interim, BSTRING );
#if DEBUG > 2
    printf("Debug:%s + %s = %s\n",*a->var->value,*b->var->value,*retval->var->value);
#endif
    return retval;
}

/* Subtracts b from a */
struct d_elem *b_SUB( struct d_elem *a, struct d_elem *b ) {
    struct d_elem *retval;
    size_t size;
    char *interim;
    if ( a == NULL || b == NULL ) {
        fprintf(stderr,"Error: Attempting to operate on NULLs in %s()!\n",__func__);
        return NULL;
    }
    retval = d_elem_new();
    /* Figure out which has more digits, a or b. Worst case, the difference a-b will be one digit longer than the bigger of the two */
    size = (strlen(*(a->var->value)) > strlen(*(b->var->value))) ?
              strlen(*(a->var->value))+1 : strlen(*(b->var->value))+1;
    interim = xmalloc(sizeof(size+2)); 
    snprintf(interim,size+1,"%lld",atoll(*(a->var->value)) - atoll(*(b->var->value)));
/* Normally this function assumes the difference of a and b will be the same order of magnitude as a or b, whichever is larger. This is not always the case, so we can save one byte when this doesn't happen by shortening the difference. */
#if MEMORY_OPTIMIZE
    if ( strlen(interim)+1 < size+2 ) {
        xrealloc( interim, strlen(interim)+1 );
    }
#endif
    bvar_assign( retval->var, interim, BSTRING );
#if DEBUG > 2
    printf("Debug:%s - %s = %s\n",*a->var->value,*b->var->value,*retval->var->value);
#endif
    return retval;
}

/* Multiplies a and b */
struct d_elem *b_MULT( struct d_elem *a, struct d_elem *b ) {
    struct d_elem *retval;
    size_t size;
    char *interim;
    if ( a == NULL || b == NULL ) {
        fprintf(stderr,"Error: Attempting to operate on NULLs in %s()!\n",__func__);
        return NULL;
    }
    retval = d_elem_new();
    /* The worst case number of digits in the product a*b is going to be the number of digits in a + the number of digits in b */
    size = strlen(*(a->var->value)) + strlen(*(b->var->value));
    interim = xmalloc(sizeof(size+2));
    snprintf(interim,size+1,"%lld",atoll(*(a->var->value)) * atoll(*(b->var->value)));
/* Normally this function assumes the product of a and b will be an order of magnitude larger than the length of a + b. This is not always the case, so we can save one byte when this doesn't happen by shortening the product. */
#if MEMORY_OPTIMIZE
    if ( strlen(interim)+1 < size+2 ) {
        xrealloc( interim, strlen(interim)+1 );
    }
#endif
    bvar_assign( retval->var, interim, BSTRING );
#if DEBUG > 2
    printf("Debug:%s * %s = %s\n",*a->var->value,*b->var->value,*retval->var->value);
#endif
    return retval;
}

/* Prints the value of a to stdout */
void b_PRINT( struct d_elem *a ) {
    printf("PRINTING:%s\n",*a->next->var->value);
    return;
}

void b_NOP( void ) {
    return;
}

/* Bitshift a left by b */
//struct d_elem b_SHIFTL( struct d_elem a, struct d_elem b );
/* Bitshift a right by b */
//struct d_elem b_SHIFTR( struct d_elem a, struct d_elem b );
/* Greater than */
//struct d_elem b_GT( struct d_elem a, struct d_elem b );
/* Less than */
//struct d_elem b_LT( struct d_elem a, struct d_elem b );
//struct d_elem b_EQUAL( struct d_elem a, struct d_elem b );
/* Assign the value of b to a */
//struct d_elem b_ASSIGN( struct d_elem a, struct d_elem b );
