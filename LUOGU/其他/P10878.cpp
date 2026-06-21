#include <iostream>
#include <vector>
using namespace std;

// [JRKSJ R9] 在相思树下 III
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
