#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        vector<long long> cnt(9);
        for (int i = 0; i < 9; i++) cin >> cnt[i];
        
        long long ans = 0;
        
        // 直接配对1-2和2-1木棒
        long long pairs = min(cnt[5], cnt[7]);
        ans += pairs;
        cnt[5] -= pairs;
        cnt[7] -= pairs;
        
        // 考虑其他配对方式
        // 1-2木棒后面可以接2-0, 2-1, 2-2木棒（左边是2）
        // 2-1木棒后面可以接1-0, 1-1, 1-2木棒（左边是1）
        
        // 尝试更复杂的配对
        // 由于题目限制较大，可能需要数学推导
        
        // 简单情况：如果还有1-2木棒，可以与2-0,2-2配对
        if (cnt[5] > 0) {
            long long can_pair = min(cnt[5], cnt[6] + cnt[8]);
            ans += can_pair;
            cnt[5] -= can_pair;
        }
        
        // 如果还有2-1木棒，可以与1-0,1-1配对
        if (cnt[7] > 0) {
            long long can_pair = min(cnt[7], cnt[3] + cnt[4]);
            ans += can_pair;
            cnt[7] -= can_pair;
        }
        
        cout << ans << "\n";
    }
    return 0;
}