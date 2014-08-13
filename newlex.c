#include "bdeque.h"
#include "bparse.h"

/* When merging this back into the main source, rename is_def to operator_num */
int operator_num( char *in ) {
    return is_def( in );
}

/* 

Parameters: Deque currently being parsed, the d_elem that is to be parsed from, precedence level of the calling bparse instance

Recursive function. Parses from the elem passed to it. The elem passed MUST reside in the deque passed, or bad bad things will happen. Read the d_elems in from the deque. If it's an operator, determine if the next operator in the deque has higher precedence. If it does, recurse onto that operator. If it doesn't, perform the operation. Check to see if the next operator has equal or lower precedence than the calling bparse instance. If it does, return the result of the operations performed and allow the calling bparse to continue. If it doesn't, continue parsing until the next operand is of equal or lower precedence. When calling for the initial run, set the calling precedence level as 0.

*/
struct d_elem *bparse( struct bdeque *deque, struct d_elem *elem, unsigned int prev_precede ) {
    int op_num = operator_num( d_elem->var->value );
    
}
