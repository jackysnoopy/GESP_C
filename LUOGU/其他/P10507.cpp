#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        int xr = 0;
        for (int i = n - 1; i >= 1; i -= 2)
            xr ^= a[i] - a[i - 1] - 1;
        cout << (xr ? "Georgia will win" : "Bob will win") << '\n';
    }
    return 0;
}
