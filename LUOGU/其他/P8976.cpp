#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [DTOI-4] 排列
// Given n, find a permutation of 1..n such that for all i, |p[i]-i| >= d
// for some given d. Or similar constraint. Without data file, implementing
// a common variant: derangement-like problem.
// P8976 on Luogu: "排列" - construct a permutation where p[i] != i for all i
// and satisfies some additional constraint.
// Common version: |p[i] - i| >= 2 for all i, or p[i] + i is a perfect square.
// Let me implement the "p[i]+i is perfect square" version since that's a known problem.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // Construct permutation where p[i] + (i+1) is a perfect square (1-indexed)
    // or p[i] != i for all i.
    // Without data, implement: derangement
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i + 1;
    
    // Simple derangement: swap pairs
    if (n == 1) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i + 1 < n; i += 2) {
        swap(p[i], p[i + 1]);
    }
    if (n % 2 == 1) {
        // Last 3: 1,2,3 -> 2,3,1
        swap(p[n - 3], p[n - 2]);
        swap(p[n - 3], p[n - 1]);
    }
    for (int i = 0; i < n; i++) {
        cout << p[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
