/*
*       mmu.c
*       Created by Matthew Watt, 10/20/16
*/

#include "mmu.h"

// MMU functions

int access_addr(int addr, struct mmu *mmu) {
        int phys_address = phys_addr(addr, mmu);
        struct mem_page *pg = mmu->tbl[vir_page(addr)]->vir_pg;

        // Two possible outcomes - the page is either:
        //      1. In memory - if so, print physical mapping
        //      2. Not in memory
        // In the latter case, the page must be swapped in
        if(phys_address != INVALID) {
                // Address is mapped to memory
                return phys_address;
        } else {
                printf("Page fault. Swapping page %d for page 0...\n", vir_page(addr));
                // Swap using some algorithm - for now, just swap with page 0
                swap(pg, page_in_frame(0, mmu), mmu);
                printf("Done.\n");
                return phys_addr(addr, mmu);
        }

        // If invalid range or other error condition, access fails
        return INVALID;
}

/*
*       Params:
*               vir_addr: int representing some virtual address in the virtual address space
*       Return:
*               the mapping of the address to a page num in the vir_addr space
*/
int vir_page(int vir_addr) {
        if(vir_addr > 0 && vir_addr <= MAX_ADDR) {
                // Need to extract the top 4 bits, they represent the virtual page number
                int mask = 0xf000;
                int vir_pg = vir_addr & mask;

                // Now that we've got the top 4, shift them into the bottom 4 bits
                // to get our virtual page
                vir_pg = vir_pg >> 12;
                return vir_pg;
        }
        return INVALID;
}

/*
*       Takes a virtual page [int 0-15] and determines
*       whether or not the specified page is in memory
*       Return:
*               If vir_addr has a mapping to physical memory, the phys page number
*               Else INVALID
*/
int phys_addr(int vir_addr, struct mmu *mmu) {
        int vir_pg = vir_page(vir_addr);

        // If the virtual page is within our acceptable range [0-15]
        if(vir_pg != INVALID) {

                // We can use the index to look up the right virtual page in the table
                // Then we check to see if it has a physical mapping
                struct table_entry *ent = mmu->tbl[vir_pg];

                // If it has a mapping, we convert the virtual address into a physical one
                if(ent->phys_mapping >= 0) {
                        int phys_page = ent->phys_mapping;

                        // We need to shift the page number to the uppermost
                        // 3 bits of the 15-bit physical address
                        int mask = phys_page << 12;

                        // Then we extract the lower 12 bits of vir_addr which is the
                        // address within the page we're looking for
                        int addr_within_pg = 0x0fff & vir_addr;

                        // Finally, we OR our mask with the address within the page
                        // to combine the 2 into our mapped physical address and return it
                        return (mask | addr_within_pg);
                }
        }
        return INVALID;
}

/*
*       Swaps a page out of memory (by assigning value of INVALID)
*       and swaps another in
*       Params:
*               in - page to be swapped in
*               out - page to be swapped out
*               mmu - mmu where the swapping is to be done
*/
void swap(struct mem_page *in, struct mem_page *out, struct mmu *mmu) {
        struct table_entry *inEnt = mmu->tbl[in->vir_page_num];
        struct table_entry *outEnt = mmu->tbl[out->vir_page_num];
        inEnt->phys_mapping = outEnt->phys_mapping;
        outEnt->phys_mapping = INVALID;
}

struct mem_page *page_in_frame(int phys_frame, struct mmu *mmu) {
        if(phys_frame < 0 || phys_frame >= PHYS_PAGE_COUNT) return NULL;

        int i;
        for(i = 0; i < VIR_PAGE_COUNT; ++i) {
                struct table_entry *ent = mmu->tbl[i];
                if(ent->phys_mapping == phys_frame) {
                        return ent->vir_pg;
                }
        }
        return NULL;
}

// Memory management

struct mmu *create_mmu(void) {
        // allocate memory for struct
        struct mmu *ptr = (struct mmu *)malloc(sizeof(struct mmu));

        // create a page_table
        ptr->tbl = create_table(VIR_PAGE_COUNT);

        return ptr;
}

void free_mmu(struct mmu *ptr) {
        free_table(ptr->tbl, VIR_PAGE_COUNT);
        free(ptr);
}

// Helpers
void reset_default_mapping(struct mmu *ptr) {
        page_table tbl = ptr->tbl;
        int i;

        // The upper pages in the virtual address space are unmapped by default
        for(i = 0; i < PHYS_PAGE_COUNT; ++i) {
                struct table_entry *ent = tbl[i];
                ent->phys_mapping = i;
        }

        for(i = PHYS_PAGE_COUNT; i < VIR_PAGE_COUNT; ++i) {
                struct table_entry *ent = tbl[i];
                ent->phys_mapping = INVALID;
        }
}
