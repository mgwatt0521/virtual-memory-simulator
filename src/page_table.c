/*
*       page_table.c
*       Created By Matthew Watt, 10/24/16
*/

#include "page_table.h"

// Memory management

struct table_entry *create_entry(int vir_page, int phys_mapping) {
        struct table_entry *ent = (struct table_entry *)malloc(sizeof(struct table_entry));
        ent->vir_pg = create_page(vir_page);
        ent->phys_mapping = phys_mapping;
        return ent;
}

void free_entry(struct table_entry *ent) {
        free_page(ent->vir_pg);
        free(ent);
}

page_table create_table(int size) {
        page_table tbl = (page_table)malloc(sizeof(struct table_entry) * size);
        int i;
        for(i = 0; i < size; ++i) {
                tbl[i] = create_entry(i, i);
        }
        return tbl;
}

void free_table(page_table tbl, int size) {
        int i;
        for(i = 0; i < size; ++i) {
                free_entry(tbl[i]);
        }
        free(tbl);
}

void print_table(page_table tbl, int size) {
        int i;
        for(i = 0; i < size; ++i) {
                struct table_entry *ent = tbl[i];
                print_page(ent->vir_pg);
                if(ent->phys_mapping >= 0) {
                        printf(" -> %d", ent->phys_mapping);
                }
                printf("\n");
        }
}
