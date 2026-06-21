#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    int m;
    string s;
    cin >> m >> s;
    
    vector<int> pos;
    for (int i = 0; i + 2 < m; i++) {
        if (s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
            pos.push_back(i);
            i += 2;
        }
    }
    
    long long ans = 0;
    int sz = (int)pos.size();
    for (int i = 0; i < sz; ) {
        int j = i;
        while (j + 1 < sz && pos[j + 1] == pos[j] + 3) j++;
        int len = j - i + 1;
        
        vector<long long> f(len + 1, 0);
        for (int k = 1; k <= len; k++) {
            for (int t = 1; t <= min(n, k); t++) {
                f[k] = max(f[k], f[k - t] + a[t]);
            }
        }
        ans += f[len];
        i = j + 1;
    }
    
    cout << ans << '\n';
    
    return 0;
}
