/*

Operator precendence levels:
 Use even levels in case sometime in the future we need to stick something in between without having to reorder everything.

 0:     ;, no ops
 2:     unary arithmetic (-), unary logical (!)
 4:     addition, subtraction, 
 6:     multiplication, division
 8:     functions, keywords
10:     parentheses and other encapsulators
*/

struct b_op {
    char *name; /* Name of operation */
    struct d_elem *(*op)(); /* Pointer to function of operator */
    unsigned int operands; /* Number of operands to pass to function */
    unsigned int precedence; /* Precedence level. Higher comes first. */
};


void b_op_error( char *error );

/* Adds a and b */
struct d_elem *b_ADD( struct d_elem *a, struct d_elem *b );
struct d_elem *b_SUB( struct d_elem *a, struct d_elem *b );
struct d_elem *b_MULT( struct d_elem *a, struct d_elem *b );
/* Bitshift a left by b */
struct d_elem b_SHIFTL( struct d_elem a, struct d_elem b );
/* Bitshift a right by b */
struct d_elem b_SHIFTR( struct d_elem a, struct d_elem b );
/* Greater than */
struct d_elem b_GT( struct d_elem a, struct d_elem b );
/* Less than */
struct d_elem b_LT( struct d_elem a, struct d_elem b );
struct d_elem b_EQUAL( struct d_elem a, struct d_elem b );
/* Assign the value of b to a */
struct d_elem b_ASSIGN( struct d_elem a, struct d_elem b );

void b_PRINT( struct d_elem *a );

void b_NOP( void );
