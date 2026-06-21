#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, e, n;
    cin >> k >> e >> n;
    // FJ travels from 0 to E. Buys K tons total.
    // Store i: position X_i, price C_i per ton, at most F_i tons.
    // Transport cost: D * X (D = distance traveled, X = current load).
    // FJ can buy at any store along the way.
    //
    // Greedy: buy from cheapest store first (considering transport cost).
    // But transport cost depends on when you buy.
    // 
    // Key insight: buying at position x costs C_i + (E - x) in transport per ton.
    // Because after buying at x, you carry it E-x more distance.
    // Wait: you travel from 0 to E. If you buy at position x, you carry it E-x distance.
    // Transport cost per ton = (E - x). Total cost per ton = C_i + (E - x).
    //
    // Actually: transport cost is distance traveled times current load.
    // If you buy at x, the ton is carried from x to E: E-x distance.
    // So effective price per ton = C_i + (E - x).
    // But this ignores that you're already carrying other stuff.
    // Actually: total transport = sum over all tons of (distance carried).
    // Each ton bought at x is carried E-x distance.
    // Total = sum(C_i * amount_i) + sum((E - x_i) * amount_i).
    // = sum((C_i + E - x_i) * amount_i).
    //
    // So minimize: buy cheapest effective price first.
    
    vector<tuple<int,int,int>> stores(n); // (effective_price, x, f)
    for (int i = 0; i < n; i++) {
        int x, f, c;
        cin >> x >> f >> c;
        stores[i] = make_tuple(c + e - x, x, f);
    }
    sort(stores.begin(), stores.end());
    long long ans = 0;
    int remaining = k;
    for (int i = 0; i < n && remaining > 0; i++) {
        int price = get<0>(stores[i]);
        int avail = get<2>(stores[i]);
        int buy = min(remaining, avail);
        ans += (long long)buy * price;
        remaining -= buy;
    }
    cout << ans << "\n";
    return 0;
}
