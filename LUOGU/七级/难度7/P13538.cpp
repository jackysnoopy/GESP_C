#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> max_coupons(int A, vector<int> P, vector<int> T) {
    int n = P.size();
    
    // 节日游戏问题
    // 贪心：按类型和价格排序
    
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    
    // 按类型分组，优先选择类型大的
    sort(order.begin(), order.end(), [&](int i, int j) {
        if (T[i] != T[j]) return T[i] > T[j];
        return P[i] < P[j];
    });
    
    vector<int> result;
    int tokens = A;
    
    for (int i = 0; i < n; i++) {
        int idx = order[i];
        if (tokens >= P[idx]) {
            tokens -= P[idx];
            tokens *= T[idx];
            result.push_back(idx);
        }
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A, n;
    cin >> A >> n;
    
    vector<int> P(n), T(n);
    for (int i = 0; i < n; i++) cin >> P[i];
    for (int i = 0; i < n; i++) cin >> T[i];
    
    vector<int> result = max_coupons(A, P, T);
    
    cout << result.size() << "\n";
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    
    return 0;
}
