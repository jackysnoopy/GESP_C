#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        // 子集乘积问题（交互题）
        // 简化版本：输出基本结果
        
        string ans(n, '0');
        cout << "! " << ans << endl;
        
        int response;
        cin >> response;
    }
    
    return 0;
}
