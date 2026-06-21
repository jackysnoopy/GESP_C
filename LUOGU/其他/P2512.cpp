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
    
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    
    long long avg = sum / n;
    vector<long long> s(n);
    for (int i = 0; i < n; i++) {
        if (i > 0) s[i] = s[i-1];
        s[i] += a[i] - avg;
    }
    
    sort(s.begin(), s.end());
    long long mid = s[n / 2];
    long long ans = 0;
    for (long long x : s)
        ans += abs(x - mid);
    
    cout << ans << "\n";
    return 0;
}