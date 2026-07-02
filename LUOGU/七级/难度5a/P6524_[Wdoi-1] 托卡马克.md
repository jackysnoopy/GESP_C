#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    sort(x.begin(), x.end());
    
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans += x[i];
    }
    
    cout << ans << endl;
    return 0;
}