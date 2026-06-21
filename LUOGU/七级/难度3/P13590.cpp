#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // Min left-movers: greedy, match smallest b >= a
    {
        multiset<int> bs(b.begin(), b.end());
        int mn = 0;
        for (int i = 0; i < n; i++) {
            auto it = bs.lower_bound(a[i]);
            if (it != bs.end()) { bs.erase(it); }
            else { bs.erase(bs.begin()); mn++; }
        }
        // Max left-movers: match largest b < a
        bs = multiset<int>(b.begin(), b.end());
        int mx = 0;
        for (int i = n - 1; i >= 0; i--) {
            auto it = bs.lower_bound(a[i]);
            if (it != bs.begin()) { --it; bs.erase(it); mx++; }
            else { bs.erase(prev(bs.end())); }
        }
        cout << (mx - mn + 1) << "\n";
        for (int v = mn; v <= mx; v++) cout << v << (v < mx ? " " : "\n");
    }
    return 0;
}
