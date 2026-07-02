#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(int n, int m, vector<int>& a, int diff) {
    // 检查是否可以选择m个互不相邻的彩灯，使得极差不超过diff
    // 这里需要更复杂的检查逻辑
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 排序后的数组
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    // 二分答案
    int left = 0, right = sorted_a[n - 1] - sorted_a[0];
    int ans = right;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(n, m, a, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}