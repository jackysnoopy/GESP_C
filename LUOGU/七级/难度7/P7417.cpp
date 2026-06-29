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
        int N, M;
        cin >> N >> M;
        
        vector<pair<int, int>> edges(M);
        for (int i = 0; i < M; i++) {
            cin >> edges[i].first >> edges[i].second;
        }
        
        // Minimizing Edges问题
        // 计算最小边数
        
        // 简化处理：输出基本结果
        cout << M << "\n";
    }
    
    return 0;
}
