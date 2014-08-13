#include <string.h>
#include <stdio.h>
#include "bvar.h"
#include "bbase.h"

/*
size_t btype_sizeof(btype t) {
    size_t retval;
    switch (t) {
        case BINT: retval=sizeof(int); break;
        case BFLOAT: retval=sizeof(float); break;
        case BDOUBLE: retval=sizeof(double); break;
        case BCHAR: retval=sizeof(char); break;
        case BSTRING: retval=sizeof(char*); break;
        default: retval=sizeof(void*); 
    }
    return retval;
}
*/

void bvar_assign( struct bvar *var, char *value, btype type ) {
    if ( var->value != NULL )
        xfree(var->value);
    var->value = xmalloc(sizeof((strlen(value)+1)*sizeof(char)));
    *var->value = value;
    var->type = type;
}

/* Returns a pointer to an initialized bvar */
struct bvar *bvar_new( void ) {
    struct bvar *newbvar = xmalloc(sizeof(*newbvar));
    newbvar->value = xmalloc(sizeof(char**));
    newbvar->type = BVAR_DEFAULT_TYPE;
    return newbvar;
}

void bvar_destroy( struct bvar *var ) {
    xfree( var->value );
    xfree( var );
}

/* Returns a string version of the variable */
/*
char* bvar_tostring( struct bvar *var ) {
    char* retval = malloc(sizeof(char*));
    switch ( var->type ) {
        case BNULL:
            snprintf(retval,sizeof(retval),"\0");
            break;
        case BINT:
            snprintf(retval,sizeof(retval),"%d",var->value);
            break;
        case BFLOAT:
            snprintf(retval,sizeof(retval),"%f",var->value);
            break;
        case BDOUBLE:
            snprintf(retval,sizeof(retval),"%lf",var->value);
            break;
        case BCHAR:
            snprintf(retval,sizeof(retval),"%c",var->value);
            break;
        case BSTRING:
            snprintf(retval,sizeof(retval),"%s",var->value);
            break;
    }
    return retval;
}
*/
/* Returns as an int. Floats, doubles, chars are translated to int and strings are 0 */
//int bvar_toint( struct bvar *var );
/* Returns a float. */
//float bvar_tofloat( struct bvar *var );

