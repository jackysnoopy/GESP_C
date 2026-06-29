#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, pi;
    cin >> n >> pi;
    
    vector<int> normal;
    vector<pair<int, int>> magic;
    
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a;
        if (cin.peek() == '\n' || cin.eof()) {
            normal.push_back(a);
        } else {
            cin >> b;
            magic.push_back({a, b});
        }
    }
    
    int normal_sum = 0;
    for (int v : normal) normal_sum += v;
    
    int magic_sum = 0;
    for (auto& p : magic) magic_sum += p.first;
    
    int m = magic.size();
    vector<int> dp(pi + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int p1 = magic[i].first;
        int p2 = magic[i].second;
        int gain = p2 - p1 - pi;
        
        if (gain <= 0) continue;
        
        for (int j = pi; j >= 1; j--) {
            dp[j] = max(dp[j], dp[j - 1] + gain);
        }
    }
    
    int best = 0;
    for (int j = 0; j <= pi; j++) {
        best = max(best, dp[j]);
    }
    
    cout << normal_sum + magic_sum + best << "\n";
    return 0;
}
