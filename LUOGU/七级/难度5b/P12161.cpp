#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    // 天数索引从1开始
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;
    // 按p[i]升序排序
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return p[a] < p[b];
    });
    
    // 两个multiset：left存储P_i < x的天数索引，right存储P_i >= x的天数索引
    multiset<int> left, right;
    // 初始时，right包含所有天数索引
    for (int i = 0; i < n; ++i) right.insert(i);
    
    long long ans = 0;
    int pos = 0; // 指向第一个P_i >= x的天数
    
    // 从大到小遍历数字x (x从n到1)
    for (int x = n; x >= 1; --x) {
        // 移动pos，使得indices[0..pos-1]的P_i < x
        while (pos < n && p[indices[pos]] < x) {
            // 将indices[pos]从right移到left
            right.erase(right.find(indices[pos]));
            left.insert(indices[pos]);
            ++pos;
        }
        
        // 现在left中都是P_i < x的天数，right中都是P_i >= x的天数
        long long best = -1e18;
        int best_idx = -1;
        bool from_left = false;
        
        // 从left中选择i最大的
        if (!left.empty()) {
            auto it = left.end();
            --it;
            int i = *it;
            long long contrib = i + 1; // 天数索引从0开始，实际天数为i+1
            if (contrib > best) {
                best = contrib;
                best_idx = i;
                from_left = true;
            }
        }
        
        // 从right中选择i最小的
        if (!right.empty()) {
            int i = *right.begin();
            long long contrib = -(i + 1); // 贡献为负
            // 如果p[i] == x，贡献为0
            if (p[i] == x) contrib = 0;
            if (contrib > best) {
                best = contrib;
                best_idx = i;
                from_left = false;
            }
        }
        
        // 选择贡献最大的
        ans += best;
        // 删除选中的天数
        if (from_left) {
            left.erase(left.find(best_idx));
        } else {
            right.erase(right.find(best_idx));
        }
    }
    
    cout << ans << endl;
    return 0;
}