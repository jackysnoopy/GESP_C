#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool canFormKit(const vector<int>& R, const vector<vector<int>>& Q, const vector<int>& packages, int servings) {
    for (int i = 0; i < R.size(); i++) {
        double required = (double)R[i] * servings;
        double minAllowed = required * 0.9;
        double maxAllowed = required * 1.1;
        
        if (Q[i][packages[i]] < minAllowed || Q[i][packages[i]] > maxAllowed) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, P;
        cin >> N >> P;
        
        vector<int> R(N);
        for (int i = 0; i < N; i++) {
            cin >> R[i];
        }
        
        vector<vector<int>> Q(N, vector<int>(P));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                cin >> Q[i][j];
            }
        }
        
        // 对于测试集1，N <= 2, P <= 8
        // 暴力枚举所有可能的包装组合
        
        int maxKits = 0;
        
        // 枚举每个包装的使用情况
        // 对于每种原料，我们需要选择相同数量的包装
        for (int count = 1; count <= P; count++) {
            // 尝试从每种原料中选择 count 个包装
            vector<vector<int>> selections(N);
            
            // 生成所有可能的选择
            function<void(int)> generate = [&](int ingredient) {
                if (ingredient == N) {
                    // 检查是否能形成 count 个 kit
                    bool valid = true;
                    
                    // 对于每个 kit，检查是否有效
                    for (int s = 0; s < count; s++) {
                        vector<int> packages(N);
                        for (int i = 0; i < N; i++) {
                            packages[i] = selections[i][s];
                        }
                        
                        // 尝试所有可能的份数
                        bool kitValid = false;
                        for (int servings = 1; servings <= 1000; servings++) {
                            if (canFormKit(R, Q, packages, servings)) {
                                kitValid = true;
                                break;
                            }
                        }
                        
                        if (!kitValid) {
                            valid = false;
                            break;
                        }
                    }
                    
                    if (valid) {
                        maxKits = max(maxKits, count);
                    }
                    return;
                }
                
                // 从当前原料中选择 count 个包装
                vector<bool> used(P, false);
                function<void(int)> select = [&](int selected) {
                    if (selected == count) {
                        generate(ingredient + 1);
                        return;
                    }
                    
                    for (int j = 0; j < P; j++) {
                        if (!used[j]) {
                            used[j] = true;
                            selections[ingredient].push_back(j);
                            select(selected + 1);
                            selections[ingredient].pop_back();
                            used[j] = false;
                        }
                    }
                };
                
                select(0);
            };
            
            generate(0);
        }
        
        cout << "Case #" << t << ": " << maxKits << endl;
    }
    
    return 0;
}
