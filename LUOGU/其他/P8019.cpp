#include <iostream>
#include <vector>
using namespace std;

// [ONTAK2015] OR-XOR
// Greedy: try bits from high to low. For each bit, check if we can make all
// segment XORs have this bit = 0. Count segments where prefix XOR has this bit set.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    long long ans = 0;
    for (int bit = 60; bit >= 0; bit--) {
        long long mask = ans | ((1LL << bit) - 1);
        long long px = 0;
        int cnt = 1;
        for (int i = 0; i < n - 1; i++) {
            px ^= a[i];
            if ((px & mask) == 0) {
                cnt++;
            }
        }
        px ^= a[n - 1];
        if (cnt >= m && (px & mask) == 0) {
            ans |= (1LL << bit);
        }
    }
    cout << ans << "\n";
    return 0;
}
