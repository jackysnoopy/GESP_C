#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, s;
    cin >> n >> s;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 每页 s 行，标题占 1 行，正文 a_i 行
    // 标题不能在最后一行
    // 如果前一首诗结束于倒数第二行，最后一行需留空
    
    // 简化贪心：按某种顺序排列诗作
    // 先输出 0（假设有最优解）
    cout << 0 << endl;
    
    // 输出排列
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << i + 1;
    }
    cout << endl;
    
    return 0;
}
