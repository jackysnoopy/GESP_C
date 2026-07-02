#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> r(l + 1);
    for (int i = 1; i <= l; i++) {
        cin >> r[i];
    }
    
    vector<pair<int, pair<int, int>>> ops(m);
    for (int i = 0; i < m; i++) {
        cin >> ops[i].first >> ops[i].second.first >> ops[i].second.second;
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            ans++;
        }
    }
    
    cout << ans << endl;
    return 0;
}