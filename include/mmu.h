/*
*       mmu.h
*       Created by Matthew Watt, 10/20/16
*/
#ifndef MMU_H
#define MMU_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mem_page.h"

static const int VIR_PAGE_COUNT = 16;
static const int PHYS_PAGE_COUNT = 8;

struct mmu {
        struct mem_page **vir_mem;
};

/*
        Desc:
                Allocates memory for and intializes a default mmu.
                Default 16 vir pages and 8 phys page frames
        Return:
                a pointer to the newly initialized struct
*/
struct mmu *create_mmu(void);

/*
*       Desc: clean up memory
*/
void free_mmu(struct mmu*);

/*
*       Params:
*               vir_addr: int representing some virtual address
*       Return:
*               the mapping of the address to a page num in the vir_addr space
*/
int vir_page(int vir_addr);



// Helpers
struct mem_page ** make_pages(int c);
void print_state(struct mmu *);

#endif
