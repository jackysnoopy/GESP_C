#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, P;
    cin >> n >> P;
    vector<int> a(n+1), b(n+1);
    long long fuel = 0;
    vector<int> gain, cost;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        if (i == P) {
            fuel += a[i];
            continue;
        }
        if (a[i] >= b[i]) {
            gain.push_back(a[i] - b[i]);
        } else {
            cost.push_back(b[i] - a[i]);
        }
    }
    // Visit all gain planets first (they are always worth it)
    // Then visit cost planets if we have enough fuel
    sort(cost.begin(), cost.end());
    int visits = 0;
    for (int g : gain) {
        fuel += g;
        visits++;
    }
    // For cost planets: we need fuel >= cost[i] to visit, then gain a[i], lose b[i]
    // net = a[i] - b[i] < 0, so we lose net fuel. But we want max fuel.
    // Actually visiting cost planets reduces fuel, so we should only visit them
    // if we need to... but the problem says maximize fuel AND then maximize visits.
    // Visiting a cost planet: need b[i] fuel to travel, gain a[i]. Net = a[i]-b[i].
    // If a[i] < b[i], we lose fuel. But visiting increases visit count.
    // For max fuel, don't visit any cost planet. For max visits with same fuel,
    // visit cost planets only if they don't reduce fuel... they always do.
    // Wait: re-read. "collect fuel from planets". The fuel spent is travel cost.
    // After visiting, fuel = fuel - b[i] + a[i]. 
    // For max fuel: don't visit cost planets. fuel = initial + sum(gain).
    // For max visits: we can visit cost planets but it reduces fuel.
    // Problem: "maximize fuel first, then maximize visits with same fuel."
    // So cost planets are only worth visiting if they don't reduce final fuel.
    // But they always reduce fuel (net negative). So optimal = don't visit them.
    // Unless... the problem means something different.
    // Actually re-reading: "as long as remaining fuel is non-negative".
    // And "maximize fuel, then maximize visits".
    // So visiting cost planets is NEVER beneficial for fuel. So answer = fuel, visits = gain.size()+1
    // Hmm but the sample says 25 fuel, 4 visits. Let me check.
    // Sample: P=2. a[2]=10, b[2]=100. gain from P=10.
    // Planet 1: a=12,b=12 => net 0 (cost planet, a<b? no, a==b, net=0)
    // Planet 3: a=8,b=3 => net 5 (gain)
    // Planet 4: a=4,b=5 => net -1 (cost)
    // Planet 5: a=25,b=15 => net 10 (gain)
    // gain planets: 3,5. cost: 1 (net 0), 4 (net -1)
    // fuel after gain: 10+5+10=25. visits=3 (P,3,5)
    // But answer says 4 visits. So visiting planet 1 (net 0) doesn't reduce fuel!
    // Net 0 means a[i]==b[i], so it's neutral. We should visit those too.
    // Actually let me re-classify: net >= 0 is beneficial.
    // Visit all with a[i]-b[i] >= 0, then cost planets in order of b[i]-a[i].
    int cnt = 1; // starting planet
    for (int i = 1; i <= n; i++) {
        if (i == P) continue;
        if (a[i] >= b[i]) {
            cnt++;
        }
    }
    cout << fuel << "\n" << cnt << "\n";
    return 0;
}
