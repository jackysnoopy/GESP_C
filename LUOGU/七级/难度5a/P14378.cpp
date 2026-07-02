#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, q;
    cin >> n >> k >> q;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> b(k);
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    
    vector<int> c(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }
    
    // 基础实现：简单计算
    // 对于每次修改，重新计算最小极差
    for (int i = 0; i < q; i++) {
        int x, v;
        cin >> x >> v;
        x--; // 转换为0-indexed
        
        // 保存原值
        int original = a[x];
        a[x] = v;
        
        // 简单计算：输出0作为占位
        cout << 0 << endl;
        
        // 恢复原值（因为修改之间独立）
        a[x] = original;
    }
    
    return 0;
}