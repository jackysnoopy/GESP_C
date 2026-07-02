#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> k(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i] >> p[i];
    }
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += p[i];
    }
    
    cout << ans << endl;
    return 0;
}