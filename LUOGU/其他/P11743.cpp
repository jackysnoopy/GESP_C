#include <iostream>
#include <vector>
using namespace std;

// P11743: Dynamic Array Problem
// Without data file.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += a[i];
    cout << ans << "\n";
    return 0;
}
