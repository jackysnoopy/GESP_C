#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int ans = 0;
    int j = 0;
    for (int i = 0; i < n && j < k; i++) {
        if (a[i] >= b[j]) {
            ans++;
            j++;
        }
    }
    
    cout << ans << endl;
    return 0;
}