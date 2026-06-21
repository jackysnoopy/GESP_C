#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int al = 0, ar = n - 1, bl = 0, br = n - 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[ar] > b[br]) { ans += 200; ar--; br--; }
        else if (a[al] > b[bl]) { ans += 200; al++; bl++; }
        else { if (a[al] < b[br]) ans -= 200; al++; br--; }
    }
    cout << ans << "\n";
    return 0;
}
