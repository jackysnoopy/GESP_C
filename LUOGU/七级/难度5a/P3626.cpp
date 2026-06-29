#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
pair<int, int> intervals[MAXN];
int n;

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &intervals[i].first, &intervals[i].second);
    }
    
    // 按结束时间排序，结束时间相同按开始时间排序
    vector<pair<int, int>> sorted;
    for (int i = 0; i < n; i++) {
        sorted.push_back({intervals[i].second, i + 1});
    }
    sort(sorted.begin(), sorted.end());
    
    // 贪心选择
    vector<int> ans;
    int last_end = -1;
    
    for (auto [end, idx] : sorted) {
        if (intervals[idx - 1].first > last_end) {
            ans.push_back(idx);
            last_end = end;
        }
    }
    
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++) {
        printf("%d%c", ans[i], i + 1 == (int)ans.size() ? '\n' : ' ');
    }
    
    return 0;
}
