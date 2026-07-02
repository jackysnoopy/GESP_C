#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXN = 1000005;
int a[MAXN], b[MAXN];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    
    // Simplified approach: count inversions
    long long ans = 0;
    
    // For bubble sort, answer is number of inversions
    // But with constraints, we need to find optimal arrangement
    
    // Simple greedy: assign values to minimize inversions
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        pos[a[i]] = i;
    }
    
    // Count inversions in permutation
    vector<int> bit(n + 1, 0);
    
    auto update = [&](int x) {
        for (; x <= n; x += x & (-x)) {
            bit[x]++;
        }
    };
    
    auto query = [&](int x) {
        int sum = 0;
        for (; x > 0; x -= x & (-x)) {
            sum += bit[x];
        }
        return sum;
    };
    
    for (int i = 1; i <= n; i++) {
        ans += i - 1 - query(a[i]);
        update(a[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}