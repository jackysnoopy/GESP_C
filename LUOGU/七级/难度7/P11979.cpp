#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> min_shooting_buildings(vector<int> A) {
    int n = A.size();
    vector<pair<int, int>> result;
    
    // 射击游戏问题
    // 模拟过程
    vector<bool> destroyed(n, false);
    int remaining = n;
    
    while (remaining > 0) {
        int h1 = 1, h2 = 1;
        
        // 找到第一个未被摧毁的建筑物
        for (int i = 0; i < n; i++) {
            if (!destroyed[i]) {
                h1 = A[i];
                break;
            }
        }
        
        // 找到第二个未被摧毁的建筑物
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!destroyed[i] && A[i] != h1) {
                h2 = A[i];
                found = true;
                break;
            }
        }
        
        if (!found) {
            h2 = h1;
        }
        
        // 摧毁建筑物
        for (int i = 0; i < n; i++) {
            if (!destroyed[i] && A[i] >= min(h1, h2)) {
                destroyed[i] = true;
                remaining--;
            }
        }
        
        result.push_back({h1, h2});
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    vector<pair<int, int>> result = min_shooting_buildings(A);
    
    for (auto& [h1, h2] : result) {
        cout << h1 << " " << h2 << "\n";
    }
    
    return 0;
}
