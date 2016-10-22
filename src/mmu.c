/*
*       mmu.c
*       Created by Matthew Watt, 10/20/16
*/

#include "mmu.h"

struct mmu *create_mmu(void) {
        // allocate memory for struct
        struct mmu *ptr = (struct mmu *)malloc(sizeof(struct mmu *));

        // create a mem_page arr of size VIR_PAGE_COUNT
        ptr->vir_mem = make_pages(VIR_PAGE_COUNT);

        // set first 8 pages to be in memory
        int i;
        for(i = 0; i < PHYS_PAGE_COUNT; ++i) {
                ptr->vir_mem[i]->present = true;
                ptr->vir_mem[i]->phys_page_num = i;
        }
        return ptr;
}

struct mem_page ** make_pages(int c) {
        struct mem_page **pages = (struct mem_page **)malloc(c * sizeof(struct mem_page *));
        int i;
        for(i = 0; i < c; ++i) {
                struct mem_page *pg = create_page(i);
                pages[i] = pg;
        }
        return pages;
}

void free_mmu(struct mmu *ptr) {
        int i;
        for(i = 0; i < VIR_PAGE_COUNT; ++i) {
                free(ptr->vir_mem[i]);
        }
        free(ptr->vir_mem);
        free(ptr);
}

int vir_page(int vir_addr) {
        int mask = 0xe000;
        int vir_pg = vir_addr & mask;
        vir_pg = vir_pg >> 13; // top 3 bits to bottom 3 spots
//        printf("vir_pg for address %d: %d\n", vir_addr, vir_pg);
        return vir_pg;
}

void print_state(struct mmu *ptr) {
        int i;
        printf("***** Virtual pages *****\n");
        for(i = 0; i < VIR_PAGE_COUNT; ++i) {
                print_page(ptr->vir_mem[i], false);
                printf("\n");
        }

        printf("***** Physical memory *****\n");
        for(i = 0; i < VIR_PAGE_COUNT; ++i) {
                if(ptr->vir_mem[i]->present) {
                        print_page(ptr->vir_mem[i], true);
                        printf("\n");
                }
        }
}

/*
struct mmu {
        struct mem_page **vir_mem;
};
*/
