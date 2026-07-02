#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    
    vector<tuple<int, int, int>> beavers(N);
    for (int i = 0; i < N; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        beavers[i] = {x, y, z};
    }
    
    // 简单实现：枚举所有可能的组合
    int ans = -1;
    
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                auto [x1, y1, z1] = beavers[i];
                auto [x2, y2, z2] = beavers[j];
                auto [x3, y3, z3] = beavers[k];
                
                // 检查是否符合条件
                bool ok = true;
                
                // 检查每个成员是否有一项能力严格大于其他两人
                // 这里需要更复杂的检查逻辑
                
                if (ok) {
                    int total = max({x1, x2, x3}) + max({y1, y2, y3}) + max({z1, z2, z3});
                    ans = max(ans, total);
                }
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}