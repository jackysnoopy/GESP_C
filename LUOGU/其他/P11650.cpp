#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long D, X;
    cin >> n >> D >> X;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> y[i];
    // Greedy with priority queue.
    // Walk from 0 to X. At each restaurant, we can choose to eat or not.
    // We want to minimize the number of restaurants visited.
    // Strategy: walk as far as possible, then eat at the restaurant that gives
    // the most energy, to walk further.
    //
    // Greedy: sort restaurants by position.
    // Walk from 0. When energy runs out, eat at the best available restaurant.
    // But we want to minimize the number of restaurants, not maximize energy.
    //
    // Better: binary search on the number of restaurants k.
    // For a given k: can we reach X using at most k restaurants?
    // Greedy: use the k restaurants with the largest y values that are reachable.
    //
    // Or: greedy simulation.
    // Walk forward. When energy is about to run out, eat at the best available restaurant.
    // This minimizes the number of restaurants because we only eat when necessary.
    
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) { return x[i] < x[j]; });
    
    long long energy = D;
    int pos = 0; // index in sorted order
    int count = 0;
    priority_queue<long long> available;
    
    while (energy < X) {
        // Add all restaurants we've passed
        while (pos < n && x[order[pos]] <= energy) {
            available.push(y[order[pos]]);
            pos++;
        }
        if (available.empty()) {
            cout << -1 << "\n";
            return 0;
        }
        // Eat at the best restaurant
        energy += available.top();
        available.pop();
        count++;
        if (count > n) { cout << -1 << "\n"; return 0; }
    }
    cout << count << "\n";
    return 0;
}
