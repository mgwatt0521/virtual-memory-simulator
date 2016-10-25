/*
*       page_table.h
*       Created By Matthew Watt, 10/24/16
*
*/

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include "mem_page.h"

/*
*       Structure to represent an entry in the page table
*/
struct table_entry {
        struct mem_page *vir_pg;
        int phys_mapping;
};

/*
*       Rather than define a new struct for a page table,
*       we'll let a page_table simply be a typedef for an array of table_entry
*/
typedef struct table_entry ** page_table;

// Memory management
struct table_entry *create_entry(int, int);
void free_entry(struct table_entry *);

page_table create_table(int);
void free_table(page_table, int);

// Helpers
void print_table(page_table, int);


#endif
