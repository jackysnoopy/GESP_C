#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int m = n;
    int best = m;
    for (int i = 0; i < n; ++i) {
        int cur = 0, used = 0;
        for (int j = i; j < n; ++j) {
            if (a[j] >= k) {
                best = min(best, used);
                break;
            }
            ++cur;
            if (cur + 1 == k) {
                ++used;
                cur = 0;
            }
        }
        best = min(best, used);
    }
    cout << best << '\n';
    return 0;
}
