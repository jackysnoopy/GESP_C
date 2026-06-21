#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, s;
        cin >> n >> s;
        
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        
        int acc0 = s, acc1 = s;
        for (int i = 0; i < n; i++) {
            int mx = max(acc0, acc1);
            if (p[i] >= mx) {
                if (acc0 >= acc1) {
                    acc0 = (acc0 + p[i] + 1) / 2;
                } else {
                    acc1 = (acc1 + p[i] + 1) / 2;
                }
            } else {
                if (acc0 <= acc1) {
                    acc0 = (acc0 + p[i] + 1) / 2;
                } else {
                    acc1 = (acc1 + p[i] + 1) / 2;
                }
            }
        }
        
        cout << max(acc0, acc1) << endl;
    }
    
    return 0;
}
