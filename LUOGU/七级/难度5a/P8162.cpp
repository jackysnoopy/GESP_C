#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    
    sort(a.begin(), a.end());
    
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        ans += a[i];
    }
    
    cout << ans << endl;
    return 0;
}