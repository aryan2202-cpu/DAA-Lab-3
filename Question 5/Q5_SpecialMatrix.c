#include <stdio.h>
#include <stdlib.h>

// Helper functions for matrix addition and subtraction
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Special Pattern Matrix Multiplication: O(n^2)
void multiply_special_matrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    // Base Case: 1x1 Matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A1[k][k], A2[k][k];
    int B1[k][k], B2[k][k];
    int C1[k][k], C2[k][k];

    // Extract block components A1, A2, B1, B2
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    int sumA[k][k], sumB[k][k], diffA[k][k], diffB[k][k];
    int P1[k][k], P2[k][k];

    // Compute P1 = (A1 + A2) * (B1 + B2)
    add(k, A1, A2, sumA);
    add(k, B1, B2, sumB);
    multiply_special_matrix(k, sumA, sumB, P1);

    // Compute P2 = (A1 - A2) * (B1 - B2)
    sub(k, A1, A2, diffA);
    sub(k, B1, B2, diffB);
    multiply_special_matrix(k, diffA, diffB, P2);

    // C1 = (P1 + P2) / 2, C2 = (P1 - P2) / 2
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j] = (P1[i][j] + P2[i][j]) / 2;
            C2[i][j] = (P1[i][j] - P2[i][j]) / 2;
        }
    }

    // Assemble final matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];
            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }
}

int main() {
    int n;
    printf("Enter dimension n (must be a power of 2, e.g., 2, 4): ");
    if (scanf("%d", &n) != 1 || n <= 0 || (n & (n - 1)) != 0) {
        printf("Invalid dimension!\n");
        return 0;
    }

    int A[n][n], B[n][n], C[n][n];

    printf("\nEnter Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    multiply_special_matrix(n, A, B, C);

    printf("\n--- Resultant Matrix (A x B) ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}