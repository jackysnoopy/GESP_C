#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> A(n), B(n), C(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    for (int i = 0; i < n; i++) cin >> C[i];
    // Choose subset of events. Maximize events where some country wins.
    // A country wins if its total > sum of other two.
    // i.e., X > Y+Z or Y > X+Z or Z > X+Y.
    // Maximize number of events selected such that at least one country wins.
    //
    // Binary search on answer k: can we select k events such that some country wins?
    // For country X (Wei): need sum(A[i]*selected) > sum(B[i]*selected) + sum(C[i]*selected)
    //   i.e., sum((A[i]-B[i]-C[i])*selected) > 0
    // Similarly for Y (Shu): sum((B[i]-A[i]-C[i])*selected) > 0
    // Z (Wu): sum((C[i]-A[i]-B[i])*selected) > 0
    //
    // For a given k, to check if X can win:
    //   Select k events maximizing sum((A[i]-B[i]-C[i])*selected).
    //   Sort by (A[i]-B[i]-C[i]) descending, take top k.
    //   If sum > 0, X can win with k events.
    // Do this for all three countries.
    
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        bool ok = false;
        // Check Wei
        {
            vector<long long> vals(n);
            for (int i = 0; i < n; i++) vals[i] = A[i] - B[i] - C[i];
            sort(vals.rbegin(), vals.rend());
            long long sum = 0;
            for (int i = 0; i < mid; i++) sum += vals[i];
            if (sum > 0) ok = true;
        }
        // Check Shu
        if (!ok) {
            vector<long long> vals(n);
            for (int i = 0; i < n; i++) vals[i] = B[i] - A[i] - C[i];
            sort(vals.rbegin(), vals.rend());
            long long sum = 0;
            for (int i = 0; i < mid; i++) sum += vals[i];
            if (sum > 0) ok = true;
        }
        // Check Wu
        if (!ok) {
            vector<long long> vals(n);
            for (int i = 0; i < n; i++) vals[i] = C[i] - A[i] - B[i];
            sort(vals.rbegin(), vals.rend());
            long long sum = 0;
            for (int i = 0; i < mid; i++) sum += vals[i];
            if (sum > 0) ok = true;
        }
        if (ok) lo = mid;
        else hi = mid - 1;
    }
    if (lo == 0) cout << -1 << endl;
    else cout << lo << endl;
    return 0;
}
