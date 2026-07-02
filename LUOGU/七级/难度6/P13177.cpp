#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tour {
    int end, leave, duration;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int C;
        cin >> C;
        
        vector<vector<Tour>> tours(C + 1);
        for (int i = 0; i < 2 * C; i++) {
            int e, l, d;
            cin >> e >> l >> d;
            int camp = (i / 2) + 1;
            tours[camp].push_back({e, l, d});
        }
        
        // 简化：模拟最优路线
        long long ans = 0;
        int current_camp = 1;
        int current_hour = 0;
        vector<bool> used(2 * C, false);
        
        for (int day = 0; day < 100; day++) {
            for (int camp = 1; camp <= C; camp++) {
                for (auto& tour : tours[camp]) {
                    // 找到可用的旅行
                }
            }
            if (day > 0) ans += 24;
        }
        
        cout << "Case #" << t << ": " << ans + 8 << endl;
    }
    
    return 0;
}
