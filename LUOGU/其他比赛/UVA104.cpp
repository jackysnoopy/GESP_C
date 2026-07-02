#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXN = 35;
double rate[MAXN][MAXN];  // 汇率矩阵
int next_node[MAXN][MAXN]; // 路径重建数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        // 初始化汇率矩阵
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> rate[i][j];
                next_node[i][j] = j; // 初始路径：直接到达
            }
        }
        
        // 修改版Floyd-Warshall算法
        // 用乘法代替加法，寻找最大汇率乘积
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (rate[i][k] * rate[k][j] > rate[i][j]) {
                        rate[i][j] = rate[i][k] * rate[k][j];
                        next_node[i][j] = next_node[i][k];
                    }
                }
            }
        }
        
        // 检查是否存在套利机会（起点终点相同的环）
        bool found = false;
        for (int i = 1; i <= n; i++) {
            if (rate[i][i] > 1.01) { // 超过1%利润即为套利
                found = true;
                
                // 路径重建：从i出发回到i
                vector<int> path;
                int cur = i;
                do {
                    path.push_back(cur);
                    cur = next_node[cur][i];
                } while (cur != i);
                path.push_back(i);
                
                // 输出路径
                for (int j = 0; j < (int)path.size(); j++) {
                    if (j > 0) cout << " ";
                    cout << path[j];
                }
                cout << "\n";
                break;
            }
        }
        
        if (!found) {
            cout << "no arbitrage sequence exists\n";
        }
    }
    
    return 0;
}
