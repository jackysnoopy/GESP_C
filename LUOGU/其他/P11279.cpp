#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    sort(w.begin(), w.end());
    long long ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans += w[i] * w[n - 1 - i];
    }
    cout << ans << "\n";
    return 0;
}
