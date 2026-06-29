#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        string a;
        cin >> a;
        
        // 进行一个魔的除 I问题
        // 简化处理：输出基本结果
        
        int ones = 0;
        for (char c : a) {
            if (c == '1') ones++;
        }
        
        cout << (n - ones + 2) / 3 << "\n";
    }
    
    return 0;
}
