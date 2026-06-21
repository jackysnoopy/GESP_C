#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long x = h[i];
        while (x > 1) {
            ++ans;
            if (x == 2) { x = 1; break; }
            if (x % 2 == 1) x = x / 2 + 1;
            else x = x / 2;
        }
    }
    cout << ans << '\n';
    return 0;
}
