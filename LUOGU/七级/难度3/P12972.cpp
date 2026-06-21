#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<unsigned long long> a(n + 1);
    for (int i = 1; i <= n; i++) scanf("%llu", &a[i]);
    vector<unsigned long long> dp(n + 1);
    dp[0] = 0;
    vector<pair<unsigned long long, unsigned long long>> cur;
    for (int i = 1; i <= n; i++) {
        for (auto& [ov, bd] : cur) ov |= a[i];
        cur.insert(cur.begin(), {a[i], dp[i - 1]});
        vector<pair<unsigned long long, unsigned long long>> nxt;
        for (auto& [ov, bd] : cur) {
            if (!nxt.empty() && nxt.back().first == ov) nxt.back().second = min(nxt.back().second, bd);
            else nxt.push_back({ov, bd});
        }
        cur = nxt;
        unsigned long long best = ULLONG_MAX;
        for (auto& [ov, bd] : cur) best = min(best, bd + ov);
        dp[i] = best;
    }
    printf("%llu\n", dp[n]);
    return 0;
}
