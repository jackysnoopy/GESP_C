#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<int, int>> a(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < n; i++) cin >> c[i].first >> c[i].second;
    
    // Sort a by score descending, c by score descending
    sort(a.begin(), a.end(), [](const pair<int,int>& x, const pair<int,int>& y) {
        return x.second > y.second;
    });
    sort(c.begin(), c.end(), [](const pair<int,int>& x, const pair<int,int>& y) {
        return x.second > y.second;
    });
    
    // For each player in a (sorted by score desc), find matching player in c
    // A player from a at position i can match player from c at position j if:
    // 1. a[i].second <= c[j].second (score constraint)
    // 2. The country can be matched (either already same, or we modify)
    
    // We want to maximize the number of matches where a[i].country == c[j].country
    // (no modification needed)
    
    // Greedy: for each a[i], try to find c[j] with same country and D[j] >= B[i]
    // Use two pointers or set
    
    // Actually, we need to find maximum matching where:
    // - a[i] matches c[j] (permutation)
    // - B[i] <= D[j]
    // - A[i] == C[j] (no modification)
    
    // The answer is N - (maximum number of matches without modification)
    
    // Use greedy with priority queue
    vector<vector<int>> cByScore(n + 1); // cByScore[d] = list of indices with score d
    vector<int> cIdx(n); // cIdx[i] = index in sorted c array
    
    // For each a[i], find the c[j] with same country and minimum score >= B[i]
    // This is a matching problem
    
    // Simpler approach: iterate through a from highest score to lowest
    // For each a[i], find the best c[j] to match (same country, D[j] >= B[i])
    
    vector<int> matched(n, 0);
    int ans = 0;
    
    // Sort by score descending, for ties sort by country
    // Use greedy: for each a player (high to low score), match with c player of same country if possible
    
    // Actually, let's think differently
    // The key insight: we want to maximize matches where countries are the same
    // For each country, count how many a players and c players have that country
    // But we also need D[j] >= B[i]
    
    // Use a multiset for each country's c players' scores
    vector<multiset<int>> cScores(n + 1);
    for (int i = 0; i < n; i++) {
        cScores[c[i].first].insert(c[i].second);
    }
    
    // Sort a by score descending
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) {
        return a[i].second > a[j].second;
    });
    
    for (int i : order) {
        int country = a[i].first;
        int score = a[i].second;
        
        // Find c player with same country and D >= score
        auto it = cScores[country].lower_bound(score);
        if (it != cScores[country].end()) {
            ans++;
            cScores[country].erase(it);
        }
    }
    
    cout << n - ans << "\n";
    return 0;
}
