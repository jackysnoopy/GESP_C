#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int height, weight, strength;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, h;
    cin >> n >> h;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].height >> cows[i].weight >> cows[i].strength;
    }
    
    // Sort by strength + weight (larger first)
    sort(cows.begin(), cows.end(), [](const Cow& a, const Cow& b) {
        return a.strength + a.weight > b.strength + b.weight;
    });
    
    // DP: dp[i][j] = maximum safety factor using first i cows with total weight j
    vector<vector<int>> dp(n + 1, vector<int>(n * 1000 + 1, -1));
    dp[0][0] = 1e9;
    
    int total_height = 0;
    int best_safety = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = n * 1000; j >= 0; j--) {
            if (dp[i][j] < 0) continue;
            
            // Don't take this cow
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            
            // Take this cow
            if (j + cows[i].weight <= cows[i].strength) {
                int new_safety = min(dp[i][j], cows[i].strength - j - cows[i].weight);
                dp[i + 1][j + cows[i].weight] = max(dp[i + 1][j + cows[i].weight], new_safety);
            }
        }
        
        // Check if we can reach height h
        if (dp[i + 1][0] >= 0) {
            int height_sum = 0;
            for (int k = 0; k <= i; k++) {
                height_sum += cows[k].height;
            }
            if (height_sum >= h) {
                best_safety = max(best_safety, dp[i + 1][0]);
            }
        }
    }
    
    if (best_safety < 0) {
        cout << "Mark is too tall\n";
    } else {
        cout << best_safety << "\n";
    }
    
    return 0;
}
