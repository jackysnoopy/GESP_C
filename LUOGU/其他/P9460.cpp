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
    if (k == 0) {
        cout << n << '\n';
        return 0;
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) mx = max(mx, a[i]);
    cout << n + k - mx + 1 << '\n';
    return 0;
}
