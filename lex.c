/*

All of the lines of the brint script being run are stored in the array bd[]. We iterate through the array one by one to interpret each line. Currently there are no control structures or functions, so we can just go from top to bottom.

*/


/*

func name... ? blex_resolve
    Need a better name.

The way this should work is that there is a recursive function that takes a d_elem and the bdeque containing that d_elem as arguments. The function will attempt to perform the operations of that bdeque starting at that d_elem. It will attempt to resolve the bdeque from right to left.

FIXME: This algorithm doesn't have a way of dealing with leading unary operators. Should work on that.

TODO: In the interest of saving memory, should probably have the function return when it encounters an operator of equal or lower precedence than the operator that caused the function to be called. In other words, if 7+4*9-2 is operated on, the function will recurse using 4*9-2 as the new input. 4*9-2 will resolve to 36-2 in one step, then the function will notice that - is of the same precedence as + and return 36 and tell the the prior function that the righthand value is now 36 and that the next operator-operand pair is -2

Bad pseudo code
    rh = right hand

1:  is my rh operation of higher precedence than my rh neighbor's rh operation?
        Perform my rh operation on myself and my rh neighbor.
        Do I still have a rh neighbor?
            goto 1:
        else
            return retval d_elem
    else
        rh_neighbor = blex_resolve ( rh_neighbor, parent bdeque );
        goto 1:

*/

for ( i=0; i<bd_sz; i++ ) { // bd_sz is the number of deques in bd[]
    struct bdeque *in_deque = bd[i];
                  *out_deque = bdeque_create(); // This is where we are going to be stuffing whatever is left over from the interpreted in_deque. Though for the current state of this code, all that should be is some number.
    struct d_elem *in_node = in_deque->head;
    bdeque_npush( outdeque, d_elem_copy(in_node) ); // We want to hold onto the first node for our operations. We know this ndoe is not going to be NULL, because deques containing only NULLs should have been discarded by this point.
    while ( in_node != NULL ) {
        int isop = is_op(*node->var->value); // Figure out if the node we are currently looking at 
        if ( isop != -1 ) {
            1; // We will want to evaluate the operation, given this operator and its operand(s)
        }
    }
