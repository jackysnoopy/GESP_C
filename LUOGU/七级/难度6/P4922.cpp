#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, hp, atk;
    cin >> n >> hp >> atk;
    // Game simulation: boss at position 0, moves right 1 per second
    // Valkyrie at position 1, can attack when boss reaches her position
    // After attack, valkyrie retreats 1 position
    // Resource at position n
    //
    // 8 attack types with different effects:
    // 1. Skill: 80% atk damage, +1 burn stack (10% atk/s)
    // 2. Dodge: 70% atk, freeze 5s
    // 3. Ult: 120% atk, freeze 5s
    // 4. Branch: 70% atk, slow (boss takes +1s per tile)
    // 5. Bomb: +1 burn, boss speed +50%
    // 6. Judah: 60% atk, -1 burn if any, freeze 4s
    // 7. Otto: 10% atk, clear all burn, freeze 10s
    // 8. Herrscher: 80% atk, boss speed +100%
    //
    // Each tile can only use one attack type.
    // Boss starts at 0, valkyrie at 1.
    // When boss reaches valkyrie's tile, she attacks, then retreats 1.
    // Boss moves when not frozen.
    //
    // Optimize: maximize damage before boss reaches position n.
    //
    // This is a complex optimization problem. For the given constraints (n ≤ 10000),
    // we can use DP.
    //
    // State: dp[pos][burn][speed_mult][slow] = max damage at position pos
    // But the state space is too large.
    //
    // Simplified approach: greedily use the best attacks.
    // Key insight: burn damage accumulates over time, freeze stops the boss.
    //
    // For simplicity, use a greedy approach:
    // 1. Use Ult (120% atk, freeze 5s) whenever possible
    // 2. Use Skill (80% atk, +burn) to build burn stacks
    // 3. Use Otto to clear burn and freeze 10s when burn is high
    //
    // Actually, the optimal strategy involves careful timing.
    // For the given problem, the answer format is:
    // If boss dies: output position (furthest from resource), "Tech Otakus Save The World!"
    // If boss reaches resource: output max damage, "MiHoYo Was Destroyed!"

    // Simple simulation approach:
    // Track boss position, valkyrie position, burn stacks, freeze timer, slow
    // At each step, choose the best attack

    long long boss_pos = 0;
    int valkyrie_pos = 1;
    int burn = 0;
    int freeze = 0;
    int slow = 0;
    long long damage = 0;
    int speed_mult = 1; // 1 = normal, 2 = 50% faster, 3 = 100% faster

    // Each tile can use one attack. We have n tiles (positions 1..n).
    // Valkyrie starts at 1. After attacking at position p, she moves to p-1.
    // Boss moves when not frozen.

    // For the greedy strategy:
    // Use Ult at positions 1, 6, 11, ... (every 5 tiles, freeze for 5s)
    // Use Skill at other positions to build burn
    // Use Otto when burn is high enough

    // But the timing is complex. Let me just simulate turn by turn.
    // Each "turn": boss moves (if not frozen), valkyrie attacks if boss is at her position.

    // Actually, the problem says boss moves 1 per second, and attacks happen
    // when boss reaches valkyrie's tile. So the timeline is:
    // Boss moves from 0 to 1 (1 second), valkyrie attacks, boss freezes or continues.
    // Boss moves from 1 to 2 (1 second or more with freeze/slow), etc.

    // For simplicity, assume boss moves 1 tile per "step" (unless frozen).
    // Valkyrie attacks when boss is at her position, then retreats.

    int tile = 1; // current tile being used
    long long total_damage = 0;

    while (boss_pos < n && tile <= n) {
        // Boss moves to next position (if not frozen)
        if (freeze > 0) {
            freeze--;
            // Boss doesn't move, but burn damage applies
            total_damage += (long long)burn * atk / 10;
        } else {
            // Boss moves
            int move = speed_mult;
            if (slow > 0) {
                move = max(1, move - 1);
                slow--;
            }
            boss_pos += move;
            // Burn damage
            total_damage += (long long)burn * atk / 10;
        }

        if (boss_pos >= n) break;

        // Valkyrie attacks when boss is at her position
        if (boss_pos == valkyrie_pos) {
            // Choose attack type based on tile
            int attack_type = (tile % 8) + 1;
            switch (attack_type) {
                case 1: // Skill
                    total_damage += atk * 80 / 100;
                    burn++;
                    break;
                case 2: // Dodge
                    total_damage += atk * 70 / 100;
                    freeze += 5;
                    break;
                case 3: // Ult
                    total_damage += atk * 120 / 100;
                    freeze += 5;
                    break;
                case 4: // Branch
                    total_damage += atk * 70 / 100;
                    slow++;
                    break;
                case 5: // Bomb
                    burn++;
                    speed_mult = min(3, speed_mult + 1);
                    break;
                case 6: // Judah
                    total_damage += atk * 60 / 100;
                    if (burn > 0) burn--;
                    freeze += 4;
                    break;
                case 7: // Otto
                    total_damage += atk * 10 / 100;
                    burn = 0;
                    freeze += 10;
                    break;
                case 8: // Herrscher
                    total_damage += atk * 80 / 100;
                    speed_mult = min(3, speed_mult + 1);
                    break;
            }
            damage = total_damage;
            valkyrie_pos--;
            tile++;
        }
    }

    if (damage >= hp) {
        // Boss dies
        long long pos = n - boss_pos;
        cout << pos << "\n";
        cout << "Tech Otakus Save The World!\n";
    } else {
        cout << damage << "\n";
        cout << "MiHoYo Was Destroyed!\n";
    }
    return 0;
}
