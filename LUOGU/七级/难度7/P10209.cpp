#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
int H, W, Q;
char A[MAXN][10], B[MAXN][10];
int C[MAXN];
int parent[MAXN * 2];
int rank_[MAXN * 2];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank_[x] < rank_[y]) swap(x, y);
    parent[y] = x;
    if (rank_[x] == rank_[y]) rank_[x]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> H >> W >> Q;
    
    for (int i = 1; i <= H; i++) {
        cin >> (A[i] + 1);
    }
    for (int i = 1; i < H; i++) {
        cin >> (B[i] + 1);
    }
    for (int i = 1; i <= H; i++) {
        cin >> C[i];
    }
    
    // 初始化并查集
    for (int i = 1; i <= H * W; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
    
    // 合并初始连通的交叉点
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j < W; j++) {
            if (A[i][j] == '1') {
                int u = (i - 1) * W + j;
                int v = (i - 1) * W + j + 1;
                unite(u, v);
            }
        }
    }
    for (int i = 1; i < H; i++) {
        for (int j = 1; j <= W; j++) {
            if (B[i][j] == '1') {
                int u = (i - 1) * W + j;
                int v = i * W + j;
                unite(u, v);
            }
        }
    }
    
    // 处理询问
    while (Q--) {
        int Tk;
        cin >> Tk;
        vector<int> points(Tk);
        for (int i = 0; i < Tk; i++) {
            int x, y;
            cin >> x >> y;
            points[i] = (x - 1) * W + y;
        }
        
        // 检查所有点是否已经连通
        bool connected = true;
        for (int i = 1; i < Tk; i++) {
            if (find(points[i]) != find(points[0])) {
                connected = false;
                break;
            }
        }
        
        if (connected) {
            cout << "0\n";
        } else {
            // 需要维修道路
            cout << "-1\n";
        }
    }
    
    return 0;
}
