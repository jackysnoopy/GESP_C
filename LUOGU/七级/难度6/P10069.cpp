#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S, T;
    cin >> S >> T;
    
    // 简单实现：检查是否可能
    // 这里需要更复杂的算法
    int ans = -1;
    
    // 检查T是否是S的子串
    if (S.find(T) == string::npos) {
        ans = 0;
    } else {
        // 尝试一次操作
        // 这里需要更复杂的检查
        ans = -1;
    }
    
    cout << ans << "\n";
    return 0;
}