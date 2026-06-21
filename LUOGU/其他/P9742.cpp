#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        long long r[200001], c[200001];
        for (int i = 0; i < n; i++) cin >> r[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        
        struct Person { int id; long long c; int a; };
        Person p[200001];
        for (int i = 0; i < n; i++) {
            p[i].id = i;
            p[i].c = c[i];
            p[i].a = i + 1;
        }
        
        // Sort by c descending (most positive first)
        sort(p, p + n, [](const Person& x, const Person& y) {
            return x.c > y.c;
        });
        
        set<int> avail;
        for (int i = 1; i <= n; i++) avail.insert(i);
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long ci = p[i].c;
            int ai = p[i].a;
            
            if (ci > 0) {
                // Want b_i <= a_i (to get +c_i)
                auto it = avail.upper_bound(ai);
                if (it != avail.begin()) {
                    --it;
                    ans += ci;
                    avail.erase(it);
                } else {
                    // No position <= ai, assign to any
                    auto it2 = avail.begin();
                    avail.erase(it2);
                }
            } else if (ci < 0) {
                // Want b_i > a_i (to get -c_i)
                auto it = avail.upper_bound(ai);
                if (it != avail.end()) {
                    ans -= ci;
                    avail.erase(it);
                } else {
                    auto it2 = avail.begin();
                    avail.erase(it2);
                }
            } else {
                avail.erase(avail.begin());
            }
        }
        
        cout << ans << "\n";
    }
    return 0;
}
