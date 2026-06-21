#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;
typedef long long ll;

int T;
string C, J;
int n;

struct Ans {
    ll diff;
    string c, j;
    bool operator<(const Ans& o) const {
        if (diff != o.diff) return diff < o.diff;
        if (c != o.c) return c < o.c;
        return j < o.j;
    }
};

Ans best;

void tryUpdate(const string& tc, const string& tj) {
    ll vc = stoll(tc), vj = stoll(tj);
    ll diff = abs(vc - vj);
    Ans cur = {diff, tc, tj};
    if (cur < best) best = cur;
}

void solve(int tc) {
    cin >> C >> J;
    n = (int)C.size();
    best = {LLONG_MAX, "", ""};
    
    // 情况1：C == J（差=0，最优情况）
    {
        string tc(n, '0'), tj(n, '0');
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (C[i] != '?' && J[i] != '?' && C[i] != J[i]) { ok = false; break; }
            tc[i] = tj[i] = (C[i] != '?' ? C[i] : (J[i] != '?' ? J[i] : '0'));
        }
        if (ok) tryUpdate(tc, tj);
    }
    
    // 情况2&3：在位置pos处C和J开始不同
    for (int pos = 0; pos < n; pos++) {
        string base(n, '0');
        bool ok = true;
        
        // pos之前完全相同
        for (int i = 0; i < pos; i++) {
            if (C[i] != '?' && J[i] != '?' && C[i] != J[i]) { ok = false; break; }
            base[i] = (C[i] != '?' ? C[i] : (J[i] != '?' ? J[i] : '0'));
        }
        if (!ok) continue;
        
        // C[pos] > J[pos]，之后C取小J取大
        for (int cp = 0; cp <= 9; cp++) {
            if (C[pos] != '?' && C[pos] != '0' + cp) continue;
            for (int jp = 0; jp < cp; jp++) {
                if (J[pos] != '?' && J[pos] != '0' + jp) continue;
                string tc2 = base, tj2 = base;
                tc2[pos] = '0' + cp;
                tj2[pos] = '0' + jp;
                for (int i = pos + 1; i < n; i++) {
                    tc2[i] = (C[i] == '?' ? '0' : C[i]);
                    tj2[i] = (J[i] == '?' ? '9' : J[i]);
                }
                tryUpdate(tc2, tj2);
                goto done_cp;
            }
        }
        done_cp:
        
        // C[pos] < J[pos]，之后C取大J取小
        for (int jp = 0; jp <= 9; jp++) {
            if (J[pos] != '?' && J[pos] != '0' + jp) continue;
            for (int cp = 0; cp < jp; cp++) {
                if (C[pos] != '?' && C[pos] != '0' + cp) continue;
                string tc2 = base, tj2 = base;
                tc2[pos] = '0' + cp;
                tj2[pos] = '0' + jp;
                for (int i = pos + 1; i < n; i++) {
                    tc2[i] = (C[i] == '?' ? '9' : C[i]);
                    tj2[i] = (J[i] == '?' ? '0' : J[i]);
                }
                tryUpdate(tc2, tj2);
                goto next_pos;
            }
        }
        next_pos:;
    }
    
    cout << "Case #" << tc << ": " << best.c << " " << best.j << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}
