all:
	gcc -std=c99 -O3 -pedantic -Wall -Wextra -Wredundant-decls \
		-Wmissing-prototypes -fsingle-precision-constant \
		-Wunknown-pragmas -Wconversion \
		-DMEMORY_OPTIMIZE=0 -DDEBUG=3 \
		bbase.c bio.c bvar.c bdeque.c bops.c bfunc.c bparse.c brint.c -o brint
#   gcc -std=c99 -O3 -pedantic -Wall -Wextra -Wredundant-decls \
#		-Wmissing-prototypes -Wshorten-64-to-32 -fsingle-precision-constant \
#		bmisc.c bio.c bvar.c bdeque.c bops.c bparse.c brint.c -o brint
#	gcc -std=c99 -Wall -Wextra -pedantic bmisc.c bio.c bvar.c bdeque.c bparse.c interp.c -o brint

