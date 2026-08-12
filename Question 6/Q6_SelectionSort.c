#include <stdio.h>

// Function to perform Selection Sort using loop invariant principle
void selection_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        
        // Find smallest element in A[i...n-1]
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap smallest element with A[i]
        int temp = A[min_idx];
        A[min_idx] = A[i];
        A[i] = temp;
    }
}

void print_array(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input!\n");
        return 0;
    }

    int A[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("\nOriginal Array: ");
    print_array(A, n);

    selection_sort(A, n);

    printf("Sorted Array:   ");
    print_array(A, n);

    return 0;
}