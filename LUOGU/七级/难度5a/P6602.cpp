#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> x(n), a(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> a[i];
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i];
    }
    
    cout << ans << endl;
    return 0;
}