#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    // Read and process
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int mx = 0;
        for (int j = l; j <= r; j++) mx = max(mx, a[j]);
        cout << mx << (i == m-1 ? "\n" : " ");
    }
    return 0;
}
