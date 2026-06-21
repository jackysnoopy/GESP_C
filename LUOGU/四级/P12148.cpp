#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> pieces(n);
    for (int i = 0; i < n; i++) {
        cin >> pieces[i].first >> pieces[i].second;
    }
    
    sort(pieces.begin(), pieces.end());
    
    // 按列分组
    map<int, vector<int>> col_y;
    for (int i = 0; i < n; i++) {
        col_y[pieces[i].first].push_back(pieces[i].second);
    }
    
    // 收集x坐标
    vector<int> xcoords;
    for (map<int, vector<int>>::iterator it = col_y.begin(); it != col_y.end(); ++it) {
        xcoords.push_back(it->first);
    }
    sort(xcoords.begin(), xcoords.end());
    
    // 对每列的y排序
    for (int i = 0; i < (int)xcoords.size(); i++) {
        sort(col_y[xcoords[i]].begin(), col_y[xcoords[i]].end());
    }
    
    // 最小路径覆盖 = n - 最大匹配
    // 从左到右处理，对于当前列的每个棋子，尝试匹配下一列的棋子
    // 匹配的棋子从"右端点集合"中移除
    
    // 使用set维护每列可匹配的棋子y坐标
    // 从左到右，当前列的棋子作为"左端点"，下一列的棋子作为"右端点"
    
    // 贪心匹配：对于当前列的每个棋子(按y从小到大)，
    // 在下一列中找y-1,y,y+1范围内最小的未匹配棋子
    
    int match_count = 0;
    
    // 记录每列未匹配的棋子（作为右端点）
    map<int, set<int>> available;
    
    for (int idx = 0; idx < (int)xcoords.size(); idx++) {
        int x = xcoords[idx];
        int nx = x + 1;
        
        // 当前列的棋子作为左端点
        vector<int>& ys = col_y[x];
        
        // 下一列可用的右端点
        set<int>& avail = available[nx]; // 初始化为空
        
        for (int i = 0; i < (int)ys.size(); i++) {
            int y = ys[i];
            // 在下一列中找 y-1, y, y+1 范围内最小的未匹配棋子
            for (int dy = -1; dy <= 1; dy++) {
                int ty = y + dy;
                set<int>::iterator it = avail.lower_bound(ty);
                if (it != avail.end() && *it == ty) {
                    avail.erase(it);
                    match_count++;
                    goto done_match;
                }
            }
            // 也尝试 y-1 到 y+1 范围内任意一个
            {
                set<int>::iterator it = avail.lower_bound(y - 1);
                if (it != avail.end() && *it <= y + 1) {
                    avail.erase(it);
                    match_count++;
                    goto done_match;
                }
            }
            done_match:;
        }
        
        // 将下一列的棋子加入available（如果下一列存在）
        if (idx + 1 < (int)xcoords.size() && xcoords[idx + 1] == nx) {
            for (int i = 0; i < (int)col_y[nx].size(); i++) {
                available[nx].insert(col_y[nx][i]);
            }
        }
    }
    
    cout << n - match_count << endl;
    return 0;
}
