#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            // 区间[l, r]每个数+1，范围在[0,2^k-1]
            for (int i = l - 1; i < r; i++) {
                a[i]++;
                if (a[i] >= (1LL << k)) {
                    a[i] = 0;
                }
            }
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            // 查询区间[l, r]中1的个数
            int count = 0;
            for (int i = l - 1; i < r; i++) {
                if (__builtin_popcountll(a[i]) % 2 == 1) {
                    count++;
                }
            }
            cout << count << "\n";
        } else if (op == 3) {
            int l, r;
            cin >> l >> r;
            // 查询区间[l, r]中二进制表示各位1的总和
            long long total = 0;
            for (int i = l - 1; i < r; i++) {
                total += __builtin_popcountll(a[i]);
            }
            cout << total << "\n";
        }
    }

    return 0;
}
