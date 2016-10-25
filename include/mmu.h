/*
*       mmu.h
*       Created by Matthew Watt, 10/20/16
*/
#ifndef MMU_H
#define MMU_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "page_table.h"

static const int VIR_PAGE_COUNT = 16;
static const int PHYS_PAGE_COUNT = 8;
static const int MAX_ADDR = 65535; // bytes in memory are 0-indexed, pages are 4KB
static const int INVALID = 0 - MAX_ADDR;

struct mmu {
        page_table tbl;
};

// MMU functions

int access_addr(int, struct mmu *);

/*
*       Params:
*               vir_addr: int representing some virtual address
*       Return:
*               the mapping of the address to a page num in the vir_addr space
*/
int vir_page(int vir_addr);

/*
*       Takes a virtual address [int 0-65535] and returns its phys address mapping if in memory
*       Return:
*               If vir_addr has a mapping to physical memory, the phys address
*               Else INVALID
*/
int phys_addr(int vir_addr, struct mmu *);

/*
*       Swaps a page out of memory (by assigning value of INVALID)
*       and swaps another in
*       Params:
*               in - page to be swapped in
*               out - page to be swapped out
*               mmu - mmu where the swapping is to be done
*/
void swap(struct mem_page *, struct mem_page *, struct mmu *);

// Memory management

/*
        Allocates memory for and intializes a default mmu.
        Default 16 vir pages and 8 phys page frames

        Return:
                a pointer to the newly initialized struct
*/
struct mmu *create_mmu(void);

/*
*       Clean up memory
*/
void free_mmu(struct mmu*);



// Helpers

/*
*       Sets the default mapping of the mmu, namely,
*       the first 8 pages in the virtual address space
*       are mapped to physical memory
*/
void set_default_mapping(struct mmu *);

#endif
