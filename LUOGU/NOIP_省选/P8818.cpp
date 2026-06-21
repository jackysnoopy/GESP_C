#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    vector<long long> A(n), B(m);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < m; i++) cin >> B[i];
    
    int LOG = 1;
    while ((1 << LOG) <= max(n, m)) LOG++;
    
    // Sparse tables for A: 5 types
    // 0=max, 1=min, 2=maxNeg, 3=minPos, 4=hasZero (max, 0 or 1)
    vector<vector<long long>> ast[5];
    for (int t = 0; t < 5; t++) ast[t].resize(LOG, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        ast[0][0][i] = A[i];
        ast[1][0][i] = A[i];
        ast[2][0][i] = (A[i] < 0 ? A[i] : LLONG_MIN);
        ast[3][0][i] = (A[i] > 0 ? A[i] : LLONG_MAX);
        ast[4][0][i] = (A[i] == 0 ? 1 : 0);
    }
    for (int t = 0; t < 5; t++) {
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                if (t == 0 || t == 2 || t == 4)
                    ast[t][k][i] = max(ast[t][k-1][i], ast[t][k-1][i + (1 << (k-1))]);
                else
                    ast[t][k][i] = min(ast[t][k-1][i], ast[t][k-1][i + (1 << (k-1))]);
            }
        }
    }
    
    vector<vector<long long>> bst[2];
    for (int t = 0; t < 2; t++) bst[t].resize(LOG, vector<long long>(m));
    for (int i = 0; i < m; i++) { bst[0][0][i] = B[i]; bst[1][0][i] = B[i]; }
    for (int t = 0; t < 2; t++) {
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i + (1 << k) <= m; i++) {
                if (t == 0) bst[t][k][i] = max(bst[t][k-1][i], bst[t][k-1][i + (1 << (k-1))]);
                else bst[t][k][i] = min(bst[t][k-1][i], bst[t][k-1][i + (1 << (k-1))]);
            }
        }
    }
    
    auto qmax = [](vector<vector<long long>>& st, int l, int r) -> long long {
        int k = 31 - __builtin_clz(r - l + 1);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    };
    auto qmin = [](vector<vector<long long>>& st, int l, int r) -> long long {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    };
    
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--; r1--; l2--; r2--;
        
        long long aMax = qmax(ast[0], l1, r1);
        long long aMin = qmin(ast[1], l1, r1);
        long long aMaxNeg = qmax(ast[2], l1, r1);
        long long aMinPos = qmin(ast[3], l1, r1);
        long long hasZero = qmax(ast[4], l1, r1);
        long long bMax = qmax(bst[0], l2, r2);
        long long bMin = qmin(bst[1], l2, r2);
        
        long long best = LLONG_MIN;
        if (aMinPos != LLONG_MAX) {
            if (bMin >= 0) best = max(best, aMax * bMin);
            else best = max(best, aMinPos * bMin);
        }
        if (aMaxNeg != LLONG_MIN) {
            if (bMax >= 0) best = max(best, aMaxNeg * bMax);
            else best = max(best, aMin * bMax);
        }
        if (hasZero) best = max(best, 0LL);
        // If no positive, negative, or zero A, this shouldn't happen
        if (best == LLONG_MIN) best = 0;
        
        cout << best << "\n";
    }
    return 0;
}
