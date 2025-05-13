#include <stdio.h>
int multiplexer(int A0, int A1, int C) {
    return (A0 & ~C) | (A1 & C);
}

int main() {
    int A0, A1, C;
    
    
    printf("Enter A0 (0 or 1): ");
    scanf("%d", &A0);
    
    printf("Enter A1 (0 or 1): ");
    scanf("%d", &A1);
    
    printf("Enter C (0 or 1): ");
    scanf("%d", &C);
    
   
    if ((A0 != 0 && A0 != 1)  (A1 != 0 && A1 != 1)  (C != 0 && C != 1)) {
        printf("Invalid input! Please enter only 0 or 1.\n");
        return 1;
    }
    int X = multiplexer(A0, A1, C);
    printf("Output X: %d\n", X);
    
    return 0;
}
