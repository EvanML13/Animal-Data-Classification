leonardEvanA1: leonardEvanA1.o leonardEvanA1Main.o
	gcc leonardEvanA1.o leonardEvanA1Main.o -o leonardEvanA1 -lm
leonardEvanA1.o: leonardEvanA1.c givenA1.h
	gcc -Wall -std=c99 -c leonardEvanA1.c -o leonardEvanA1.o
leonardEvanA1Main.o: leonardEvanA1Main.c givenA1.h
	gcc -Wall -std=c99 -c leonardEvanA1Main.c -o leonardEvanA1Main.o
clean:
	rm -f *.o leonardEvanA1