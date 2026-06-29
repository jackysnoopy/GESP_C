#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Item {
    int l, r, pos;
    long long val;
};

bool operator<(const Item& a, const Item& b) {
    return a.val < b.val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    // Prefix sums
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + a[i];
    }
    
    // For each starting position i, find the best ending position
    // The best ending position is the one that maximizes prefix[j] - prefix[i-1]
    // where i+L-1 <= j <= min(i+R-1, n)
    
    // Use a segment tree or sparse table to find maximum prefix in range
    // For simplicity, use a vector to track best ending for each start
    
    vector<int> best_end(n + 1, 0);
    for (int i = 1; i <= n - L + 1; i++) {
        int end = i + L - 1;
        best_end[i] = end;
    }
    
    // Use a priority queue to find top k subarrays
    priority_queue<Item> pq;
    
    for (int i = 1; i <= n - L + 1; i++) {
        int end = best_end[i];
        pq.push({i, end, end, prefix[end] - prefix[i - 1]});
    }
    
    long long ans = 0;
    
    for (int cnt = 0; cnt < k; cnt++) {
        Item item = pq.top();
        pq.pop();
        
        ans += item.val;
        
        // If we can extend the subarray
        if (item.r < min(item.l + R - 1, n)) {
            int new_r = item.r + 1;
            pq.push({item.l, new_r, new_r, prefix[new_r] - prefix[item.l - 1]});
        }
    }
    
    cout << ans << "\n";
    return 0;
}
