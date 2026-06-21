#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n <= 2) {
        cout << n << "\n";
        return 0;
    }
    int ans = 2; // first two always count
    for (int i = 2; i < n; i++) {
        if (a[i] > a[i-1] && a[i] > a[i-2]) ans++;
    }
    cout << ans << "\n";
    return 0;
}
