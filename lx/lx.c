#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *def[] = {
    "qui",
    "mps",
    "fox",
    "jum",
    "ck",
    "q",
};

//void parse( char *s, void *arg ) {
void parse ( char *s ) {
    size_t def_sz = sizeof(def)/sizeof(*def); // Number of elements in def
    unsigned int i,j,k, last=0;
    for ( i=0; i<strlen(s); i++ ) {
        for ( j=0; j<def_sz; j++ ) {
            // Compare the two strings.
            if ( !strncmp(s+i,def[j],strlen(def[j])) ) {
                char *found=malloc(strlen(def[j])),
                     *prev;
                if ( last != i ) {
                    prev=malloc(i-last);
                    strncpy(prev,s+last,(i-last));
                    printf("%s",prev);
                }
                strncpy(found,s+i,strlen(def[j]));
                printf("%s",found);
                i+=strlen(def[j]);
                last=i;
            }
        }
    }
    if ( last != strlen(s) ) {
        char *prev =malloc(strlen(s)-last);
        strncpy(prev,s+last,(strlen(s)-last));
        printf("%s",prev);
    }
}

int main (void) {
    char *s = malloc(512);
    snprintf(s,512,"The quick brown fox jumps over the lazy dog.");
    //parse(s,(void*)def);
    parse(s);
    return 0;
}
