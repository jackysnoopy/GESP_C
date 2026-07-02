#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    string s;
    cin >> s;
    
    // 前缀和统计0和1的个数
    vector<int> pre0(n + 1, 0), pre1(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pre0[i + 1] = pre0[i] + (s[i] == '0');
        pre1[i + 1] = pre1[i] + (s[i] == '1');
    }
    
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--; r--; // 转换为0-indexed
        
        int cnt0 = pre0[r + 1] - pre0[l];
        int cnt1 = pre1[r + 1] - pre1[l];
        
        // 基础实现：简单计算
        // 这里只输出0作为占位，实际需要更复杂的算法
        cout << 0 << endl;
    }
    
    return 0;
}