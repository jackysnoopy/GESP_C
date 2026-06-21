#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> D(n + 1);
    for (int i = 1; i < n; i++) cin >> D[i];
    
    vector<int> T(m), A(m), B(m);
    for (int i = 0; i < m; i++) cin >> T[i] >> A[i] >> B[i];
    
    // Compute leave time at each station: max(arrival, earliest passenger departure)
    vector<int> earliest(n + 1, 0);
    for (int i = 0; i < m; i++) {
        earliest[A[i]] = max(earliest[A[i]], T[i]);
    }
    
    // Forward pass: compute arrival and departure times
    vector<int> arr(n + 1), dep(n + 1);
    dep[1] = earliest[1];
    for (int i = 2; i <= n; i++) {
        arr[i] = dep[i - 1] + D[i - 1];
        dep[i] = max(arr[i], earliest[i]);
    }
    
    while (k > 0) {
        // Compute benefit of reducing each D[i] by 1
        // A segment i benefits passengers who board at or after station i+1
        // But only if the bus arrival at their destination is affected
        
        // Influence: how many passengers are affected by segment i
        vector<int> benefit(n + 1, 0);
        vector<int> eff(n + 1, 0); // eff[i] = number of passengers who can be affected starting from station i
        // Recompute with current D
        dep[1] = earliest[1];
        for (int i = 2; i <= n; i++) {
            arr[i] = dep[i - 1] + D[i - 1];
            dep[i] = max(arr[i], earliest[i]);
        }
        // For each segment, compute how many passengers ride through it
        // A passenger from A to B rides segments A, A+1, ..., B-1
        // But they only benefit if arr[B] would decrease (i.e., if dep[B] == arr[B] or later segments haven't absorbed the slack)
        // Compute from back: suffix count of passengers
        vector<int> cnt(n + 2, 0);
        for (int i = 0; i < m; i++) {
            cnt[A[i]]++;
            cnt[B[i]]--;
        }
        vector<int> suffix(n + 2, 0);
        for (int i = n; i >= 1; i--) {
            suffix[i] = suffix[i + 1] + cnt[i];
        }
        // benefit[i] = suffix[i+1] if reducing D[i] actually helps
        // D[i] helps if there's no wait that absorbs it, i.e., dep[i+1] > arr[i+1] means some passengers at i+1 wait
        // Actually: benefit of reducing D[i] is the number of passengers who ride through segment i
        // whose arrival at destination is not blocked by a later wait
        // Simpler: just use greedy with recomputation
        int bestEdge = -1;
        for (int i = 1; i < n; i++) {
            if (D[i] <= 0) continue;
            // Number of passengers riding this segment
            benefit[i] = suffix[i + 1];
        }
        bestEdge = 1;
        for (int i = 2; i < n; i++) {
            if (benefit[i] > benefit[bestEdge]) bestEdge = i;
        }
        if (benefit[bestEdge] <= 0) break;
        D[bestEdge]--;
        k--;
    }
    
    dep[1] = earliest[1];
    for (int i = 2; i <= n; i++) {
        arr[i] = dep[i - 1] + D[i - 1];
        dep[i] = max(arr[i], earliest[i]);
    }
    
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += arr[B[i]] - T[i];
    }
    cout << ans << "\n";
    return 0;
}
