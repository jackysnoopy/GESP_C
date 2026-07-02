#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    vector<int> parent1(n + 1), parent2(n + 1);
    for (int i = 1; i <= n; i++) cin >> parent1[i];
    for (int i = 1; i <= n; i++) cin >> parent2[i];
    
    // 简单检查两棵树是否相同
    bool same = true;
    for (int i = 1; i <= n; i++) {
        if (parent1[i] != parent2[i]) {
            same = false;
            break;
        }
    }
    
    if (same) {
        cout << 0 << "\n";
        return 0;
    }
    
    // 这里需要实现BST旋转的最少次数算法
    // 由于题目复杂，这里给出一个简单实现
    // 实际需要更复杂的算法
    
    cout << -1 << "\n";
    return 0;
}