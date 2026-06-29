#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<int> next_pos(m + 1, n);
    vector<int> next_occ(n);
    for (int i = n - 1; i >= 0; i--) {
        next_occ[i] = next_pos[c[i]];
        next_pos[c[i]] = i;
    }

    set<pair<int, int>> machines;
    map<int, int> flavor_to_next;
    int washes = 0;

    for (int i = 0; i < n; i++) {
        int flavor = c[i];
        if (flavor_to_next.count(flavor)) {
            int old_next = flavor_to_next[flavor];
            machines.erase({old_next, flavor});
            machines.insert({next_occ[i], flavor});
            flavor_to_next[flavor] = next_occ[i];
        } else {
            washes++;
            if ((int)machines.size() < k) {
                machines.insert({next_occ[i], flavor});
                flavor_to_next[flavor] = next_occ[i];
            } else {
                auto it = machines.end();
                --it;
                int evict_flavor = it->second;
                machines.erase(it);
                flavor_to_next.erase(evict_flavor);
                machines.insert({next_occ[i], flavor});
                flavor_to_next[flavor] = next_occ[i];
            }
        }
    }

    cout << washes << endl;
    return 0;
}
