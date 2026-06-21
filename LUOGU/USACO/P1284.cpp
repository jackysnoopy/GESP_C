#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> len(n);
    int total = 0;
    for (int i = 0; i < n; i++) { cin >> len[i]; total += len[i]; }
    vector<bool> dp(total / 2 + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = total / 2; j >= len[i]; j--) {
            if (dp[j - len[i]]) dp[j] = true;
        }
    }
    double best = 0;
    bool found = false;
    for (int i = 0; i <= total / 2; i++) {
        if (!dp[i]) continue;
        long long a = i, b = total - i;
        for (int j = 0; j < n; j++) {
            vector<int> remaining;
            int rem = len[j];
            vector<int> used;
            for (int k = 0; k < n; k++) {
                if (k == j) continue;
                used.push_back(len[k]);
            }
            // Try different splits: side a uses some, side b uses the rest
        }
        // Just try all partitions
    }
    // Better approach: knapsack for all three sides
    // Fix side c, then split remaining into a and b
    best = 0;
    found = false;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long sumC = 0;
        vector<int> rest;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) sumC += len[i];
            else rest.push_back(len[i]);
        }
        if (sumC == 0) continue;
        int rSize = (int)rest.size();
        int rSum = (int)sumC <= total / 2 ? total - (int)sumC : total;
        // Split rest into a and b
        for (int sm = 0; sm < (1 << rSize); sm++) {
            long long sumA = 0;
            for (int j = 0; j < rSize; j++) {
                if (sm & (1 << j)) sumA += rest[j];
            }
            long long sumB = (total - sumC) - sumA;
            if (sumA == 0 || sumB == 0) continue;
            if (sumA + sumB <= sumC || sumA + sumC <= sumB || sumB + sumC <= sumA) continue;
            double s = total / 2.0;
            double area = sqrt(s * (s - sumA) * (s - sumB) * (s - sumC));
            if (area > best) { best = area; found = true; }
        }
    }
    if (!found) cout << -1 << "\n";
    else cout << (int)(best * 100) << "\n";
    return 0;
}
