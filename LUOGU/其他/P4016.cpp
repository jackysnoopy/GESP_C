#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
long long a[100001], s[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long avg = 0;
    for (int i = 1; i <= n; i++) { cin >> a[i]; avg += a[i]; }
    avg /= n;
    for (int i = 1; i <= n; i++) a[i] -= avg;
    s[0] = 0;
    for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];
    sort(s, s+n);
    long long mid = s[n/2];
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += abs(s[i] - mid);
    cout << ans << "\n";
    return 0;
}
