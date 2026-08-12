#include <stdio.h>
#include <stdlib.h>

// Function to add two matrices
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void sub(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's Matrix Multiplication Algorithm
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    // Base Case: 1x1 Matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Sub-matrices initialization
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];

    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int T1[k][k], T2[k][k];

    // Divide matrices into 4 sub-matrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(k, A11, A22, T1);
    add(k, B11, B22, T2);
    strassen(k, T1, T2, M1);

    // M2 = (A21 + A22) * B11
    add(k, A21, A22, T1);
    strassen(k, T1, B11, M2);

    // M3 = A11 * (B12 - B22)
    sub(k, B12, B22, T2);
    strassen(k, A11, T2, M3);

    // M4 = A22 * (B21 - B11)
    sub(k, B21, B11, T2);
    strassen(k, A22, T2, M4);

    // M5 = (A11 + A12) * B22
    add(k, A11, A12, T1);
    strassen(k, T1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    sub(k, A21, A11, T1);
    add(k, B11, B12, T2);
    strassen(k, T1, T2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    sub(k, A12, A22, T1);
    add(k, B21, B22, T2);
    strassen(k, T1, T2, M7);

    // C11 = M1 + M4 - M5 + M7
    add(k, M1, M4, T1);
    sub(k, T1, M5, T2);
    add(k, T2, M7, C11);

    // C12 = M3 + M5
    add(k, M3, M5, C12);

    // C21 = M2 + M4
    add(k, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    sub(k, M1, M2, T1);
    add(k, T1, M3, T2);
    add(k, T2, M6, C22);

    // Combine results into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    int n;
    printf("Enter matrix dimension n (must be a power of 2, e.g., 2, 4): ");
    if (scanf("%d", &n) != 1 || n <= 0 || (n & (n - 1)) != 0) {
        printf("Invalid input! Dimension n must be a power of 2.\n");
        return 0;
    }

    int A[n][n], B[n][n], C[n][n];

    printf("\nEnter elements of Matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter elements of Matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("\n--- Resultant Matrix (A x B) ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}