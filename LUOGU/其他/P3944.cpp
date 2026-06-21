#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];
    sort(k.rbegin(), k.rend());
    // For each amount of shrink药水 s:
    // All minions have attack reduced by 3*s
    // Minions with (k_i - 3*s) <= 2: cost 1 mana, contribute (k_i - 3*s) damage
    // Minions with 3 <= (k_i - 3*s) <= 3: cost 4 mana, contribute (k_i - 3*s) damage
    // Minions with (k_i - 3*s) > 3: can't use
    // Actually: attack <= 2 after shrink -> cost 1
    //           attack <= 3 after shrink -> cost 4
    //           attack > 3: can't pull
    // We want to minimize s, then minimize mana.
    // Try s = 0, 1, 2, ... until impossible
    long long totalDamage = 0;
    for (int i = 0; i < n; i++) totalDamage += k[i];
    if (totalDamage < m) { cout << "Human Cannot Win Dog\n"; return 0; }
    
    for (int s = 0; s <= 10000; s++) {
        long long dmg = 0;
        long long mana = 0;
        vector<int> can2, can3;
        for (int i = 0; i < n; i++) {
            int atk = k[i] - 3*s;
            if (atk <= 0) continue;
            if (atk <= 2) can2.push_back(atk);
            else if (atk <= 3) can3.push_back(atk);
            // atk > 3: can't use
        }
        // Greedy: use strongest minions first
        // Actually want to maximize damage with minimum mana
        // For s fixed: prefer 1-mana minions (atk<=2) to deal damage
        // Then 4-mana minions (atk==3)
        for (int x : can2) dmg += x;
        for (int x : can3) dmg += x;
        mana = can2.size() * 1 + can3.size() * 4;
        if (dmg >= m) {
            cout << s << " " << mana << "\n";
            return 0;
        }
    }
    cout << "Human Cannot Win Dog\n";
    return 0;
}
