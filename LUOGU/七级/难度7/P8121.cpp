#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // ACP-II问题（交互题）
    // 简化版本：输出基本结果
    
    int n, m, k, d, b;
    cin >> n >> m >> k >> d >> b;
    
    // 简单策略：不动
    for (int i = 0; i < d; i++) {
        cout << "0\n";
    }
    
    return 0;
}
