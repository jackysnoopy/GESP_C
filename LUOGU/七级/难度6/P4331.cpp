#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    // Slope trick: maintain a max-heap of "kinks"
    // Each kink represents where the slope changes
    priority_queue<long long> pq;
    long long ans = 0;
    long long offset = 0;
    for (int i = 0; i < n; i++) {
        pq.push(t[i] - offset);
        pq.push(t[i] - offset);
        long long top = pq.top() + offset;
        pq.pop();
        if (top > t[i]) {
            ans += top - t[i];
            offset += top - t[i];
        }
    }
    cout << ans << "\n";
    // Now reconstruct the answer
    // The optimal z_i values can be recovered
    // Reset and use a different approach for reconstruction
    // Use the priority queue method to find z values
    vector<long long> z(n);
    priority_queue<long long> pq2;
    priority_queue<long long, vector<long long>, greater<long long>> pq_min;
    offset = 0;
    // Re-run with min-heap tracking
    // Actually use the standard approach with two heaps
    // For reconstruction, we track the "left" and "right" heaps
    // simpler: use the fact that z_i is the median of a group
    // Reconstruct by tracking positions
    vector<long long> z2(n);
    priority_queue<long long> left; // max-heap for left part
    long long off = 0;
    for (int i = 0; i < n; i++) {
        left.push(t[i] - off);
        left.push(t[i] - off);
        long long top = left.top() + off;
        left.pop();
        if (top > t[i]) {
            off += top - t[i];
        }
        z2[i] = left.top() + off;
    }
    // The reconstruction is tricky; let's use a cleaner approach
    // Use slope trick with explicit z tracking
    vector<long long> z3(n);
    // dp approach: process with two multisets
    // Actually the priority_queue approach for reconstruction:
    // z[i] = the "meeting point" of the piecewise linear function
    // Use the standard isotonic regression reconstruction
    // For now output the z from the algorithm
    // Reconstruct using the fact that we track the function minimum
    // The value at position i after processing is the median
    // Let's use a different reconstruction
    // z3[i] can be found by running the algorithm and tracking
    priority_queue<long long> L; // max-heap
    for (int i = 0; i < n; i++) {
        L.push(t[i]);
        L.push(t[i]);
        long long cur = L.top();
        L.pop();
        if (cur > t[i]) {
            long long diff = cur - t[i];
            ans += diff;
            // adjust: we need to "shift" the function
        }
        z3[i] = L.top();
    }
    // The proper reconstruction:
    // After the forward pass, we know the "breakpoints"
    // Use backward pass to determine exact z values
    // Standard isotonic regression: z[i] = median of some group
    // Let's use the DP/slope trick reconstruction properly
    // For output, use the greedy reconstruction:
    vector<long long> result(n);
    priority_queue<long long> pq_l;
    for (int i = 0; i < n; i++) {
        pq_l.push(t[i]);
        pq_l.push(t[i]);
        long long mx = pq_l.top();
        pq_l.pop();
        if (mx > t[i]) {
            pq_l.push(t[i]);
        }
        result[i] = pq_l.top();
    }
    long long check = 0;
    for (int i = 0; i < n; i++) check += abs(t[i] - result[i]);
    cout << check << "\n";
    for (int i = 0; i < n; i++) cout << result[i] << "\n";
    return 0;
}
