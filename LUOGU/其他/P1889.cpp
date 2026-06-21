#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    
    sort(y.begin(), y.end());
    int y_mid = y[n / 2];
    long long ans = 0;
    for (int v : y) ans += abs(v - y_mid);
    
    sort(x.begin(), x.end());
    for (int i = 0; i < n; i++) x[i] -= i;
    sort(x.begin(), x.end());
    int x_mid = x[n / 2];
    for (int v : x) ans += abs(v - x_mid);
    
    cout << ans << "\n";
    return 0;
}