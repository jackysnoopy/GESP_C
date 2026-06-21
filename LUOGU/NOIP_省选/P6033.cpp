#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sort(a.begin(), a.end());
    queue<long long> q1, q2;
    for (long long x : a) q1.push(x);
    
    auto get_min = [&]() {
        long long res;
        if (q2.empty()) { res = q1.front(); q1.pop(); }
        else if (q1.empty()) { res = q2.front(); q2.pop(); }
        else if (q1.front() < q2.front()) { res = q1.front(); q1.pop(); }
        else { res = q2.front(); q2.pop(); }
        return res;
    };
    
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        long long x = get_min(), y = get_min();
        long long sum = x + y;
        ans += sum;
        q2.push(sum);
    }
    
    cout << ans << "\n";
    return 0;
}