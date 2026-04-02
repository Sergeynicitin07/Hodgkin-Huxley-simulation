all: hh_sim

hh_sim: main.o methods.o model.o struct.o great_app_test.o trash.o
	gcc -o hh_sim main.o methods.o model.o struct.o great_app_test.o trash.o -lm

main.o: main.c struct.h methods.h model.h
	gcc -c main.c

methods.o: methods.c methods.h struct.h
	gcc -c methods.c

model.o: model.c model.h
	gcc -c model.c

struct.o: struct.c struct.h
	gcc -c struct.c

great_app_test.o: great_app_test.c great_app_test.h struct.h methods.h model.h
	gcc -c great_app_test.c

trash.o: trash.c trash.h struct.h
	gcc -c trash.c

clean:
	rm -f *.o hh_sim
