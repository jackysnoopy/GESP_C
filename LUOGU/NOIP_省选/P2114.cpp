#include <iostream>
#include <vector>
#include <string>
using namespace std;

int calc(int x, const vector<pair<string, int>>& ops) {
    for (const auto& op : ops) {
        if (op.first == "AND") x &= op.second;
        else if (op.first == "OR") x |= op.second;
        else x ^= op.second;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<string, int>> ops(n);
    for (int i = 0; i < n; i++)
        cin >> ops[i].first >> ops[i].second;
    
    int ans = 0, cur = 0;
    for (int bit = 30; bit >= 0; bit--) {
        int res0 = calc(cur, ops) & (1 << bit);
        int res1 = calc(cur | (1 << bit), ops) & (1 << bit);
        if (res0 < res1 && (cur | (1 << bit)) <= m) {
            cur |= (1 << bit);
        }
        ans = max(ans, calc(cur, ops));
    }
    
    cout << ans << "\n";
    return 0;
}