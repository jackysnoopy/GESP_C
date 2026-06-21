#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, n;
    cin >> T >> n;
    vector<long long> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];
    // Binary search on initial strength S
    // For a given S, check if all equipment can be worn (with some initial spirit)
    // Equipment can be worn in any order. Sort by a[i] ascending.
    // But we also need spirit >= b[i].
    // With S fixed: sort equipment by a[i], greedily wear what we can.
    // Track current strength and spirit.
    // After wearing equipment i, strength += c[i], spirit += d[i].
    // We want to minimize S, then minimize initial spirit.
    
    // For binary search on S:
    // Sort by a[i]. Use priority queue: among all equipment with a[i] <= current strength,
    // pick the one with smallest b[i] (to minimize spirit needed).
    // Actually we want to check: is there a feasible ordering?
    // Greedy: at each step, among all unworn equipment with a[i] <= strength,
    // if any has b[i] <= spirit, wear it (best to wear the one with largest c[i]+d[i]?)
    // Actually the order matters. Let's use: at each step, wear the equipment with
    // smallest a[i] among those we can afford. This maximizes future options.
    
    // Check function: given initial strength S and initial spirit sp, can we wear all?
    auto check = [&](long long S, long long sp) -> bool {
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
        long long str = S, spir = sp;
        vector<bool> used(n, false);
        for (int round = 0; round < n; round++) {
            int best = -1;
            for (int j = 0; j < n; j++) {
                int i = idx[j];
                if (!used[i] && a[i] <= str && b[i] <= spir) {
                    best = i;
                    break;
                }
            }
            if (best == -1) {
                // Try any wearable
                for (int i = 0; i < n; i++) {
                    if (!used[i] && a[i] <= str && b[i] <= spir) {
                        best = i;
                        break;
                    }
                }
            }
            if (best == -1) return false;
            used[best] = true;
            str += c[best];
            spir += d[best];
        }
        return true;
    };
    
    // Binary search on S (strength)
    long long loS = 0, hiS = 1e18;
    while (loS < hiS) {
        long long midS = (loS + hiS) / 2;
        // Check if there exists a spirit value that works
        // Binary search on spirit too
        long long loSp = 0, hiSp = 1e18;
        bool found = false;
        while (loSp <= hiSp) {
            long long midSp = (loSp + hiSp) / 2;
            if (check(midS, midSp)) { found = true; hiSp = midSp - 1; }
            else loSp = midSp + 1;
        }
        if (found) hiS = midS;
        else loS = midS + 1;
    }
    
    long long minS = loS;
    // Find min spirit for this strength
    long long loSp = 0, hiSp = 1e18;
    while (loSp < hiSp) {
        long long midSp = (loSp + hiSp) / 2;
        if (check(minS, midSp)) hiSp = midSp;
        else loSp = midSp + 1;
    }
    
    cout << minS << " " << loSp << endl;
    return 0;
}
