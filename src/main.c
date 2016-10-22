#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mmu.h"

int main() {
        struct mmu *mmu = create_mmu();
        print_state(mmu);
        free_mmu(mmu);
}
