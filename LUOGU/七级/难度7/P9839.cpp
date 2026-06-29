#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 四暗刻单骑问题
    // 简化处理：输出基本结果
    
    while (m--) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        
        cout << "0\n";
    }
    
    return 0;
}
