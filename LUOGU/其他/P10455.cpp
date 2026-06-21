#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int k;

long long check(const vector<int>& a, int l, int r) {
    vector<int> b(a.begin() + l, a.begin() + r + 1);
    sort(b.begin(), b.end());
    long long sum = 0;
    int len = b.size();
    for (int i = 0; i < k && i < len / 2; i++) {
        long long diff = b[len - 1 - i] - b[i];
        sum += diff * diff;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        long long lim;
        cin >> n >> m >> lim;
        k = m;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        int ans = 0, start = 0;
        while (start < n) {
            int len = 1, end = start;
            while (len > 0) {
                int next_end = min(n - 1, end + len);
                if (check(a, start, next_end) <= lim) {
                    end = next_end;
                    len *= 2;
                } else {
                    len /= 2;
                }
            }
            start = end + 1;
            ans++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}