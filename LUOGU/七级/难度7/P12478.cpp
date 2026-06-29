#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, o;
    cin >> n >> m >> o;
    
    int size = 1 << n;
    vector<int> a(size);
    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }
    
    // Désive问题
    // xormex: 将每个元素异或一个相同非负整数后，序列mex的最大值
    
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        // 计算子区间的xormex
        vector<int> sub(r - l + 1);
        for (int i = l; i <= r; i++) {
            sub[i - l] = a[i];
        }
        
        // 简单计算xormex
        int xormex = 0;
        for (int x = 0; x < 100; x++) {
            vector<bool> present(100, false);
            for (int val : sub) {
                int transformed = val ^ x;
                if (transformed < 100) {
                    present[transformed] = true;
                }
            }
            
            int mex = 0;
            while (mex < 100 && present[mex]) mex++;
            xormex = max(xormex, mex);
        }
        
        cout << xormex << "\n";
    }
    
    return 0;
}
