#include <stdio.h>
#include "bmath.h"

int main(void) {
    char *a = "9726", *b = "45",
         *c = badd(a,b);
    printf("%s+%s=",a,b);
    printf("%s\n",c);
    return 0;
}
