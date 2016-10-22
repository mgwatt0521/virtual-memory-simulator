CC=gcc
FLAGS=-Wall -I../include
MMUSRC=mmu.c
MEMPG_SRC=mem_page.c
OBJECTS=mem_page.o mmu.o

main: $(OBJECTS)
	$(CC) $(FLAGS) main.c $(OBJECTS) -o main

mem_page: $(MEMPG_SRC)
	$(CC) $(FLAGS) -c $(MEMPG_SRC)

mmu: $(MMUSRC)
	$(CC) $(FLAGS) -c $(MMUSRC)
clean:
	rm main $(OBJECTS)
