#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N, M, K; cin >> N >> M >> K;
    vector<int> order(M);
    for (int i = 0; i < M; i++) cin >> order[i];
    vector<int> pos(N + 1, -1); // fixed position for each cow
    for (int i = 0; i < K; i++) { int c, p; cin >> c >> p; pos[c] = p; }
    // Binary search: can cow 1 be at position x?
    // For position x, check if all constraints can be satisfied with cow 1 at x.
    // Constraints: order must be preserved, fixed positions must be respected.
    // Cow 1 is at position x. Fill positions 1..N with cows.
    // Greedy: fill from position 1 to N. At each position, put the earliest available cow
    // that doesn't violate constraints.
    auto canPlace = [&](int x) -> bool {
        vector<int> result(N + 1, 0);
        if (pos[1] != -1 && pos[1] != x) return false;
        result[x] = 1;
        vector<bool> used(N + 1, false);
        used[1] = true;
        // Fill fixed positions first
        for (int i = 1; i <= N; i++) {
            if (pos[i] != -1) {
                if (result[pos[i]] != 0 && result[pos[i]] != i) return false;
                if (used[i]) return false;
                result[pos[i]] = i;
                used[i] = true;
            }
        }
        // Fill remaining positions greedily
        int ordIdx = 0;
        for (int p = 1; p <= N; p++) {
            if (result[p] != 0) {
                // Check order constraint: all cows before this in order must be placed before p
                while (ordIdx < M && used[order[ordIdx]]) ordIdx++;
                if (ordIdx < M && order[ordIdx] == result[p]) ordIdx++;
                continue;
            }
            // Find the earliest available cow that can go here
            bool found = false;
            for (int i = 1; i <= N; i++) {
                if (used[i]) continue;
                // Check if placing cow i here violates any constraint
                // Order: all cows before i in order must be placed before this position
                bool ok = true;
                // Check if any cow that must come before i is not yet placed
                for (int j = 0; j < M; j++) {
                    if (order[j] == i) break;
                    if (!used[order[j]]) { ok = false; break; }
                }
                if (!ok) continue;
                // Check fixed position
                if (pos[i] != -1 && pos[i] != p) continue;
                result[p] = i;
                used[i] = true;
                found = true;
                break;
            }
            if (!found) return false;
        }
        return true;
    };
    // Binary search for minimum position
    // Actually, we want the EARLIEST position for cow 1.
    // Binary search: can cow 1 be at position x?
    // If yes, try smaller. If no, try larger.
    // But the constraint says cow 1 must be before certain cows in order.
    // So the minimum position is at least 1 + (number of cows before cow 1 in order that have fixed positions).
    // Let me just binary search.
    int lo = 1, hi = N, ans = N;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (canPlace(mid)) { ans = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    cout << ans << "\n";
    return 0;
}
