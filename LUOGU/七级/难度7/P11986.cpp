#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L, N, T;
    cin >> L >> N >> T;
    
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    
    // 救护车问题
    // 4辆救护车在4个角落，判断是否所有患者能在时间T内被运送
    
    // 医院位置
    vector<pair<int, int>> hospitals = {
        {1, 1}, {1, L}, {L, 1}, {L, L}
    };
    
    // 对于每个患者，计算到每个医院的距离
    vector<vector<int>> dist(N, vector<int>(4));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++) {
            dist[i][j] = abs(X[i] - hospitals[j].first) + abs(Y[i] - hospitals[j].second);
        }
    }
    
    // 贪心：每个患者选择最近的医院
    vector<int> hospital_count(4, 0);
    for (int i = 0; i < N; i++) {
        int best = 0;
        for (int j = 1; j < 4; j++) {
            if (dist[i][j] < dist[i][best]) {
                best = j;
            }
        }
        hospital_count[best]++;
    }
    
    // 检查是否能在时间T内完成
    bool possible = true;
    for (int i = 0; i < N; i++) {
        int min_dist = *min_element(dist[i].begin(), dist[i].end());
        if (min_dist > T) {
            possible = false;
            break;
        }
    }
    
    if (possible) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    
    return 0;
}
