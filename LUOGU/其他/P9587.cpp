#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, n, k;
    if (!(cin >> c >> n >> k)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> val(n);
    for (int i = 0; i < n; ++i) val[i] = a[i];
    sort(val.begin(), val.end(), greater<int>());
    long long pref = 0;
    for (int i = 0; i < n; ++i) {
        pref += val[i];
        if (i + 1 == k) break;
    }
    for (int i = 0; i < n; ++i) {
        long long use = max(0, k - i);
        cout << use << '\n';
    }
    return 0;
}
