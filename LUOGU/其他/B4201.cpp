#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long ATK, HP;
    cin >> ATK >> HP;
    vector<long long> A(n), H(n);
    for (int i = 0; i < n; i++) cin >> A[i] >> H[i];
    // Each warrior deals A[i] damage per round, takes ATK damage per round.
    // Warrior i survives ceil(H[i]/ATK) rounds (dies when HP <= 0 after a round).
    // Actually: warrior fights until HP <= 0. Each round: warrior HP -= ATK, dragon HP -= A[i]*multiplier.
    // Warrior i survives floor((H[i]-1)/ATK) + 1 rounds? No.
    // Round 1: H[i] -= ATK. If H[i] <= 0, warrior dies after 1 round.
    // So warrior i survives floor((H[i]-1)/ATK) + 1 rounds? Let's check:
    // H[i]=2, ATK=1: round 1: HP=1. round 2: HP=0. Dies after 2 rounds. floor(1/1)+1=2. Correct.
    // H[i]=1, ATK=1: round 1: HP=0. Dies after 1 round. floor(0/1)+1=1. Correct.
    // H[i]=3, ATK=2: round 1: HP=1. round 2: HP=-1. Dies after 2 rounds. floor(2/2)+1=2. Correct.
    // So rounds_i = floor((H[i]-1)/ATK) + 1 = (H[i]-1)/ATK + 1 = ceil(H[i]/ATK).
    // Actually ceil(2/1)=2, ceil(1/1)=1, ceil(3/2)=2. Yes, rounds_i = ceil(H[i]/ATK).
    
    // Total damage from warrior i: A[i] * rounds_i * multiplier.
    // Multiplier depends on order: warrior 1 (first) has multiplier 1, warrior 2 has multiplier 2, etc.
    // Wait, the multiplier increases each time a NEW warrior starts fighting.
    // "受到第二个勇士的伤害变为两倍" - the second warrior deals 2x damage.
    // "受到第三个勇士的伤害变为三倍" - the third deals 3x, etc.
    // So warrior k (k-th to fight) deals k * A[i] damage per round.
    // Total damage from warrior k: k * A[i_k] * rounds_{i_k}.
    // We need total damage >= HP.
    // We want to minimize the number of warriors used.
    
    // Greedy: use the warrior with the highest total damage potential first.
    // Total damage from warrior i as k-th fighter: k * A[i] * rounds_i.
    // We want to maximize total damage with minimum warriors.
    // Sort warriors by A[i] * rounds_i (damage per round) in descending order.
    // Use them in order, accumulating damage.
    
    // But the multiplier depends on the ORDER. The first warrior has multiplier 1.
    // So we want the warrior with the highest A[i]*rounds_i to go first? No,
    // we want the warrior with the highest A[i]*rounds_i to go LAST (highest multiplier).
    // But we also want to minimize the number of warriors.
    
    // Actually, the multiplier is the ORDER (1, 2, 3, ...), not the warrior's strength.
    // So the total damage from using k warriors in order is:
    // sum_{i=1}^{k} i * A[i_k] * rounds_{i_k}.
    // To maximize this, we should put the strongest warrior last (highest multiplier).
    // So sort by A[i]*rounds_i ascending, and use them in that order.
    
    // Wait, but we want to MINIMIZE the number of warriors while dealing >= HP damage.
    // So we want to maximize damage per warrior.
    // If we use warrior i as the k-th fighter, it deals k * A[i] * rounds_i damage.
    // The total damage with warriors in order 1, 2, ..., k is:
    // 1*d_1 + 2*d_2 + ... + k*d_k where d_i = A[i]*rounds_i.
    // To maximize total damage for a given k, sort d_i ascending (put largest d last).
    
    // Binary search on k: can we kill the dragon with k warriors?
    // For k warriors, sort by d_i ascending. Total damage = sum i*d_i.
    // If this >= HP, we can kill the dragon.
    
    vector<long long> d(n);
    for (int i = 0; i < n; i++) {
        long long rounds = (H[i] + ATK - 1) / ATK;
        d[i] = A[i] * rounds;
    }
    sort(d.begin(), d.end());
    
    // Binary search: minimum k such that sum_{i=1}^{k} i*d[i] >= HP
    // But we need to use the LARGEST k values (sorted ascending, take the last k).
    // Actually, sort ascending. The k-th warrior (1-indexed) has multiplier k.
    // We want to assign the largest d to the largest multiplier.
    // So sort d ascending: d[0] <= d[1] <= ... <= d[n-1].
    // Use warriors d[0], d[1], ..., d[k-1] in that order.
    // Total damage = 1*d[0] + 2*d[1] + ... + k*d[k-1].
    
    // But this might not be optimal. We should use the TOP k warriors, not the bottom k.
    // Sort d ascending. Use d[n-k], d[n-k+1], ..., d[n-1].
    // Assign multipliers 1, 2, ..., k to them.
    // To maximize: assign largest multiplier to largest d.
    // So: multiplier 1 to d[n-k], multiplier 2 to d[n-k+1], ..., multiplier k to d[n-1].
    // Total = 1*d[n-k] + 2*d[n-k+1] + ... + k*d[n-1].
    
    // Binary search on k
    int lo = 1, hi = n, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        long long totalDmg = 0;
        bool ok = false;
        for (int i = 0; i < mid; i++) {
            long long mult = i + 1;
            // Use d[n-mid+i] with multiplier mult
            totalDmg += mult * d[n - mid + i];
            if (totalDmg >= HP) { ok = true; break; }
        }
        if (ok) { ans = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    
    if (ans == -1) cout << "Fail\n";
    else cout << ans << "\n";
    return 0;
}
