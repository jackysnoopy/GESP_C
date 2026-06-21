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
    // Simple problem
    sort(a.begin(), a.end());
    long long ans = 0;
    for (int i = 1; i < n; i++) ans += a[i] - a[i-1];
    cout << ans << "\n";
    return 0;
}
