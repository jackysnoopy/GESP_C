#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<long long> b(m), c(m), k(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> k[i];
    }
    
    // Calculate perimeter for each leaf
    vector<long long> perimeter(m);
    for (int i = 0; i < m; i++) {
        perimeter[i] = k[i] * b[i];
    }
    
    // Sort pens by capacity
    vector<long long> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    // Sort leaves by perimeter
    vector<pair<long long, long long>> leaves(m);
    for (int i = 0; i < m; i++) {
        leaves[i] = {perimeter[i], c[i]};
    }
    sort(leaves.begin(), leaves.end());
    
    // Greedy matching for maximum count
    int count = 0;
    int pen_idx = 0;
    
    for (int i = 0; i < m && pen_idx < n; i++) {
        while (pen_idx < n && sorted_a[pen_idx] < leaves[i].first) {
            pen_idx++;
        }
        if (pen_idx < n) {
            count++;
            pen_idx++;
        }
    }
    
    cout << count << endl;
    
    // For maximum beauty, use different strategy
    long long beauty = 0;
    vector<pair<long long, int>> leaves_with_idx(m);
    for (int i = 0; i < m; i++) {
        leaves_with_idx[i] = {perimeter[i], i};
    }
    sort(leaves_with_idx.begin(), leaves_with_idx.end());
    
    vector<bool> used(n, false);
    for (int i = 0; i < m; i++) {
        int leaf_idx = leaves_with_idx[i].second;
        for (int j = 0; j < n; j++) {
            if (!used[j] && a[j] >= perimeter[leaf_idx]) {
                used[j] = true;
                beauty += c[leaf_idx];
                break;
            }
        }
    }
    
    cout << beauty << endl;
    
    return 0;
}