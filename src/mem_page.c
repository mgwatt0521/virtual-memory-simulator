/*
*       Created by Matthew Watt, 10/20/16
*       mem_page.c
*/
#include "mem_page.h"

struct mem_page * create_page(int page_num) {
        struct mem_page *pg = (struct mem_page *)malloc(sizeof(struct mem_page *));
        pg->dirty_bit = false;
        pg->vir_page_num = page_num;
        //printf("Successfully created page.\n");
        return pg;
}

void free_page(struct mem_page *pg) {
        free(pg);
}

void print_page(struct mem_page *pg) {
        printf("[Page: %d, Modified: %d]", pg->vir_page_num, pg->dirty_bit);
}
