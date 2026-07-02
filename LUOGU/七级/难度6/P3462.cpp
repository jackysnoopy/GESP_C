#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, K;
    cin >> n >> K;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    
    long long ans = 0;
    int l = 0, r = 0;
    for (l = 0; l < n; l++) {
        while (r < n && a[r] - a[l] <= K) r++;
        ans = max(ans, (long long)(r - l));
    }
    
    cout << ans << endl;
    return 0;
}
