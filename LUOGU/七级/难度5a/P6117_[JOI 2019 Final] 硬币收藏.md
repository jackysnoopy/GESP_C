#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> x(2 * n), y(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> x[i] >> y[i];
    }
    
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(x[i] - (i + 1));
        ans += abs(y[i] - 1);
    }
    
    cout << ans << endl;
    return 0;
}