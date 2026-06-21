#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> give(n);
    give[0] = a[0];
    for (int i = 1; i < n; i++) {
        give[i] = max(a[i], give[i-1] + 1);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += give[i];
    cout << ans << "\n";
    return 0;
}
