#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> p(n), w(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> w[i];
    // Choose k people. Upgrade them to same p value.
    // For each possible target p value, compute cost.
    // Sort by p. For each person as the target (or each distinct p value):
    // The target must be >= max(p of selected k people).
    // Cost = sum of w[i] * (target - p[i]) for each selected person.
    // 
    // Strategy: sort by p descending. For each person j as the highest:
    // Target = p[j]. Need k-1 more people with p[i] <= p[j].
    // Choose k-1 cheapest to upgrade (smallest w[i]).
    // 
    // Actually: for target = p[j], select k people including j where p[i] <= p[j].
    // Cost = sum of w[i] * (p[j] - p[i]) for selected.
    // = p[j] * sum(w[i]) - sum(w[i] * p[i])
    // To minimize: choose k people with smallest w[i] among those with p[i] <= p[j].
    
    // Sort indices by p descending
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return p[a] > p[b]; });
    
    long long ans = (long long)1e18;
    vector<int> selected; // indices of selected people (sorted by w ascending)
    
    for (int i = 0; i < n; i++) {
        int j = idx[i];
        selected.push_back(j);
        if ((int)selected.size() > k) {
            // Remove the one with largest w
            int worst = 0;
            for (int x = 1; x < (int)selected.size(); x++) {
                if (w[selected[x]] > w[selected[worst]]) worst = x;
            }
            selected.erase(selected.begin() + worst);
        }
        if ((int)selected.size() == k) {
            long long cost = 0;
            for (int x = 0; x < k; x++) {
                cost += (long long)w[selected[x]] * (p[j] - p[selected[x]]);
            }
            ans = min(ans, cost);
        }
    }
    cout << ans << "\n";
    return 0;
}
