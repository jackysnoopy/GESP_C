#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, b;
    cin >> t >> b;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> p(n);
        for (int i = 1; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }
        
        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            cin >> l[i] >> r[i];
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, r[i] - l[i]);
        }
        
        cout << ans << endl;
        
        if (b == 1) {
            for (int i = 0; i < n; i++) {
                cout << l[i] << " ";
            }
            cout << endl;
        }
    }
    
    return 0;
}