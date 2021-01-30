CC := gcc
CFLAGC := -std=c99 -Wall -Werror -Wpedantic

SRCS := main.c matrix.c
OBGS := main.o matrix.o

.PHONY : clean build

build : app

app : $(OBGS)
	$(CC) $(CFLAGC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGC) -c $< -o $@

%.d : %.c
	$(CC) $(CFLAGC) -M $<

run : app
	./app in.txt out.txt

clean :
	rm -f app *.o out.txt