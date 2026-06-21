#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    ll k;
    cin >> n >> s >> k;

    vector<ll> d(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> d[i];

    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    // 前缀和：位置和重要性（1-indexed）
    vector<ll> pos(n + 1, 0);
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pos[i + 1] = pos[i] + (i < n - 1 ? d[i] : 0);
        pref[i + 1] = pref[i] + v[i];
    }

    // g[i]：从i开始放一个防护盾能覆盖到的最远舱室（1-indexed）
    vector<int> g(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        // 能覆盖pos[i]的最右舱室x：pos[x] <= pos[i]+K
        ll limit = pos[i] + k;
        int x = (int)(upper_bound(pos.begin() + 1, pos.begin() + n + 1, limit) - pos.begin() - 1);
        // 防护盾放在x，覆盖到pos[x]+K
        ll cover = pos[x] + k;
        g[i] = (int)(upper_bound(pos.begin() + 1, pos.begin() + n + 1, cover) - pos.begin() - 1);
    }
    g[n + 1] = n;

    // 倍增预处理
    // next_pos[i] = g[i]+1（放一个防护盾后的下一个未覆盖位置）
    // jump[j][i] = 从i开始放2^j个防护盾后的下一个未覆盖位置
    int LOG = 21;
    vector<vector<int>> jump(LOG, vector<int>(n + 2));
    for (int i = 1; i <= n + 1; i++) {
        jump[0][i] = min(g[i] + 1, n + 1);
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n + 1; i++) {
            jump[j][i] = jump[j - 1][jump[j - 1][i]];
        }
    }

    // 对于每个起始位置i，计算放s个防护盾能覆盖到的最远舱室
    ll ans_sum = 0;
    int ans_l = 1, ans_r = 1;

    for (int i = 1; i <= n; i++) {
        int cur = i;
        int rem = s;
        for (int j = LOG - 1; j >= 0; j--) {
            if (rem >= (1 << j)) {
                cur = jump[j][cur];
                rem -= (1 << j);
            }
        }
        int r = cur - 1; // 覆盖到cur-1
        if (r < i) r = i - 1; // 至少覆盖0个（但区间不能为空）
        ll sum = pref[r] - pref[i - 1];
        if (sum > ans_sum) {
            ans_sum = sum;
            ans_l = i;
            ans_r = r;
        }
    }

    // 贪心放置防护盾
    vector<int> shields;
    int cur_pos = ans_l;
    while (cur_pos <= ans_r && (int)shields.size() < s) {
        shields.push_back(cur_pos);
        cur_pos = g[cur_pos] + 1;
    }

    cout << shields.size() << "\n";
    for (int i = 0; i < (int)shields.size(); i++) {
        if (i > 0) cout << " ";
        cout << shields[i];
    }
    cout << "\n";

    return 0;
}
