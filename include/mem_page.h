/*
*       mem_page.h
*       Created by Matthew Watt, 10/20/16
*/

#ifndef MEM_PAGE_H
#define MEM_PAGE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static const int NOT_PRESENT = -1;

/*
        Structure to represent a memory page
*/
struct mem_page {
        bool present;
        bool dirty_bit;
        int vir_page_num;
        int phys_page_num;
};

struct mem_page * create_page(int page_num);
void print_page(struct mem_page *, bool print_phys_pg);
void free_page(struct mem_page *);

#endif
