#include <iostream>
#include <vector>
using namespace std;

// [GMOI R2-T2] 猫耳小（加强版）
// Without data file.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += a[i];
    cout << ans << "\n";
    return 0;
}
