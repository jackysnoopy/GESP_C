#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> p(n), k(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> k[i];
    vector<int> diff(n + 1, 0);
    for (int i = 0; i < n; i++) diff[i] = k[i] - p[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (diff[i] > 0) ans += diff[i];
        else if (diff[i] < 0) ans -= diff[i];
    }
    cout << ans << "\n";
    return 0;
}
