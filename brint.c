#include "brint.h"
#include "bbase.h"
//#include "bdeque.h"
#include "bparse.h"
//#include "bio.h"

/* Tests various aspects of bdeques */
void testroutine ( void ) {
    struct bdeque *newdeque = bdeque_create();
                  //*dupdeque;
    printf("DEBUG: Loading deque...\n");
    bdeque_push( newdeque, "bar" );
    bdeque_push( newdeque, "baz" );
    bdeque_unshift( newdeque, "foo" );
    bdeque_push( newdeque, "abc" );
    bdeque_unshift( newdeque, "BEGIN" );
    bdeque_unshift( newdeque, "END" );
    bdeque_push( newdeque, "def" );
    bdeque_push( newdeque, "ghi" );
    bdeque_push( newdeque, "jkl" );
    printf("DEBUG: Printing deque forwards and backwards...\n");
    bdeque_print( newdeque );
    bdeque_rprint( newdeque );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque ));
    printf("%d\n",bdeque_rcount( newdeque ));
    printf("Deque thinks its' size is: %d\n",(int)newdeque->size);
    printf("DEBUG: Popping deque...\n");
    while ( bdeque_count( newdeque ) != 0 )
        printf("%s\n",*bdeque_npop( newdeque )->var->value);
    printf("DEBUG: Printing deque forwards and backwards...\n");
    bdeque_print( newdeque );
    bdeque_rprint( newdeque );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque )); 
    printf("%d\n",bdeque_rcount( newdeque ));
    printf("Deque thinks its' size is: %d\n",(int)newdeque->size);
    printf("DEBUG: Loading deque...\n");
    bdeque_push( newdeque, "bar" );
    bdeque_push( newdeque, "baz" );
    bdeque_unshift( newdeque, "foo" );
    bdeque_push( newdeque, "abc" );
    bdeque_unshift( newdeque, "BEGIN" );
    bdeque_unshift( newdeque, "END" );
    bdeque_push( newdeque, "def" );
    bdeque_push( newdeque, "ghi" );
    bdeque_push( newdeque, "jkl" );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque ));
    printf("%d\n",bdeque_rcount( newdeque ));
    printf("Deque thinks its' size is: %d\n",(int)newdeque->size);
    /*
    printf("DEBUG: Duplicating the deque...\n");
    dupdeque = bdeque_dup( newdeque );
    printf("DEBUG: Print dup'd deque forwards and backwards...\n");
    bdeque_print( dupdeque );
    bdeque_rprint( dupdeque );
    printf("DEBUG: Destroying dup'd deque...\n");
    bdeque_destroy( dupdeque );
    */
    printf("DEBUG: Clearing deque...\n");
    bdeque_clear( newdeque );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque ));
    printf("%d\n",bdeque_rcount( newdeque ));
    printf("Deque thinks its' size is: %d\n",(int)newdeque->size);
    

    printf("DEBUG: Loading deque...\n");
    bdeque_push( newdeque, "bar" );
    bdeque_push( newdeque, "baz" );
    bdeque_unshift( newdeque, "foo" );
    bdeque_push( newdeque, "abc" );
    bdeque_unshift( newdeque, "BEGIN" );
    bdeque_unshift( newdeque, "END" );
    bdeque_push( newdeque, "def" );
    bdeque_push( newdeque, "ghi" );
    bdeque_push( newdeque, "jkl" );
    printf("DEBUG: Printing deque forwards and backwards...\n");
    bdeque_print( newdeque );
    bdeque_rprint( newdeque );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque ));
    printf("%d\n",bdeque_rcount( newdeque ));
    printf("Deque thinks its' size is: %d\n",(int)newdeque->size);
    printf("DEBUG: Popping deque...\n");
    while ( bdeque_count( newdeque ) != 0 )
        printf("%s\n",*bdeque_npop( newdeque )->var->value);
    printf("DEBUG: Printing deque forwards and backwards...\n");
    bdeque_print( newdeque );
    bdeque_rprint( newdeque );
    printf("DEBUG: Destroying deque...\n");
    bdeque_destroy( newdeque );
    printf("DEBUG: Counting deque forwards and backwards...\n");
    printf("%d\n",bdeque_count( newdeque ));
    printf("%d\n",bdeque_rcount( newdeque ));
}
/*
void testroutine2(void) {
    struct bdeque *deque = bdeque_create();
    char *a = "-71529", *b = "63398", *c = "653", *d = "3992", *e = "1794346";
    //printf("%s + %s = ", a, b);
    bdeque_push( deque, a );
    bdeque_push( deque, b );
    bdeque_push( deque, c );
    bdeque_push( deque, d );
    bdeque_push( deque, e );
    // This should be in some sort of function
    //d = *b_ADD( bdeque_nshift(deque), bdeque_nshift(deque) );
    bdeque_nunshift( deque, b_ADD( bdeque_nshift(deque), bdeque_nshift(deque) ) );
    bdeque_nunshift( deque, b_SUB( bdeque_nshift(deque), bdeque_nshift(deque) ) );
    bdeque_nunshift( deque, b_MULT( bdeque_nshift(deque), bdeque_nshift(deque) ) );
    bdeque_nunshift( deque, b_ADD( bdeque_nshift(deque), bdeque_nshift(deque) ) );
    b_PRINT( bdeque_nshift(deque) );
    //bdeque_print( deque );
   // printf("Deque thinks its' size is: %d\n",(int)deque->size);
}
*/

void brint_initialize ( void ) {
    //bfuncdb = xmalloc( sizeof( struct bfunc ) );
}

int main ( int argc, char **argv ) {
    /*
    testroutine(); 
    testroutine2();
    */
    FILE *FH;
    if ( argc < 2 ) {
        fprintf(stderr,"Error: Please specify a source file\n");
        return 1;
    }
    if ( ! strcmp(argv[1],"-t") ) {
        testroutine();
        return 1;
    }
    if ( ( FH = fopen(argv[1], "r") ) == NULL ) {
        fprintf(stderr,"Error: Can not read from file: %s\n",argv[1]);
        return 1;
    }

    brint_initialize();
    bparse_test(FH);
    fclose(FH);

    return 0;
}
