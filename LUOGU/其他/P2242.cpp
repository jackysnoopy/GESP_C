#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int ans = 0;
    int i = 0;
    while (i < n) {
        ans++;
        int end = a[i] + m - 1;
        while (i < n && a[i] <= end) i++;
    }
    cout << ans << "\n";
    return 0;
}
