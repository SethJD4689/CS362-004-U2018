CFLAGS = -Wall -fpic -coverage -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

tester.o: dominion.o interface.o tester.h tester.c
	gcc -c tester.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o tester.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o tester.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o tester.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o tester.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o interface.o tester.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o tester.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o interface.o tester.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o tester.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o interface.o tester.o $(CFLAGS)

unittestresults: cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o interface.o tester.o

	echo "\n###--------------------------------------------------------------------------###" > unittestresults.out
	echo "###                        Coverage Results for Tests                        ###" >> unittestresults.out
	echo "###--------------------------------------------------------------------------###\n" >> unittestresults.out

	gcov dominion.o -a -b -f >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out
	echo "###                      Results for Running Card Tests                      ###" >> unittestresults.out
	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o cardtest1 cardtest1.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./cardtest1 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o cardtest2 cardtest2.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./cardtest2 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o cardtest3 cardtest3.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./cardtest3 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o cardtest4 cardtest4.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./cardtest4 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out
	echo "###                    Results for Running Function Tests                    ###" >> unittestresults.out
	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o unittest1 unittest1.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./unittest1 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o unittest2 unittest2.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./unittest2 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o unittest3 unittest3.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./unittest3 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

	gcc -o unittest4 unittest4.c dominion.o rngs.o interface.o tester.o $(CFLAGS)
	./unittest4 >> unittestresults.out

	echo "###--------------------------------------------------------------------------###" >> unittestresults.out
	echo "###                               End of File                                ###" >> unittestresults.out
	echo "###--------------------------------------------------------------------------###" >> unittestresults.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
