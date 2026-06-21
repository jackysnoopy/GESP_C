#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long val = a[i];
        for (int j = 0; j < m; j++) {
            val *= 2;
        }
        ans |= val;
    }

    cout << ans << "\n";
    return 0;
}
