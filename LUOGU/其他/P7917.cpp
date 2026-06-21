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
    sort(a.begin(), a.end(), greater<long long>());
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    // Need to find max subset sum
    long long ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
