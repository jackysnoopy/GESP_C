#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;
const int P = 131;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s; cin >> s;
    int n = s.size();
    
    vector<ULL> h(n+1,0), pow(n+1,1);
    for (int i = 0; i < n; i++) {
        h[i+1] = h[i]*P + s[i];
        pow[i+1] = pow[i]*P;
    }
    
    auto get = [&](int l, int r) { return h[r] - h[l-1]*pow[r-l+1]; };
    auto lcp = [&](int a, int b) {
        int lo = 0, hi = n - max(a,b);
        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            if (get(a+1, a+mid) == get(b+1, b+mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    };
    
    vector<int> sa(n);
    for (int i = 0; i < n; i++) sa[i] = i;
    
    sort(sa.begin(), sa.end(), [&](int a, int b) {
        int len = lcp(a, b);
        if (a+len >= n || b+len >= n) return a > b;
        return s[a+len] < s[b+len];
    });
    
    for (int x : sa) cout << x << " "; cout << "\n";
    cout << 0 << " ";
    for (int i = 1; i < n; i++) cout << lcp(sa[i-1], sa[i]) << " ";
    cout << "\n";
    return 0;
}