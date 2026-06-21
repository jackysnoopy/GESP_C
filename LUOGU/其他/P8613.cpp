#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    
    // Each person's unhappy cost = 1+2+...+k = k*(k+1)/2 where k = number of swaps.
    // Number of swaps for person i = number of people before i with height > h[i]
    //   + number of people after i with height < h[i]
    // This is the number of inversions involving person i.
    
    // Use BIT to count inversions.
    int maxH = 1000000;
    vector<int> bit(maxH + 2, 0);
    
    auto update = [&](int x, int v) {
        for (x++; x <= maxH + 1; x += x & (-x)) bit[x] += v;
    };
    auto query = [&](int x) -> int {
        int r = 0;
        for (x++; x > 0; x -= x & (-x)) r += bit[x];
        return r;
    };
    
    // Forward pass: count people before i with height > h[i]
    vector<int> left(n, 0);
    for (int i = 0; i < n; i++) {
        left[i] = query(maxH) - query(h[i]);
        update(h[i], 1);
    }
    
    // Backward pass: count people after i with height < h[i]
    fill(bit.begin(), bit.end(), 0);
    vector<int> right(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        right[i] = query(h[i] - 1);
        update(h[i], 1);
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long k = left[i] + right[i];
        ans += k * (k + 1) / 2;
    }
    
    cout << ans << "\n";
    return 0;
}
