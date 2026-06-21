#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int np = 10;
    
    auto getMask = [&](int x) {
        int mask = 0;
        for (int i = 0; i < np; i++) {
            int cnt = 0;
            while (x % primes[i] == 0) { x /= primes[i]; cnt++; }
            if (cnt & 1) mask |= (1 << i);
        }
        return mask;
    };
    
    map<int, long long> cnt;
    cnt[0] = 1;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur ^= getMask(a[i]);
        cnt[cur]++;
    }
    
    long long ans = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        long long c = it->second;
        ans += c * (c - 1) / 2;
    }
    cout << ans << "\n";
    return 0;
}
