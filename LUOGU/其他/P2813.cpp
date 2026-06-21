#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> def(m), atk(n);
    for (int i = 0; i < m; i++) cin >> def[i];
    for (int i = 0; i < n; i++) cin >> atk[i];
    sort(def.begin(), def.end());
    sort(atk.begin(), atk.end());
    // Match attacks to defenses: attack i breaks defense j if atk[i] > def[j]
    // Use greedy: match strongest attacks to weakest breakable defenses
    int j = 0;
    long long ans = 0;
    for (int i = 0; i < n && j < m; i++) {
        if (atk[i] > def[j]) { j++; }
    }
    // j defenses broken. Remaining n-j attacks hit the ship.
    // But we need to maximize damage = sum of unmatched attacks
    // Actually: total damage = sum of all attacks - sum of matched attack values
    // Wait, the problem says: when all defenses are broken, all attacks hit the ship.
    // So we want to break all defenses using minimum total attack power.
    // If we can't break all, then... 
    // Actually: "当一艘母舰的防御系统全部被破坏掉之后，所有的攻击都会攻击到敌方母舰本身上去造成伤害"
    // So damage = total of ALL attack power if all defenses are broken.
    // If not all broken, damage depends on which specific attacks are used on defenses.
    // The problem likely asks: maximize total damage = maximize attacks that aren't wasted.
    // 
    // Strategy: break defenses with minimum attack power, save rest for damage.
    // Sort defenses ascending. For each defense, use the weakest attack that can break it.
    int ai = 0;
    long long wasted = 0;
    for (int di = 0; di < m; di++) {
        while (ai < n && atk[ai] <= def[di]) ai++;
        if (ai >= n) { cout << 0 << "\n"; return 0; }
        wasted += atk[ai];
        ai++;
    }
    long long totalAtk = 0;
    for (int i = 0; i < n; i++) totalAtk += atk[i];
    cout << totalAtk - wasted << "\n";
    return 0;
}
