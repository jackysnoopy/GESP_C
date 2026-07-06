#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    sort(h.begin(), h.end());
    long long ans = 0;
    int l = 0, r = n - 1;
    int prev = 0;
    bool fromTop = true;
    while (l <= r) {
        if (fromTop) {
            ans += (long long)(h[r] - prev) * (h[r] - prev);
            prev = h[r];
            r--;
        } else {
            ans += (long long)(h[l] - prev) * (h[l] - prev);
            prev = h[l];
            l++;
        }
        fromTop = !fromTop;
    }
    cout << ans << endl;
    return 0;
}
