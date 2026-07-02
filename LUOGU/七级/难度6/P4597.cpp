#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Coordinate compression
    vector<long long> vals(a.begin(), a.end());
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    vector<int> comp(n);
    for (int i = 0; i < n; i++)
        comp[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();

    // DP using slope trick / priority queue
    // dp[i][j] = min cost for prefix i with a[i] mapped to value j
    // Optimization: dp[i][j] = min over k<=j of dp[i-1][k] + |a[i]-vals[j]|
    // This can be optimized using the "convex hull trick" or priority queue

    // Use the standard approach with two heaps (slope trick)
    // Maintain a piecewise linear convex function
    // For each a[i], add |x - a[i]| to the function, then take prefix min

    // Use multiset approach:
    // Process elements, maintain the function as a multiset of slopes
    // When processing a[i]:
    //   1. Insert a[i] twice (for the |x-a[i]| function)
    //   2. Remove the largest element (to make function non-decreasing)

    multiset<long long> S;
    long long ans = 0;
    long long lazy = 0;

    for (int i = 0; i < n; i++) {
        long long v = a[i];
        // Insert v-lazy twice
        S.insert(v - lazy);
        S.insert(v - lazy);
        // Remove the largest element (make function "flatter")
        auto it = S.end();
        --it;
        long long largest = *it;
        S.erase(it);
        // The new function minimum point shifts
        lazy += largest - (v - lazy);
        // Actually: we want to remove the element that makes the function non-decreasing
        // The standard approach:
        // After inserting two copies of v, the function has slopes: ...,-2,-1,0,1,2,...
        // centered at v. We need to shift the function to make it non-decreasing.
        // The "rightmost" slope that needs to be removed is the one at position v+lazy.
    }

    // Simpler approach using the known O(n log n) algorithm:
    // Use two multisets (left and right) to maintain the piecewise linear function
    // This is the "slope trick" for making sequence non-decreasing

    // Even simpler: use the DP with priority queue
    // f[i] = min cost to make a[0..i] non-decreasing
    // Process: maintain a max-heap. For each a[i]:
    //   Push a[i] twice to heap
    //   Pop the max (this accounts for the cost)
    //   The accumulated pops give the answer

    // Reset
    priority_queue<long long> pq;
    long long result = 0;
    for (int i = 0; i < n; i++) {
        pq.push(a[i]);
        pq.push(a[i]);
        long long top = pq.top();
        pq.pop();
        result += top - a[i];
    }
    cout << result << "\n";
    return 0;
}
