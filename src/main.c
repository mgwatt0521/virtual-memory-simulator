/*
*       main.c
*       Created by Matthew Watt, 10/20/16
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "mmu.h"

bool buf_empty(void);
void clear_buf(void);
void prompt(void);
int get_addr(void);

int main() {
        struct mmu *mmu = create_mmu();
        page_table tbl = mmu->tbl;
        reset_default_mapping(mmu);

        // Main execution loop
        bool quit = false;
                char input;
                while(true) {
                        prompt();
                        input = getchar();
                        // For cleanliness and consistency, only accept input if the user enters a single char
                        if(buf_empty()) {
                                int addr = 0;
                                switch(input) {
                                case 'a':
                                        addr = get_addr();
                                        int phys_addr = access_addr(addr, mmu);
                                        printf("Virtual address %d maps to physical address %d\n", addr, phys_addr);
                                        break;
                                case 'b':
                                        printf("Current page table:\n");
                                        print_table(tbl, VIR_PAGE_COUNT);
                                        break;
                                case 'c':
                                        printf("Resetting default page mapping...\n");
                                        reset_default_mapping(mmu);
                                        printf("Done.");
                                        break;
                                case 'd':
                                        quit = true;
                                        break;
                                default:
                                        // Unrecognized input
                                        // Remind the user yet again of their incompetence
                                        printf("Unrecognized choice.\n");
                                        break;
                                }
                        } else {
                        // We've not yet received valid input
                        // Clear stdin and try again
                                printf("Invalid. Try again\n");
                                clear_buf();
                        }
                        if(quit) break;
                }


        free_mmu(mmu);

        return 0;
}

int get_addr(void) {
        char in;
        int addr = 0;
        bool fail = false;
        printf("Please enter an address [0-65535]: ");
        while(true) {
                in = getchar();
                while(in != '\n') {
                        if(!isdigit(in)) {
                                fail = true;
                                break;
                        } else {
                                // Digit...we're good to continue on
                                char str[2] = {in, '\0'};
                                addr = (addr * 10) + atoi(str);
                                in = getchar();
                        }
                }
                if(fail) {
                        printf("Invalid address. Try again: ");
                        if(!buf_empty()) clear_buf();
                        continue;
                } else {
                        if(addr >= 0 && addr < MAX_ADDR) {
                                return addr;
                        } else {
                                printf("Invalid. Address must be [0-65535]: ");
                                if(!buf_empty()) clear_buf();
                                else continue;
                        }
                }
        }
}

void prompt(void) {
        printf("Please select an operation:\n");
        printf("\ta. Access a memory address\n");
        printf("\tb. Show page table\n");
        printf("\tc. Reset to default mapping\n");
        printf("\td. Quit\n");
        printf("Selection: ");
}

bool buf_empty(void) {
        char ch = getchar();
        if(ch == '\n')
                return true;
        else {
                return false;
        }
}

void clear_buf(void) {
        char ch;
	while( ch != '\n' )
		ch = getchar();
}
