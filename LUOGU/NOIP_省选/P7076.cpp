#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, c, k;
    cin >> n >> m >> c >> k;
    vector<long long> animals(n);
    for (int i = 0; i < n; i++) cin >> animals[i];
    vector<long long> bitmask(k, 0);
    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        if (p < k) bitmask[p] |= (1LL << q);
    }
    long long usedBits = 0;
    for (long long a : animals) {
        for (int i = 0; i < k; i++) {
            if (a & (1LL << i)) usedBits |= bitmask[i];
        }
    }
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        bool canAdd = true;
        for (int j = 0; j < k; j++) {
            if (bitmask[j] != 0 && (usedBits & bitmask[j]) == bitmask[j]) {
                canAdd = true;
            }
        }
        if (!(usedBits & (1LL << i))) {
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
