#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    vector<long long> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    
    // 简单实现：计算每种颜色的最大数量
    vector<long long> ans(n);
    long long total = 0;
    
    for (int i = 0; i < n; i++) {
        // 使用第一类工具：可以变成任意颜色
        // 使用第二类工具：可以变成两个同色球
        long long cnt = a[i];
        
        // 使用第二类工具
        cnt += c[i] * 1; // 每个第二类工具增加一个球
        
        // 使用第一类工具
        cnt += b[i]; // 每个第一类工具增加一个球
        
        ans[i] = cnt;
        total += cnt;
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    cout << total << "\n";
    
    return 0;
}