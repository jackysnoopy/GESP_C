#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

static long long N;
static int A, B;
static vector<int> digits;
static const int LMAX = 20;
static long long dp[LMAX][2][2][LMAX][LMAX];
static const long long INF = (long long)1e18;

static long long dfs(int pos, int tight, int started, int ua, int ub) {
    if (ua > A || ub > B) return -INF;
    if (pos == (int)digits.size()) return started ? 0 : -INF;
    long long &res = dp[pos][tight][started][ua][ub];
    if (res != -1) return res;
    res = -INF;
    int up = tight ? digits[pos] : 9;
    for (int nd = 0; nd <= up; ++nd) {
        int ntight = tight && (nd == up);
        int nstarted = started || (nd != 0);
        if (!nstarted) {
            long long sub = dfs(pos + 1, ntight, 0, ua, ub);
            if (sub > res) res = sub;
            continue;
        }
        for (int delta = 0; delta <= 9; ++delta) {
            if (delta == 0) {
                int nua = ua + (nd == 9 ? 1 : 0);
                int nub = ub + (nd == 0 ? 1 : 0);
                long long sub = dfs(pos + 1, ntight, 1, nua, nub);
                if (sub > -INF / 2) {
                    long long cur = sub * 10 + nd;
                    if (cur > res) res = cur;
                }
            } else {
                int nua = ua + (delta == 1 ? 1 : 0);
                int nub = ub + (delta == 1 ? 1 : 0);
                long long sub = dfs(pos + 1, ntight, 1, nua, nub);
                if (sub > -INF / 2) {
                    int nd2 = nd + delta;
                    if (nd2 >= 10) nd2 -= 10;
                    long long cur = sub * 10 + nd2;
                    if (cur > res) res = cur;
                }
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> A >> B;
    for (long long t = N; t > 0; t /= 10) digits.push_back((int)(t % 10));
    if (N == 0) digits.push_back(0);
    reverse(digits.begin(), digits.end());
    memset(dp, 0xff, sizeof(dp));
    cout << dfs(0, 1, 0, 0, 0) << '\n';
    return 0;
}
