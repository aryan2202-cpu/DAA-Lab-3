#include <stdio.h>

// Structure to return both max and min values
struct Pair {
    int max;
    int min;
};

// Divide and Conquer function to find Max and Min
struct Pair get_max_min(int arr[], int low, int high) {
    struct Pair result, left_res, right_res;
    int mid;

    // Base Case 1: Only 1 element
    if (low == high) {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    // Base Case 2: Only 2 elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    // Divide: Find mid point
    mid = low + (high - low) / 2;

    // Conquer: Recursively solve left and right halves
    left_res = get_max_min(arr, low, mid);
    right_res = get_max_min(arr, mid + 1, high);

    // Combine: Compare results of both halves
    if (left_res.max > right_res.max) {
        result.max = left_res.max;
    } else {
        result.max = right_res.max;
    }

    if (left_res.min < right_res.min) {
        result.min = left_res.min;
    } else {
        result.min = right_res.min;
    }

    return result;
}

int main() {
    int n;

    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 0;
    }

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Pair result = get_max_min(arr, 0, n - 1);

    printf("\n--- Result ---\n");
    printf("Maximum element: %d\n", result.max);
    printf("Minimum element: %d\n", result.min);

    return 0;
}