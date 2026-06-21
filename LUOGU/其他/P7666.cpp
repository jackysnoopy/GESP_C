#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    // Total time if one match = t[n-1]+1 - t[0]
    // With K matches, we save the K-1 largest gaps between consecutive客人
    long long total = t[n-1] + 1 - t[0];
    vector<int> gaps;
    for (int i = 1; i < n; i++) {
        gaps.push_back(t[i] - t[i-1] - 1);
    }
    sort(gaps.begin(), gaps.end(), greater<int>());
    long long saved = 0;
    for (int i = 0; i < k - 1 && i < (int)gaps.size(); i++) {
        saved += gaps[i];
    }
    cout << total - saved << "\n";
    return 0;
}
