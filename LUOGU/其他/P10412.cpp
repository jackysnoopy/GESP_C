#include <iostream>
#include <vector>
using namespace std;

// [QFOI R2] 钟声远带斜阳
// Without data file.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Placeholder: find maximum subarray sum
    long long ans = a[0], cur = a[0];
    for (int i = 1; i < n; i++) {
        cur = max(a[i], cur + a[i]);
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
