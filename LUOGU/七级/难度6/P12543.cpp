#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void energy(int n, vector<int> v) {
    // APIO 2025 交互题 - 需要调用 rotate 函数
    // 这里只提供框架
    
    // 策略：将所有杆旋转到均匀分布
    // 目标：最大化 sum of acute angles
    
    // 由于是交互题，这里只给出框架
    vector<int> indices(n);
    for (int i = 0; i < n; i++) indices[i] = i;
    
    // 示例：旋转所有杆
    // rotate(indices, 0); // 不旋转
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // 计算初始能量效率
    long long initial = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int diff = abs(v[i] - v[j]);
            initial += min(diff, 50000 - diff);
        }
    }
    
    cout << initial << endl;
    
    return 0;
}
