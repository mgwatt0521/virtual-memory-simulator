/*
*       main.c
*       Created by Matthew Watt, 10/20/16
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mmu.h"

// Just a test driver to test the modules at this point...
int main() {
        struct mmu *mmu = create_mmu();
        page_table tbl = mmu->tbl;
        set_default_mapping(mmu);

        print_table(tbl, VIR_PAGE_COUNT);
        printf("Accessing address 45000...\n");
        int phy = access_addr(45000, mmu);
        printf("Physical address: %d\n", phy);

        print_table(tbl, VIR_PAGE_COUNT);

        free_mmu(mmu);

        return 0;
}
