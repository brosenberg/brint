#pragma once
#include <stdio.h>

#ifndef MEMORY_OPTIMIZE
#define MEMORY_OPTIMIZE 0
#endif

void *xmalloc( size_t size );
void *xcalloc( size_t count, size_t size );
void xfree( void *ptr );
void *xrealloc( void *ptr, size_t size );
