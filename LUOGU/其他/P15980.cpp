#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Process left to right. a[0] stays. For each i, a[i] must be in [a[i-1]-k, a[i-1]+k]
    // and a[i] >= original a[i]. If current a[i] > a[i-1]+k, impossible (can't lower).
    // If current a[i] < a[i-1]-k, raise to a[i-1]-k.
    // If current a[i] in [a[i-1]-k, a[i-1]+k], keep as is.
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i-1] + k) { cout << -1 << "\n"; return 0; }
        if (a[i] < a[i-1] - k) {
            ans += (a[i-1] - k) - a[i];
            a[i] = a[i-1] - k;
        }
    }
    cout << ans << "\n";
    return 0;
}
