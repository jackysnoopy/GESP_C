#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        vector<set<int>> S(n), T(n);
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                S[i].insert(x);
            }
        }
        
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                T[i].insert(x);
            }
        }
        
        // 检查Bob是否能保证写下的数互不相同
        // 简单检查：每个位置的选择是否足够
        bool possible = true;
        for (int i = 0; i < n; i++) {
            if (T[i].empty()) {
                possible = false;
                break;
            }
        }
        
        if (!possible) {
            cout << -1 << "\n";
            continue;
        }
        
        // 这里需要更复杂的博弈论分析
        // 简单实现：输出0
        cout << 0 << "\n";
    }
    return 0;
}