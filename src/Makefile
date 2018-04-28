plunge: plunge.o limit.o
	gcc -o plunge plunge.o limit.o -Wall -O2

plunge.o: plunge.c limit.h
	gcc -c plunge.c

limit.o: limit.c limit.h
	gcc -c limit.c

clean:
	rm -f *.o