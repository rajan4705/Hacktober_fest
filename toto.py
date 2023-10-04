#include <iostream>
#include <vector>

using namespace std;

// Structure to represent items
struct Item {
    int weight;
    int value;
};

// Function to solve the 0/1 Knapsack problem using dynamic programming
int knapsack(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    vector<Item> items = {
        {2, 10},
        {3, 15},
        {5, 40},
        {7, 60}
    };
    int capacity = 10;

    int max_value = knapsack(items, capacity);

    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
