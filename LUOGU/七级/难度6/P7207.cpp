#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // 对于每个x，找y使得x & y == x
    // 即y的二进制表示中，x为1的位y也必须为1
    // y = M, M+1, ..., M+N-1
    
    // 贪心：按x的popcount降序处理，优先分配y
    vector<int> xord(n), yord(n);
    for (int i = 0; i < n; i++) xord[i] = i;
    for (int i = 0; i < n; i++) yord[i] = m + i;
    
    sort(xord.begin(), xord.end(), [](int a, int b) {
        return __builtin_popcount(a) > __builtin_popcount(b);
    });
    
    vector<bool> used(n, false);
    vector<pair<int,int>> result(n);
    
    for (int xi = 0; xi < n; xi++) {
        int x = xord[xi];
        bool found = false;
        for (int yi = 0; yi < n; yi++) {
            if (used[yi]) continue;
            int y = yord[yi];
            if ((x & y) == x) {
                result[xi] = {x, y};
                used[yi] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            // 应该总能找到
            result[xi] = {x, m};
        }
    }
    
    for (auto& p : result) {
        cout << p.first << " " << p.second << "\n";
    }
    
    return 0;
}
