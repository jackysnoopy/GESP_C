#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int c, p; cin >> c >> p;
    vector<long long> m(c), s(c);
    for (int i = 0; i < c; i++) cin >> m[i] >> s[i];
    vector<long long> q(p), d(p);
    for (int i = 0; i < p; i++) cin >> q[i] >> d[i];
    // Greedy: sort contests by satisfaction descending.
    // For each contest, find the best (lowest cost) problem that qualifies.
    // But this is a matching problem. Use greedy matching.
    // Sort problems by quality descending. Sort contests by min quality descending.
    // For each problem, find the best contest it can go to.
    // Or: for each contest, find the best problem.
    //
    // Better: sort contests by s[i] descending. For each contest, pick the
    // cheapest qualifying problem.
    vector<int> cidx(c), pidx(p);
    for (int i = 0; i < c; i++) cidx[i] = i;
    for (int i = 0; i < p; i++) pidx[i] = i;
    sort(cidx.begin(), cidx.end(), [&](int i, int j) { return s[i] > s[j]; });
    sort(pidx.begin(), pidx.end(), [&](int i, int j) { return q[i] < q[j]; });
    
    vector<bool> used(p, false);
    long long total = 0;
    for (int ci : cidx) {
        // Find cheapest qualifying unused problem
        long long best = 0;
        int bestIdx = -1;
        for (int pi : pidx) {
            if (used[pi]) continue;
            if (q[pi] >= m[ci]) {
                long long gain = s[ci] - d[pi];
                if (gain > best || (gain == best && bestIdx == -1)) {
                    best = gain;
                    bestIdx = pi;
                }
            }
        }
        if (best > 0 && bestIdx >= 0) {
            total += best;
            used[bestIdx] = true;
        }
    }
    if (total < 0) total = 0;
    cout << total << "\n";
    return 0;
}
