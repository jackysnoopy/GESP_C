#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    long long ans = 0;
    while (n > 3) {
        // Strategy 1: a[1]+a[0]+a[n-1]+a[1] (two fastest ferry, fastest returns)
        // Strategy 2: a[n-1]+a[n-2]+a[0]+a[0] (two slowest go together)
        long long s1 = a[1] + a[0] + a[n-1] + a[1];
        long long s2 = a[n-1] + a[n-2] + a[0] + a[0];
        ans += min(s1, s2);
        n -= 2;
    }
    if (n == 3) ans += a[0] + a[1] + a[2];
    else if (n == 2) ans += a[1];
    else if (n == 1) ans += a[0];
    
    cout << ans << "\n";
    return 0;
}
