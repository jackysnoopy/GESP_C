#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> w(n), c(m);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < m; i++) cin >> c[i];
    sort(w.begin(), w.end());
    sort(c.begin(), c.end());
    int ans = 0;
    int j = 0;
    for (int i = 0; i < n && j < m; i++) {
        while (j < m && c[j] < w[i]) j++;
        if (j < m) { ans++; j++; }
    }
    cout << ans << "\n";
    return 0;
}
