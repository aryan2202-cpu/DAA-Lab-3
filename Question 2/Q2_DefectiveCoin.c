#include <stdio.h>

// Helper function to sum weights in a range
int get_weight(int coins[], int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += coins[i];
    }
    return sum;
}

// Divide & Conquer algorithm - O(log2 n) time complexity
int find_defective_coin(int coins[], int low, int high) {
    if (low == high) {
        return low; // Base case: single coin left
    }

    int mid = low + (high - low) / 2;
    int left_len = mid - low + 1;
    int right_len = high - mid;

    // Even split
    if (left_len == right_len) {
        int left_weight = get_weight(coins, low, mid);
        int right_weight = get_weight(coins, mid + 1, high);

        if (left_weight < right_weight) {
            return find_defective_coin(coins, low, mid);
        } else if (right_weight < left_weight) {
            return find_defective_coin(coins, mid + 1, high);
        } else {
            return -1; // No lighter coin in this range
        }
    } 
    // Odd split
    else {
        int left_weight = get_weight(coins, low, mid - 1);
        int right_weight = get_weight(coins, mid + 1, high);

        if (left_weight < right_weight) {
            return find_defective_coin(coins, low, mid - 1);
        } else if (right_weight < left_weight) {
            return find_defective_coin(coins, mid + 1, high);
        } else {
            // Compare middle coin against standard coin
            if (coins[mid] < coins[low]) {
                return mid;
            } else {
                return -1;
            }
        }
    }
}

int main() {
    int n, std_weight;

    printf("Enter total number of coins (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    printf("Enter standard weight of a genuine coin: ");
    if (scanf("%d", &std_weight) != 1) return 0;

    int coins[n];
    printf("Enter weights of %d coins:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    int index = find_defective_coin(coins, 0, n - 1);

    printf("\n--- Result ---\n");
    if (index != -1 && coins[index] < std_weight) {
        printf("Defective (lighter) coin found at Index %d (Weight: %d)\n", index, coins[index]);
    } else {
        printf("No defective coin present. All coins have exact required weight.\n");
    }

    return 0;
}