CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic

SRCS := main.c fileio.c list.c
OBGS := main.o fileio.o list.o

build : app.exe

run : app.exe
	./app.exe in.txt out.txt

app.exe : $(OBGS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean :
	rm -f *.o
	rm -f *.exe
	rm -f out.txt
