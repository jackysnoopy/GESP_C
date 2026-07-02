#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        
        string s;
        cin >> s;
        
        // 简单实现：填充'?'为'0'
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] != s[i + 1]) cnt++;
        }
        
        // 如果当前cnt等于k，直接输出
        if (cnt == k) {
            cout << s << "\n";
            continue;
        }
        
        // 否则尝试修改'?'位置
        // 这里需要更复杂的构造逻辑
        cout << "Impossible\n";
    }
    
    return 0;
}