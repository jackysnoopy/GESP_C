#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, m;
    int k;
    cin >> n >> m >> k;
    map<long long,int> cnt;
    long long total = 0;
    for (int i = 0; i < k; i++) {
        long long x, y;
        cin >> x >> y;
        total++;
        cnt[x - y]++;
    }
    long long ans = min(n, m);
    long long diag = total - ans;
    long long extra = 0;
    for (auto& p : cnt) {
        extra = max(extra, (long long)p.second);
    }
    cout << ans + extra << "\n";
    return 0;
}
