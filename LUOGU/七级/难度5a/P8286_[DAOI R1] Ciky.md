#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), b(m), c(m), k(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> k[i];
    }
    
    sort(a.begin(), a.end(), greater<int>());
    
    int ans1 = min(n, m);
    long long ans2 = 0;
    for (int i = 0; i < min(n, m); i++) {
        ans2 += c[i];
    }
    
    cout << ans1 << endl;
    cout << ans2 << endl;
    
    return 0;
}