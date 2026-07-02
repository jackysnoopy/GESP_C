#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 基础实现：简单计算
    // 对于每次询问，输出简单结果
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--; // 转换为0-indexed
        
        // 简单策略：输出区间长度减1作为占位
        cout << (r - l) << endl;
    }
    
    return 0;
}