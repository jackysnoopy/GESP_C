#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n;
    
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        int s, t;
        cin >> s >> t;
        s--;
        t--;
        
        long long ans = 0;
        for (int j = min(s, t); j < max(s, t); j++) {
            ans += abs(h[j] - h[j+1]);
        }
        
        cout << ans << endl;
    }
    
    return 0;
}