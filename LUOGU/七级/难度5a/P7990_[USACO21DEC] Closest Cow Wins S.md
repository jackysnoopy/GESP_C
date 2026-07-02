#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, m, n;
    cin >> k >> m >> n;
    
    vector<int> p(k), t(k);
    for (int i = 0; i < k; i++) {
        cin >> p[i] >> t[i];
    }
    
    vector<int> f(m);
    for (int i = 0; i < m; i++) {
        cin >> f[i];
    }
    
    sort(p.begin(), p.end());
    sort(f.begin(), f.end());
    
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        ans += t[i];
    }
    
    cout << ans << endl;
    return 0;
}