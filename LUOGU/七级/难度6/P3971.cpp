#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    long long l = 0, r = n - 1;
    long long ans = 0;
    while (l < r) {
        long long sum = a[l] + a[r];
        if (sum == m) {
            ans++;
            l++;
            r--;
        } else if (sum < m) {
            l++;
        } else {
            r--;
        }
    }
    
    cout << ans << endl;
    return 0;
}
