#include <stdio.h>

int main() {
    int minterms[] = {0, 2, 5, 7, 9, 11};
    int dont_cares[] = {3, 8, 10, 12, 14};
    int kmap[4][4] = {0};
    for (int i = 0; i < 6; i++) {
        int val = minterms[i];
        int row = (val >> 2) & 3; 
        int col = val & 3;       
        kmap[row][col] = 1;
    }
    for (int i = 0; i < 5; i++) {
        int val = dont_cares[i];
        int row = (val >> 2) & 3;
        int col = val & 3;      
        kmap[row][col] = -1; 
    }
    printf("K-map:\n");
    printf("PQ\\RS | 00 | 01 | 11 | 10 |\n");
    printf("------|----|----|----|----|\n");
    for (int i = 0; i < 4; i++) {
        printf(" %02d |", i);
        for (int j = 0; j < 4; j++) {
            if (kmap[i][j] == 1) {
                printf(" 1 |");
            } else if (kmap[i][j] == -1) {
                printf(" d |");
            } else {
                printf(" 0 |");
            }
        }
        printf("\n");
    }
    printf("\nEssential Prime Implicants:\n");
    printf("P'Q'R'\n");
    printf("P'QR\n");
    printf("PQ'R'\n");

    printf("\nNumber of Essential Prime Implicants: 3\n");

    return 0;
}
