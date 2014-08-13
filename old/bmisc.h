#pragma once
#include <stdio.h>
/* Either optimize for memory usage or CPU usage */
#ifndef MEMORY_OPTIMIZE
 #if CPU_OPTIMIZE
  #define MEMORY_OPTIMIZE 0
 #else
  #define MEMORY_OPTIMIZE 1
 #endif
#endif

#ifndef CPU_OPTIMIZE
 #if MEMORY_OPTIMIZE
  #define CPU_OPTIMIZE 0
 #else
  #define CPU_OPTIMIZE 1
 #endif
#endif

/* If both MEMORY_OPTIMIZE and CPU_OPTIMIZE are set, default to only MEMORY_OPTIMIZE */
#if MEMORY_OPTIMIZE
 #if CPU_OPTIMIZE
  #error "Can not optimize for both CPU and Memory. Defaulting to Memory Optimization"
  #undef CPU_OPTIMIZE
  #define CPU_OPTIMIZE 0
 #endif
#endif


void *xmalloc( size_t size );
void *xcalloc( size_t count, size_t size );
void xfree( void *ptr );
void *xrealloc( void *ptr, size_t size );
