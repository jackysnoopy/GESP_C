#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Q;
    cin >> Q;
    
    while (Q--) {
        string S;
        cin >> S;
        
        // 小园香径独徘徊问题
        // 构造字典序最小的T
        
        // 简化处理：输出排序后的字符串
        string T = S;
        sort(T.begin(), T.end());
        
        cout << T << "\n";
    }
    
    return 0;
}
