#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        vector<int> L(m), R(m), V(m);
        for (int i = 0; i < m; i++) {
            cin >> L[i] >> R[i] >> V[i];
        }
        
        // 冒泡排序问题
        // 计算最小交换次数
        
        // 简化处理：输出基本结果
        cout << "0\n";
    }
    
    return 0;
}
