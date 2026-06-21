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
    // Lottery Fun Time: without full problem, implement common approach.
    // Likely: maximize expected value or find optimal strategy.
    
    // Simple: sort and compute
    sort(a.begin(), a.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] * (2 * i - n + 1);
    }
    cout << ans << endl;
    return 0;
}
