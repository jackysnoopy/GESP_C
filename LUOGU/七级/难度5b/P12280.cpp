#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;
int a[MAXN];
int right_len[MAXN]; // right_len[i]表示从i开始的最长无重复子数组长度
bool vis[MAXN]; // 用于检查重复

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    // 预处理right_len
    memset(vis, false, sizeof(vis));
    int r = n;
    for (int i = n; i >= 1; --i) {
        while (r >= i && !vis[a[r]]) {
            vis[a[r]] = true;
            --r;
        }
        right_len[i] = r - i + 1;
        // 移动窗口：移除i位置的元素
        vis[a[i]] = false;
    }
    
    // 枚举前缀右端点i
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i <= n; ++i) {
        // 前缀为a[1..i]，后缀为a[j..n]
        // 我们需要找最小的j>i使得a[j]在a[1..i]中出现
        // 但为了简化，我们尝试所有可能的j
        // 这里使用暴力枚举j，对于大数据可能超时
        int j = i + 1;
        while (j <= n && !vis[a[j]]) {
            ++j;
        }
        // 现在j是第一个使得a[j]在a[1..i]中出现的位置，或者j=n+1
        // 后缀可以从j+1开始，但需要确保后缀内部无重复
        int suffix_start = j + 1;
        if (suffix_start <= n) {
            int suffix_len = right_len[suffix_start];
            ans = max(ans, i + suffix_len);
        } else {
            // 后缀为空
            ans = max(ans, i);
        }
        
        // 将a[i+1]加入前缀（如果i+1<=n）
        if (i + 1 <= n) {
            if (vis[a[i+1]]) {
                // 前缀出现重复，不能继续增加i
                break;
            }
            vis[a[i+1]] = true;
        }
    }
    
    cout << ans << endl;
    return 0;
}