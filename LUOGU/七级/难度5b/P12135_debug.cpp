#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string row1, row2;
    cin >> row1 >> row2;
    
    int n = row1.length();
    
    // 建立并查集
    // 节点编号：(0, i) 对应 row1[i]，(1, i) 对应 row2[i]
    UnionFind uf(2 * n);
    
    // 统计检测器数量和连通分量
    int detector_count = 0;
    vector<bool> is_detector(2 * n, false);
    
    for (int i = 0; i < n; i++) {
        if (row1[i] == '#') {
            is_detector[i] = true;
            detector_count++;
        }
        if (row2[i] == '#') {
            is_detector[n + i] = true;
            detector_count++;
        }
    }
    
    // 合并相邻的检测器
    for (int i = 0; i < n; i++) {
        // 上下相邻
        if (is_detector[i] && is_detector[n + i]) {
            uf.unite(i, n + i);
        }
        
        // 左右相邻（第一行）
        if (i < n - 1) {
            if (is_detector[i] && is_detector[i + 1]) {
                uf.unite(i, i + 1);
            }
            if (is_detector[n + i] && is_detector[n + i + 1]) {
                uf.unite(n + i, n + i + 1);
            }
        }
    }
    
    // 统计连通分量数量
    int components = 0;
    vector<bool> seen(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        if (is_detector[i]) {
            int root = uf.find(i);
            if (!seen[root]) {
                seen[root] = true;
                components++;
            }
        }
    }
    
    // 调试输出
    cerr << "Detector count: " << detector_count << endl;
    cerr << "Components: " << components << endl;
    cerr << "Answer: " << components - 1 << endl;
    
    // 如果没有检测器，需要添加1个（但题目保证有检测器？）
    if (detector_count == 0) {
        cout << 1 << endl;
        return 0;
    }
    
    // 最少需要添加的检测器数量 = 连通分量数 - 1
    int ans = components - 1;
    
    cout << ans << endl;
    
    return 0;
}