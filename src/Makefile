all: hh_sim

hh_sim: main.o struct.o methods.o model.o great_app_test.o rubbish.o
	gcc -o hh_sim main.o struct.o methods.o model.o great_app_test.o rubbish.o -lm

main.o: main.c struct.h methods.h model.h great_app_test.h rubbish.h
	gcc -c main.c

struct.o: struct.c struct.h
	gcc -c struct.c

methods.o: methods.c methods.h struct.h
	gcc -c methods.c

model.o: model.c model.h
	gcc -c model.c

great_app_test.o: great_app_test.c great_app_test.h struct.h
	gcc -c great_app_test.c

rubbish.o: rubbish.c rubbish.h struct.h methods.h model.h great_app_test.h
	gcc -c rubbish.c

clean:
	rm -f *.o hh_sim
