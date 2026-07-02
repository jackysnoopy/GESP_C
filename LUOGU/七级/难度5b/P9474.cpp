#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;
int a[100005];
int pos[100005];

bool check(int d) {
    // For each possible minimum value (sorted), check if we can pick m
    // non-adjacent elements within range [a[i], a[i]+d]
    for (int i = 0; i < n; i++) {
        // Try a[i] as minimum, range is [a[i], a[i]+d]
        int cnt = 0;
        int last = -2; // last chosen position
        for (int j = 0; j < n; j++) {
            if (a[j] >= pos[i] && a[j] <= pos[i] + d) {
                if (cnt == 0 || j - last >= 2) {
                    cnt++;
                    last = j;
                    if (cnt >= m) return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    vector<pair<int, int>> vp(n);
    for (int i = 0; i < n; i++) {
        cin >> vp[i].first;
        vp[i].second = i;
    }
    
    sort(vp.begin(), vp.end());
    for (int i = 0; i < n; i++) {
        a[i] = vp[i].first;
        pos[i] = vp[i].second;
    }
    
    // Binary search on the answer
    // But we need to check differently: sorted values, pick m with min gap
    // Key insight: sort by value, then for each starting point, greedily pick
    // non-adjacent (in original position) elements within the range
    
    // Actually, let's reconsider. We sort by value.
    // For each i, let a[i] be the minimum. We want the smallest j such that
    // we can pick m elements from a[i..j] where no two are adjacent in original position.
    
    // Simpler approach: for each starting index i in sorted array,
    // greedily pick elements from i onwards that are non-adjacent in original position
    
    int lo = 0, hi = a[n-1] - a[0];
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        bool ok = false;
        for (int i = 0; i < n && !ok; i++) {
            int cnt = 0;
            int last_pos = -2;
            for (int j = i; j < n && a[j] - a[i] <= mid; j++) {
                if (cnt == 0 || pos[j] - last_pos >= 2) {
                    cnt++;
                    last_pos = pos[j];
                    if (cnt >= m) { ok = true; break; }
                }
            }
        }
        if (ok) hi = mid;
        else lo = mid + 1;
    }
    
    cout << lo << "\n";
    return 0;
}
