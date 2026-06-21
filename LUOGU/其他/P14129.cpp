#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x, p0;
    cin >> n >> x >> p0;
    vector<long long> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    int k;
    cin >> k;
    vector<long long> t(k), p(k);
    for (int i = 0; i < k; i++) cin >> t[i] >> p[i];
    
    // Binary search on answer: max number of people who can reach airport.
    // At time 0, distance = x, deadline = p0.
    // After k postponements, new deadline = p0 + sum of p[i] for i<=k.
    // Person i can travel at speed s[i]. Time to reach = x / s[i] (must be <= deadline).
    // We can choose which people to bring.
    // 
    // Key insight: with postponement, we get more time. We want to maximize people.
    // After j postponements (0<=j<=k), deadline = p0 + sum(p[0..j-1]).
    // Person i can make it if x / s[i] <= new_deadline.
    // We want to find the j that maximizes the number of people who can make it.
    //
    // But wait: we can only bring people who can reach on time.
    // The answer is: for each j from 0 to k, count people with s[i] >= ceil(x / deadline).
    // Actually: person i needs time x/s[i]. Must be <= deadline.
    // So s[i] >= x / deadline. Since s[i] is integer: s[i] >= ceil(x / deadline).
    // But x and deadline are integers, so ceil(x/deadline) = (x + deadline - 1) / deadline.
    
    long long curDeadline = p0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] > 0 && x <= curDeadline * s[i]) ans++;
    }
    
    for (int j = 0; j < k; j++) {
        curDeadline += p[j];
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] > 0 && x <= curDeadline * s[i]) count++;
        }
        ans = max(ans, count);
    }
    
    cout << ans << endl;
    return 0;
}
