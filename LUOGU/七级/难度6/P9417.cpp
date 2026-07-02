#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    
    vector<int> possible;
    
    // 简单实现：检查所有可能的长度
    for (int l = 1; l <= min(n, m); l++) {
        bool ok = true;
        
        // 检查是否可以用长度为l的模板覆盖整个矩形
        // 这里需要更复杂的检查逻辑
        
        if (ok) {
            possible.push_back(l);
        }
    }
    
    cout << possible.size() << "\n";
    for (int i = 0; i < possible.size(); i++) {
        if (i > 0) cout << " ";
        cout << possible[i];
    }
    cout << "\n";
    
    return 0;
}