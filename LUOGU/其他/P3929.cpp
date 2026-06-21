#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        if (n <= 2) { cout << "Yes\n"; continue; }
        // Two patterns: peak-valley or valley-peak
        // Pattern 1: a[0]<=a[1]>=a[2]<=a[3]>=...
        // Pattern 2: a[0]>=a[1]<=a[2]>=a[3]<=...
        auto check = [&](int pat) -> bool {
            int bad = 0;
            for (int i = 1; i < n; i++) {
                bool ok;
                if (pat == 0) ok = (i%2==1) ? (a[i-1]<=a[i]) : (a[i-1]>=a[i]);
                else ok = (i%2==1) ? (a[i-1]>=a[i]) : (a[i-1]<=a[i]);
                if (!ok) bad++;
            }
            return bad <= 2; // changing one element fixes at most 2 adjacent relations
        };
        if (check(0) || check(1)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
