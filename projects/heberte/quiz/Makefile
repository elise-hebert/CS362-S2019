default: testme

testme:
	gcc -o testme -c testme.c -g -Wall -coverage -lm -fpic -std=c99

prog: testme
	./testme >> results.out
	gcov testme.c -f -b >> results.out
	cat testme.c.gcov >> results.out

clean:
	rm testme *.gcov *.gcda *.gcno *.so *.out
