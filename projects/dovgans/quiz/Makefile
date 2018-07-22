CFLAGS = -Wall -fpic -coverage -std=c99

testme: testme.c
	gcc -o testme -g  testme.c $(CFLAGS)

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.out
