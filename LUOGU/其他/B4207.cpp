#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long iH, iA, H, dA, M;
    cin >> iH >> iA >> H >> dA >> M;
    vector<long long> C(M + 1);
    for (int i = 1; i <= M; i++) cin >> C[i];
    
    // Binary search on number of turns to kill monster
    // For a given number of turns T, check if it's possible
    // Strategy: in each "life" of the warrior, he can attack some turns and sharpen some turns
    // After each death, warrior respawns with full HP and full attack
    // 
    // Actually, let's think about it differently.
    // The warrior has iH HP and iA attack. Each turn he can attack (deal current attack damage)
    // or sharpen (increase attack by dA). Monster attacks for C[i] damage each turn.
    // Warrior dies when HP <= 0, then respawns.
    //
    // Key insight: the warrior should sharpen as much as possible early, then attack.
    // But he needs to survive.
    //
    // Let's binary search on the answer T (number of turns).
    // For a given T, we need to check if the warrior can kill the monster in T turns.
    //
    // The warrior's attack after sharpening s times is iA + s*dA.
    // If he attacks a times and sharpens s times, a + s = T, and total damage = sum of attacks.
    // The damage depends on when he attacks (his current attack at that time).
    //
    // This is complex. Let me try a different approach:
    // For each possible number of sharpenings s (0 to T-1), the warrior sharpens s times
    // and attacks T-s times. The attack value during the i-th sharpening is iA + (i-1)*dA.
    // The attack value during the j-th attack (after all sharpenings) is iA + s*dA.
    // Wait, the order matters. The warrior can interleave sharpening and attacking.
    //
    // Optimal strategy: sharpen first, then attack. This maximizes total damage.
    // If warrior sharpens s times first, then attacks T-s times:
    // Total damage = (iA + s*dA) * (T - s)
    // We need this >= H.
    //
    // But the warrior also needs to survive T turns. The warrior's HP after turn t is:
    // iH - sum of C[1..t] (if he doesn't die and respawn)
    // Actually, the warrior respawns whenever he dies. So he can survive "infinite" turns
    // by dying and respawning. The constraint is just that he kills the monster in T turns.
    //
    // Wait, but when the warrior dies, his attack resets to iA. So he can't accumulate
    // sharpening bonuses across deaths!
    //
    // So the warrior needs to survive long enough to deal enough damage in one "life".
    // In one life, he can survive for some number of turns t, where iH > sum(C[1..t]).
    // During those t turns, he sharpens s times and attacks t-s times.
    // Total damage = (iA + s*dA) * (t - s).
    // Maximize this over s in [0, t].
    //
    // But he can have multiple lives. In each life, he starts fresh.
    // The total turns used across all lives must be <= M.
    // The total damage across all lives must be >= H.
    //
    // Actually, re-reading the problem: "最少能在几个回合内杀死怪物"
    // So we want to minimize the total number of turns.
    //
    // In each life, the warrior can survive up to some number of turns.
    // Let's compute for each life how many turns he survives:
    // Life 1: survives turns 1..t1 where sum(C[1..t1]) < iH
    // Life 2: survives turns t1+1..t2 where sum(C[t1+1..t2]) < iH
    // etc.
    //
    // Wait, after respawning, the turn counter continues. So in life 2, the warrior
    // faces C[t1+1], C[t1+2], etc.
    //
    // Let me just simulate:
    // For each possible total turns T (1 to M), check if the monster can be killed.
    // Simulate the warrior's life cycle.
    
    // Actually, let's just simulate turn by turn and find the minimum T.
    // At each turn, the warrior chooses to attack or sharpen.
    // We want to minimize the number of turns to deal H total damage.
    //
    // Optimal strategy within one life: sharpen as much as possible while surviving,
    // then attack with maximum damage.
    //
    // But across lives, it's more complex because the warrior might want to attack
    // a little in one life and sharpen more in the next.
    //
    // Let me try a simpler approach: binary search on T.
    // For a given T, simulate the warrior's optimal strategy.
    //
    // Actually, the optimal strategy is:
    // - In each life, sharpen until just before death, then attack.
    // - But we need to track the total damage dealt.
    //
    // Let me just simulate greedily:
    // For each turn, decide whether to sharpen or attack.
    // Sharpen if it increases total damage potential.
    // Attack if we need to deal damage now.
    //
    // This is getting complex. Let me try a direct approach:
    // Binary search on T. For each T, check all possible numbers of sharpenings s (0 to T-1).
    // For each s, the warrior sharpens s times and attacks T-s times.
    // The damage per attack is iA + s*dA (if all sharpenings happen before all attacks).
    // Total damage = (iA + s*dA) * (T - s).
    // We need to check if the warrior can survive long enough to do this.
    //
    // But the warrior might die and respawn. After respawning, attack resets to iA.
    // So the s sharpenings must happen within one life.
    //
    // In one life, the warrior can survive up to t turns where sum(C[1..t]) < iH.
    // During those t turns, he sharpens s times and attacks t-s times.
    // Total damage from this life = (iA + s*dA) * (t - s).
    //
    // But wait, C[i] depends on the turn number, not the life number.
    // So in life 1, turns 1..t1, the warrior faces C[1], C[2], ..., C[t1].
    // In life 2, turns t1+1..t2, the warrior faces C[t1+1], ..., C[t2].
    //
    // For a given T, the warrior uses T turns total across all lives.
    // In each life, he sharpens some times and attacks some times.
    // The total damage is the sum across all lives.
    //
    // This is a complex optimization problem. Let me just implement the simulation.
    
    // Simple simulation: for each turn, decide to sharpen or attack.
    // Greedy: always sharpen if possible (to maximize future damage).
    // But we need to deal damage to kill the monster.
    //
    // Let me use binary search on T and simulate:
    // For a given T, the warrior has T turns. He needs to deal >= H damage.
    // In each life, he can survive some turns. He should maximize damage per life.
    //
    // Actually, let me just iterate T from 1 to M and simulate:
    
    long long curHP = iH;
    long long curAtk = iA;
    long long totalDamage = 0;
    int answer = -1;
    
    // For each turn, decide to sharpen or attack
    // Optimal: sharpen if curAtk * 1 < (curAtk + dA) * 1, i.e., always sharpen first
    // But we also need to survive. After sharpening, monster attacks and we lose HP.
    // If we die, attack resets.
    //
    // The optimal strategy in one life: sharpen as many times as possible, then attack.
    // How many times can we sharpen? Until we would die.
    // After s sharpenings, our HP is iH - sum(C[current..current+s-1]).
    // If this > 0, we can sharpen s times. Then attack with curAtk = iA + s*dA.
    //
    // But we might want to attack some times during the life too.
    // Actually, sharpening first is always optimal because it maximizes the damage
    // of subsequent attacks.
    //
    // Let me compute: in one life starting at turn t0, the warrior can survive
    // up to t0 + s - 1 where sum(C[t0..t0+s-1]) < iH.
    // Then he attacks with curAtk = iA + s*dA.
    // But wait, after s sharpenings, he has s turns left in this life? No.
    // He has some total turns in this life. Let's say he survives s turns (sharpening all).
    // Then on the s+1-th turn, the monster would kill him. So he can't attack.
    // Unless he attacks before dying.
    //
    // Let me reconsider: in a life starting at turn t0:
    // Turn t0: sharpen (if possible) or attack
    // Turn t0+1: sharpen or attack
    // ...
    // The warrior dies at turn t0+k where sum(C[t0..t0+k-1]) >= iH.
    // Wait, the warrior acts first, then the monster. So:
    // Turn t0: warrior acts, then monster attacks for C[t0]
    // After turn t0: warrior HP = iH - C[t0] (if he didn't sharpen, which doesn't affect HP)
    // Actually, sharpening doesn't affect HP. So HP after turn t0 = iH - C[t0].
    // After turn t0+1: HP = iH - C[t0] - C[t0+1].
    // The warrior dies when HP <= 0 after monster's attack.
    // So he survives turns t0, t0+1, ..., t0+k-1 where sum(C[t0..t0+k-1]) <= iH.
    // Wait, HP after turn t0+j is iH - sum(C[t0..t0+j]).
    // He dies when this <= 0. So he survives up to the last j where sum(C[t0..t0+j]) < iH.
    // (He dies on the turn where sum >= iH, but he acts first that turn.)
    //
    // So in a life starting at t0, the warrior can act for s turns where
    // s = max{j : sum(C[t0..t0+j-1]) < iH} + 1 (the +1 is because he acts before dying on the last turn).
    // Actually, let me be more precise:
    // After turn t0+j (0-indexed), HP = iH - sum(C[t0..t0+j]).
    // He dies when HP <= 0, i.e., sum(C[t0..t0+j]) >= iH.
    // He can act on turn t0+j if sum(C[t0..t0+j-1]) < iH (he's alive at start of turn).
    // Wait, he acts first, then monster attacks. So:
    // Start of turn t0+j: HP = iH - sum(C[t0..t0+j-1]).
    // If HP > 0, he acts. Then monster attacks: HP -= C[t0+j].
    // If HP <= 0 after monster attack, he dies and respawns.
    //
    // So he can act on turn t0+j if iH - sum(C[t0..t0+j-1]) > 0.
    // The number of turns he acts is the largest j such that sum(C[t0..t0+j-1]) < iH.
    // This is s = max{j : prefix[t0+j-1] - prefix[t0-1] < iH}.
    
    // OK this is getting very detailed. Let me just implement a clean simulation.
    
    // For each turn, track: is the warrior alive? What's his attack?
    // Optimal strategy: sharpen on every turn until the warrior would die next turn,
    // then attack on the last turn of each life.
    //
    // Actually, the optimal strategy might be more nuanced. Let me think...
    // In a life with s turns:
    // If warrior sharpens s-1 times and attacks once: damage = (iA + (s-1)*dA) * 1
    // If warrior sharpens s-2 times and attacks twice: damage = (iA + (s-2)*dA) * 2
    // ...
    // If warrior sharpens 0 times and attacks s times: damage = iA * s
    //
    // Maximize (iA + k*dA) * (s - k) for k in [0, s].
    // This is a quadratic in k: -dA*k^2 + (s*dA - iA)*k + iA*s.
    // Maximum at k = (s*dA - iA) / (2*dA) = s/2 - iA/(2*dA).
    //
    // But we also need to consider that the warrior might want to deal some damage
    // in one life and continue in the next.
    //
    // For minimizing total turns, the optimal strategy is:
    // In each life, maximize damage per turn. Then use the minimum number of lives.
    //
    // Actually, let me just use binary search on T and check feasibility.
    // For a given T, simulate the warrior's life cycles and check if total damage >= H.
    // In each life, use the optimal number of sharpenings.
    
    // Let me implement this:
    
    auto check = [&](int T) -> bool {
        // Simulate T turns
        long long dmg = 0;
        long long hp = iH;
        long long atk = iA;
        int turnsLeft = T;
        int turn = 1;
        
        while (turnsLeft > 0 && dmg < H) {
            // In this life, how many turns can the warrior survive?
            long long remainHP = hp;
            int lifeTurns = 0;
            for (int t = turn; t <= turn + turnsLeft - 1 && t <= M; t++) {
                if (remainHP <= 0) break;
                remainHP -= C[t];
                lifeTurns++;
                if (remainHP <= 0) break; // dies after this turn
            }
            // Wait, the warrior acts first, then monster attacks.
            // He can act on turn t if his HP > 0 at start of turn.
            // After acting, monster attacks. If HP <= 0, he dies.
            
            // Let me redo: lifeTurns = number of turns he acts in this life
            lifeTurns = 0;
            remainHP = hp;
            for (int t = turn; t <= turn + turnsLeft - 1 && t <= M; t++) {
                if (remainHP <= 0) break;
                lifeTurns++;
                remainHP -= C[t];
                if (remainHP <= 0) break;
            }
            // Hmm, this gives lifeTurns including the turn where he dies.
            // But he acts before dying, so lifeTurns is correct.
            
            if (lifeTurns == 0) break;
            
            // Optimize: sharpen k times, attack (lifeTurns - k) times
            // Damage = (iA + k*dA) * (lifeTurns - k)
            // Maximize over k in [0, lifeTurns]
            long long bestDmg = 0;
            for (int k = 0; k <= lifeTurns; k++) {
                long long d = (iA + (long long)k * dA) * (lifeTurns - k);
                if (d > bestDmg) bestDmg = d;
            }
            dmg += bestDmg;
            turnsLeft -= lifeTurns;
            turn += lifeTurns;
            hp = iH; // respawn
        }
        
        return dmg >= H;
    };
    
    // Binary search on T
    int lo = 1, hi = M, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
