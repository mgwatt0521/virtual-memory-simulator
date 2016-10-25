# A simple makefile

CC=gcc
FLAGS=-I../include
NOLINK=-c
OBJECTS=mem_page.o mmu.o page_table.o

main: $(OBJECTS) main.c
	$(CC) $(FLAGS) main.c $(OBJECTS) -o main

mem_page.o: mem_page.c
	$(CC) $(FLAGS) $(NOLINK) $<

mmu.o: mmu.c
	$(CC) $(FLAGS) $(NOLINK) $<

page_table.o: page_table.c
	$(CC) $(FLAGS) $(NOLINK) $<
clean:
	rm main $(OBJECTS)
