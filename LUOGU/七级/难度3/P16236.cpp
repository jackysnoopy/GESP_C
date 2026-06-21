#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.rbegin(), a.rend());

    int ans = 0;
    for (int i = 0; i < min(3, n); i++) ans += a[i];

    cout << ans << "\n";
    return 0;
}
