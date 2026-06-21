#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> l(n), r(n), val;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        val.push_back(l[i]);
        val.push_back(r[i] + 1);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    vector<int> d(val.size() + 1, 0);
    for (int i = 0; i < n; i++) {
        int li = lower_bound(val.begin(), val.end(), l[i]) - val.begin() + 1;
        int ri = lower_bound(val.begin(), val.end(), r[i] + 1) - val.begin() + 1;
        d[li]++; d[ri]--;
    }
    long long ans = 0;
    int cur = 0;
    for (int i = 1; i < (int)val.size(); i++) {
        cur += d[i];
        if (cur > 0) ans += (long long)(val[i] - val[i-1]) * cur;
    }
    cout << ans << "\n";
    return 0;
}
