default: prog

test:
	gcc -o testme -g testme.c -c -Wall -coverage -lm -fpic -std=c99

prog: test
	./testme &> results.out
	gcov testme.c -f -b >> results.out
	cat testme.c.gcov >> results.out
