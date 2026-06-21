#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> pos;
    for (int i = 0; i < n; ++i) if (a[i] == 2 || a[i] == 3) pos.push_back(i);
    if (pos.empty()) { cout << n << '\n'; return 0; }
    vector<int> dp;
    for (int x : pos) {
        int v = (a[x] == 2 ? x : -x);
        auto it = lower_bound(dp.begin(), dp.end(), v);
        if (it == dp.end()) dp.push_back(v);
        else *it = v;
    }
    cout << n - (int)dp.size() << '\n';
    return 0;
}
