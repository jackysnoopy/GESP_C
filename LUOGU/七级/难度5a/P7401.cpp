#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, h;
    cin >> n >> h;
    
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    
    int ans = 0;
    for (int i = 1; i < n - 1; i += 2) {
        if (y[i] > y[i-1] && y[i] > y[i+1]) {
            ans++;
        }
    }
    
    cout << ans << endl;
    return 0;
}