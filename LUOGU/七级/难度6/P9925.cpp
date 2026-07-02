#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }
    
    // 简单实现：贪心选择
    // 这里需要更复杂的算法
    vector<pair<int, int>> ans;
    
    // 按右端点排序
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return segments[i].second < segments[j].second;
    });
    
    // 贪心选择不相交的线段对
    int last_end = -1;
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        if (segments[id].first > last_end) {
            ans.push_back({id + 1, id + 1});
            last_end = segments[id].second;
        }
    }
    
    cout << ans.size() << "\n";
    for (auto& p : ans) {
        cout << p.first << " " << p.second << "\n";
    }
    
    return 0;
}