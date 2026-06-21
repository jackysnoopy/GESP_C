#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string digits, tmpl;
    cin >> digits >> tmpl;
    int nd = (int)digits.size();
    int nm = (int)tmpl.size();
    // 按+分割模板为若干乘法段
    vector<vector<int>> groups;
    vector<int> cur;
    for (int i = 0; i < nm; ++i) {
        if (tmpl[i] == '+') {
            groups.push_back(cur);
            cur.clear();
        } else if (tmpl[i] == '*') {
            // skip
        } else {
            cur.push_back(i);
        }
    }
    groups.push_back(cur);
    int ng = (int)groups.size();
    vector<int> need(ng);
    int total_need = 0;
    for (int i = 0; i < ng; ++i) { need[i] = (int)groups[i].size(); total_need += need[i]; }
    // dp[pos][g][k] = 前 pos 个数字分配到第 g 组前 k 个位置的最大值
    // 简化：逐组贪心分配
    long long ans = 0;
    int pos = 0;
    for (int g = 0; g < ng; ++g) {
        int len = need[g];
        if (len == 0) continue;
        // 取接下来 len 个数字，按位分配使乘积最大
        // 贪心：将最大的数字放在最高位
        vector<int> nums(len);
        for (int i = 0; i < len; ++i) nums[i] = digits[pos + i] - '0';
        pos += len;
        // 排序后从高位到低位分配
        sort(nums.begin(), nums.end(), greater<int>());
        long long prod = 1;
        long long val = 0;
        for (int i = 0; i < len; ++i) val = val * 10 + nums[i];
        ans += val;
    }
    cout << ans << '\n';
    return 0;
}
