#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll x;
    cin >> x;
    
    if (x == 0) {
        cout << "1\n1\n";
        return 0;
    }
    
    // Find smallest n such that C(n,2) >= x
    ll n = 1;
    while (n * (n - 1) / 2 < x) n++;
    
    // Build lexicographically smallest permutation with x inversions
    vector<int> s;
    for (int i = 1; i <= n; i++) s.push_back(i);
    
    vector<int> result;
    ll remaining = x;
    
    for (int i = 0; i < n; i++) {
        int rem = n - i; // remaining elements count
        for (int j = 0; j < (int)s.size(); j++) {
            ll maxAfter = (ll)(rem - 1) * (rem - 2) / 2; // C(rem-1, 2)
            if (remaining - j >= 0 && remaining - j <= maxAfter) {
                result.push_back(s[j]);
                remaining -= j;
                s.erase(s.begin() + j);
                break;
            }
        }
    }
    
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    return 0;
}
