#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int,int>> tl(n), br(n);
    for (int i = 0; i < n; i++) cin >> tl[i].first >> tl[i].second;
    for (int i = 0; i < n; i++) cin >> br[i].first >> br[i].second;
    
    // 按行号排序，行号相同按列号排序
    vector<int> oi(n), oj(n);
    for (int i = 0; i < n; i++) oi[i] = i;
    for (int i = 0; i < n; i++) oj[i] = i;
    
    sort(oi.begin(), oi.end(), [&](int a, int b) {
        if (tl[a].first != tl[b].first) return tl[a].first < tl[b].first;
        return tl[a].second < tl[b].second;
    });
    sort(oj.begin(), oj.end(), [&](int a, int b) {
        if (br[a].first != br[b].first) return br[a].first < br[b].first;
        return br[a].second < br[b].second;
    });
    
    // 匹配：对于每个top-left，找最小的包含它的bottom-right
    vector<int> ans(n);
    stack<int> stk;
    int j = 0;
    bool error = false;
    
    for (int ii = 0; ii < n; ii++) {
        int i = oi[ii];
        int r1 = tl[i].first, c1 = tl[i].second;
        
        // 将所有r2 > r1且c2 > c1的bottom-right压入栈
        while (j < n) {
            int k = oj[j];
            int r2 = br[k].first, c2 = br[k].second;
            if (r2 > r1 && c2 > c1) {
                stk.push(k);
                j++;
            } else {
                break;
            }
        }
        
        if (stk.empty()) {
            error = true;
            break;
        }
        
        int k = stk.top();
        stk.pop();
        ans[i] = k;
        
        // 检查嵌套：栈中剩余的bottom-right必须更大
        if (!stk.empty()) {
            int top = stk.top();
            if (br[top].first <= br[k].first || br[top].second <= br[k].second) {
                error = true;
                break;
            }
        }
    }
    
    if (error) {
        cout << "syntax error" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << "\n";
        }
    }
    
    return 0;
}
