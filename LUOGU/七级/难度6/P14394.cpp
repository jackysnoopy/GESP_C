#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200005;

int n;
pair<int, int> dolls[MAXN];
int q;
pair<int, int> queries[MAXN];
int ans[MAXN];

// BIT for LIS
int bit[MAXN];

void update(int x, int val) {
    for (; x < MAXN; x += x & (-x))
        bit[x] = max(bit[x], val);
}

int query(int x) {
    int res = 0;
    for (; x > 0; x -= x & (-x))
        res = max(res, bit[x]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> q;
    
    for (int i = 0; i < n; i++) {
        cin >> dolls[i].first >> dolls[i].second;
    }
    
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].second = i;
    }
    
    // Sort dolls by R descending, then by H ascending
    // Sort queries by A descending
    
    // For each query (A, B), we need dolls with R >= A and H <= B
    // Among these dolls, we want the maximum matching where each doll can be nested in another
    // (R_i > R_j and H_i > H_j)
    
    // This is equivalent to finding LIS on the filtered dolls sorted by R
    
    // Offline approach: sort both by threshold
    vector<int> dollOrder(n);
    for (int i = 0; i < n; i++) dollOrder[i] = i;
    sort(dollOrder.begin(), dollOrder.end(), [&](int i, int j) {
        if (dolls[i].first != dolls[j].first) return dolls[i].first > dolls[j].first;
        return dolls[i].second < dolls[j].second;
    });
    
    vector<int> queryOrder(q);
    for (int i = 0; i < q; i++) queryOrder[i] = i;
    sort(queryOrder.begin(), queryOrder.end(), [&](int i, int j) {
        return queries[i].first > queries[j].first;
    });
    
    memset(bit, 0, sizeof(bit));
    
    int ptr = 0;
    for (int qi = 0; qi < q; qi++) {
        int idx = queryOrder[qi];
        int A = queries[idx].first;
        int B = queries[idx].second;
        
        // Add dolls with R >= A
        while (ptr < n && dolls[dollOrder[ptr]].first >= A) {
            int d = dollOrder[ptr];
            if (dolls[d].second <= B) {
                // LIS update: use H as index
                int lis = query(dolls[d].second - 1) + 1;
                update(dolls[d].second, lis);
            }
            ptr++;
        }
        
        // Query LIS for H <= B
        ans[idx] = query(B);
    }
    
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
