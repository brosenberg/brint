#include <stdlib.h>
#define btype unsigned char
#define BNULL   0
#define BINT    1
#define BFLOAT  2
#define BDOUBLE 4
#define BCHAR   8
#define BSTRING 16
#define BFUNC   32
/* Type to default to upon initialization */
#define BVAR_DEFAULT_TYPE BSTRING


struct bvar {
    char **value; 
    btype type;
};

void bvar_assign( struct bvar *var, char *value, btype type );
/* Returns a pointer to an initialized bvar */
struct bvar *bvar_new(void);

void bvar_destroy( struct bvar *var );
/* Returns as an int. Floats, doubles, chars are translated to int and strings are 0 */
int bvar_toint( struct bvar *var );
/* Returns a float. */
float bvar_tofloat( struct bvar *var );
