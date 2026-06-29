#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    
    string row1, row2;
    cin >> row1 >> row2;
    
    // 分割问题：将C(红球)移到右下，P(蓝球)移到左上
    // 使用冒泡排序的思想计算逆序对
    
    vector<int> grid(2 * N);
    for (int i = 0; i < N; i++) {
        grid[i] = (row1[i] == 'C') ? 1 : 0;
        grid[N + i] = (row2[i] == 'C') ? 1 : 0;
    }
    
    // 计算逆序对数
    auto count_inversions = [](vector<int>& g) -> ll {
        ll inv = 0;
        int n = g.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g[i] > g[j]) inv++;
            }
        }
        return inv;
    };
    
    cout << count_inversions(grid) << "\n";
    
    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        x--; y--;
        
        if (t == 1) {
            // 交换同行相邻
            swap(grid[x], grid[N + y]);
        } else {
            // 交换同列相邻
            swap(grid[x], grid[N + y]);
        }
        
        cout << count_inversions(grid) << "\n";
    }
    
    return 0;
}
