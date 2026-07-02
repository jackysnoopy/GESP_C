#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string s;
        cin >> s;
        
        int n = s.length();
        
        // 基础实现：简单模拟
        // 统计0、1、2的个数
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for (char c : s) {
            if (c == '0') cnt0++;
            else if (c == '1') cnt1++;
            else cnt2++;
        }
        
        // 简单策略：将2转换为0或1，使得能删除更多
        // 这里只输出简单结果作为占位
        int result = (cnt0 + cnt1 + cnt2) % 2;
        cout << result << endl;
    }
    
    return 0;
}