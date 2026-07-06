#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    multiset<int> sizes;
    int offset = 0;
    int ans = n;
    long long prev_val = -2e9;

    for (int i = 0; i < n; ) {
        long long v = a[i];
        int cnt = 0;
        while (i < n && a[i] == v) { cnt++; i++; }

        if (v != prev_val + 1 && prev_val != -2e9) {
            for (int s : sizes) ans = min(ans, s + offset);
            sizes.clear();
            offset = 0;
        }

        int open = sizes.size();
        if (open > 0) offset++;

        if (cnt >= open) {
            for (int j = 0; j < cnt - open; j++)
                sizes.insert(1 - offset);
        } else {
            int finish = open - cnt;
            for (int j = 0; j < finish; j++) {
                auto it = prev(sizes.end());
                ans = min(ans, *it + offset);
                sizes.erase(it);
            }
        }

        prev_val = v;
    }

    for (int s : sizes) ans = min(ans, s + offset);

    cout << ans << endl;
    return 0;
}
