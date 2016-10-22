/*
*       Created by Matthew Watt, 10/20/16
*       mem_page.c
*/
#include "mem_page.h"

struct mem_page * create_page(int page_num) {
        struct mem_page *pg = (struct mem_page *)malloc(sizeof(struct mem_page *));
        pg->present = false;
        pg->dirty_bit = false;
        pg->vir_page_num = page_num;
        pg->phys_page_num = NOT_PRESENT; // not present
        //printf("Successfully created page.\n");
        return pg;
}

void free_page(struct mem_page *pg) {
        free(pg);
//        printf("Page freed.\n");
}

void print_page(struct mem_page *pg, bool print_phys_pg) {
        char str[10]; // " -> 00\n\0"
        sprintf(str, "%d -> ", pg->phys_page_num);
        printf("%s[vir #%d]\n", ((print_phys_pg & pg->present) ? str : ""), pg->vir_page_num);
        printf("[d-bit: %s]\n", (pg->dirty_bit ? "Set" : "Not set"));
}
/*
struct mem_page {
        bool present;
        bool dirty_bit;
        int vir_page_num;
        int phys_page_num;
};
*/
