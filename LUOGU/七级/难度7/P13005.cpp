#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<int> X(N), Y(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i] >> Y[i];
        }
        
        // 三角形问题
        // 找到最大三角形集合
        
        // 简单贪心：每次选择三个点形成三角形
        vector<bool> used(N, false);
        vector<tuple<int, int, int>> triangles;
        
        for (int i = 0; i < N; i++) {
            if (used[i]) continue;
            
            for (int j = i + 1; j < N; j++) {
                if (used[j]) continue;
                
                for (int k = j + 1; k < N; k++) {
                    if (used[k]) continue;
                    
                    // 检查三点不共线
                    long long cross = (long long)(X[j] - X[i]) * (Y[k] - Y[i]) - 
                                      (long long)(X[k] - X[i]) * (Y[j] - Y[i]);
                    
                    if (cross != 0) {
                        triangles.push_back({i + 1, j + 1, k + 1});
                        used[i] = true;
                        used[j] = true;
                        used[k] = true;
                        break;
                    }
                }
                
                if (used[i]) break;
            }
        }
        
        cout << "Case #" << t << ": " << triangles.size() << "\n";
        for (auto& [a, b, c] : triangles) {
            cout << a << " " << b << " " << c << "\n";
        }
    }
    
    return 0;
}
