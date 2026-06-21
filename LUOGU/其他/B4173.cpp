#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;
int n;
int ls_[MAXN], rs_[MAXN], par_[MAXN];
int pre_[MAXN], sz_[MAXN], tin_[MAXN], tout_[MAXN], timer_;
int curN;

void calcPre(int u) {
    if (u == 0) return;
    pre_[curN++] = u;
    calcPre(ls_[u]);
    calcPre(rs_[u]);
}

void calcSz(int u) {
    if (u == 0) { sz_[u] = 0; return; }
    tin_[u] = timer_++;
    sz_[u] = 1;
    calcSz(ls_[u]);
    calcSz(rs_[u]);
    sz_[u] += sz_[ls_[u]] + sz_[rs_[u]];
    tout_[u] = timer_;
}

bool isDesc(int u, int v) {
    return tin_[v] >= tin_[u] && tout_[v] <= tout_[u];
}

void solve() {
    cin >> n;
    memset(ls_ + 1, 0, sizeof(int) * n);
    memset(rs_ + 1, 0, sizeof(int) * n);
    memset(par_ + 1, 0, sizeof(int) * n);
    for (int i = 1; i <= n; i++) {
        cin >> ls_[i] >> rs_[i];
        if (ls_[i]) par_[ls_[i]] = i;
        if (rs_[i]) par_[rs_[i]] = i;
    }
    
    timer_ = 0;
    calcSz(1);
    curN = 0; calcPre(1);
    vector<int> origPre(pre_, pre_ + n);
    vector<int> bestPre = origPre;
    
    vector<pair<int,int>> slots;
    for (int i = 1; i <= n; i++) {
        if (ls_[i] == 0) slots.push_back({i, 0});
        if (rs_[i] == 0) slots.push_back({i, 1});
    }
    
    int saveLs[MAXN], saveRs[MAXN], savePar[MAXN];
    memcpy(saveLs, ls_, sizeof(int) * (n + 1));
    memcpy(saveRs, rs_, sizeof(int) * (n + 1));
    memcpy(savePar, par_, sizeof(int) * (n + 1));
    
    for (int v = 2; v <= n; v++) {
        for (size_t si = 0; si < slots.size(); si++) {
            int p = slots[si].first;
            int side = slots[si].second;
            
            if (p == v) continue;
            if (side == 0 && ls_[p] == v) continue;
            if (side == 1 && rs_[p] == v) continue;
            // Cycle check: p must not be in v's subtree
            if (isDesc(v, p)) continue;
            
            int vPar = par_[v];
            if (ls_[vPar] == v) ls_[vPar] = 0;
            else if (rs_[vPar] == v) rs_[vPar] = 0;
            else continue;
            
            if (side == 0) ls_[p] = v;
            else rs_[p] = v;
            par_[v] = p;
            
            curN = 0; calcPre(1);
            if (curN == n) {
                vector<int> newPre(pre_, pre_ + curN);
                if (newPre < bestPre) {
                    bestPre = newPre;
                }
            }
            
            memcpy(ls_, saveLs, sizeof(int) * (n + 1));
            memcpy(rs_, saveRs, sizeof(int) * (n + 1));
            memcpy(par_, savePar, sizeof(int) * (n + 1));
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << bestPre[i] << (i + 1 < n ? ' ' : '\n');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
