#include <iostream>
#include <vector>
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
        
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }
        
        // 马赛克问题
        // 构造n个正方形，使得它们的并是一个矩形，且互不相交
        
        // 简单情况：如果所有点的x坐标或y坐标相同
        bool same_x = true, same_y = true;
        for (int i = 1; i < n; i++) {
            if (x[i] != x[0]) same_x = false;
            if (y[i] != y[0]) same_y = false;
        }
        
        if (same_x || same_y) {
            cout << "TAK";
            for (int i = 0; i < n; i++) {
                cout << " " << 1;
            }
            cout << "\n";
        } else {
            // 检查是否可能
            // 按x坐标排序
            vector<int> idx(n);
            for (int i = 0; i < n; i++) idx[i] = i;
            sort(idx.begin(), idx.end(), [&](int i, int j) {
                return x[i] < x[j];
            });
            
            // 检查是否有解
            bool possible = true;
            for (int i = 1; i < n; i++) {
                if (x[idx[i]] == x[idx[i-1]] && y[idx[i]] == y[idx[i-1]]) {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                cout << "TAK";
                for (int i = 0; i < n; i++) {
                    cout << " " << 1;
                }
                cout << "\n";
            } else {
                cout << "NIE\n";
            }
        }
    }
    
    return 0;
}
