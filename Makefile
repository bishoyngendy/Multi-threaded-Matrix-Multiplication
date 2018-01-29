
matMultp: main.o fileManager.o multiplier.o environment.o
	gcc main.o fileManager.o multiplier.o environment.o -pthread -o matMultp

main.o: main.c
	gcc -c main.c

multiplier.o: multiplier.o
	gcc -c multiplier.c

fileProcessing.o: fileManager.c fileManager.h
	gcc -c fileManager.c

environment.o: environment.c environment.h
	gcc -c environment.c

clean:
	rm *.o matMultp
