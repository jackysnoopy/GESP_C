#include <iostream>
#include <set>
using namespace std;
int count_sixes(long long x) {
    if (x == 0) return 0;
    int c = 0;
    while (x > 0) { if (x % 10 == 6) c++; x /= 10; }
    return c;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int big = 0;
    multiset<int> ms;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        int c = count_sixes(a);
        if (c >= 6) big++;
        else if (c > 0) ms.insert(c);
    }
    int groups = big;
    while (!ms.empty()) {
        auto it = prev(ms.end());
        int sum = *it;
        ms.erase(it);
        int used = 1;
        while (sum < 6 && used < 3 && !ms.empty()) {
            int need = 6 - sum;
            auto fit = ms.lower_bound(need);
            if (fit != ms.end()) { sum += *fit; ms.erase(fit); }
            else { auto lit = prev(ms.end()); sum += *lit; ms.erase(lit); }
            used++;
        }
        if (sum >= 6) groups++;
    }
    cout << groups << "\n";
    return 0;
}
