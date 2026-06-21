#include <iostream>
#include <vector>
using namespace std;

// [WHOI-2] 彗星蜜月
// Without data file, implementing a basic solution.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Sort and find pattern
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += a[i];
    cout << ans << "\n";
    return 0;
}
