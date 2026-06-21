#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<long long> sorted_a = a;
        sort(sorted_a.begin(), sorted_a.end());
        long long cur_max = a[0];
        long long ans = a[0];
        int swaps_used = 0;
        int ptr = n - 1;
        for (int i = 1; i < n; i++) {
            if (a[i] > cur_max) {
                cur_max = a[i];
            } else if (swaps_used < k && ptr > i) {
                if (sorted_a[ptr] > cur_max) {
                    cur_max = sorted_a[ptr];
                    swaps_used++;
                    ptr--;
                }
            }
            ans += cur_max;
        }
        cout << ans << "\n";
    }
    return 0;
}
