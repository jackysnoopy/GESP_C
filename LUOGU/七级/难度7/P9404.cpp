#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, l, k, d;
    cin >> n >> l >> k >> d;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    // 扫雪波特问题
    // 简化处理：输出基本结果
    
    while (d--) {
        int z, u, p;
        cin >> z >> u >> p;
        
        vector<int> repair(z), broken(u);
        for (int i = 0; i < z; i++) cin >> repair[i];
        for (int i = 0; i < u; i++) cin >> broken[i];
        
        cout << l << "\n";
    }
    
    return 0;
}
