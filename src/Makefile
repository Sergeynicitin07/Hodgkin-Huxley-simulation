all: hh_sim

hh_sim: main.o methods.o model.o struct.o
	gcc -o hh_sim main.o methods.o model.o struct.o -lm

main.o: main.c struct.h methods.h model.h
	gcc -c main.c

methods.o: methods.c methods.h struct.h
	gcc -c methods.c

model.o: model.c model.h
	gcc -c model.c

struct.o: struct.c struct.h
	gcc -c struct.c

clean:
	rm -f *.o hh_sim
