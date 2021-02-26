EXEC = proj2
CC = g++
CFLAGS = -c -Wall

# $(EXEC) has the value of shell variable EXEC, which is run.
# run depends on the files main.o somefile.o
$(EXEC)	: Main.o util.o heap.o graph.o
# run is created by the command g++ -o run main.o somefile.o
	$(CC) -o $(EXEC) Main.o util.o heap.o graph.o

# main.o depends on the files main.h main.c
# main.o is created by the command g++ -c -Wall main.c
Main.o	: Main.cpp Main.h
	$(CC) $(CFLAGS) Main.cpp

util.o	: util.cpp util.h
	$(CC) $(CFLAGS) util.cpp

heap.o	: heap.cpp heap.h
	$(CC) $(CFLAGS) heap.cpp

graph.o	: graph.cpp graph.h
	$(CC) $(CFLAGS) graph.cpp

clean	:
	rm *.o