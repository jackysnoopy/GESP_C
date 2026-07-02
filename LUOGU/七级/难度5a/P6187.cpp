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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        
        long long ans = 0;
        for (int j = 0; j < n; j++) {
            ans += (long long)a[j] * a[(j + k) % n];
        }
        
        cout << ans << endl;
    }
    
    return 0;
}