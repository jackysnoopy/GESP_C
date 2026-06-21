#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

long long gcd_func(long long a, long long b) { while (b) { a %= b; long long t = a; a = b; b = t; } return a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int families = 0;
    vector<long long> gcds, refs;
    for (int i = 0; i < n; i++) {
        bool placed = false;
        for (int f = 0; f < families; f++) {
            long long diff = a[i] - refs[f];
            if (diff == 0) { placed = true; break; }
            long long newGcd;
            if (gcds[f] == 0) newGcd = llabs(diff);
            else newGcd = gcd_func(gcds[f], llabs(diff));
            if (newGcd >= 2) { gcds[f] = newGcd; placed = true; break; }
        }
        if (!placed) { families++; gcds.push_back(0); refs.push_back(a[i]); }
    }
    cout << families << "\n";
    return 0;
}
