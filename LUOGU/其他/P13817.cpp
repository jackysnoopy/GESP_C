#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        // Maximize collisions. Two marbles collide when moving toward each other.
        // Elastic collision = they exchange velocities (effectively pass through each other).
        // So we can think of marbles as passing through each other.
        // A collision between marbles i,j happens iff they move toward each other.
        // To maximize collisions, we want as many pairs as possible to collide.
        // But constraint: no 3+ marbles at same position simultaneously.
        // 
        // Key insight: if marbles have distinct velocities, we can position them
        // so that collisions happen. The max collisions = n*(n-1)/2 for distinct velocities.
        // But if velocities are equal, two marbles with same velocity can never collide
        // (they maintain distance).
        //
        // Actually: marbles with same velocity, moving in same direction, never collide.
        // Two marbles collide iff they have different velocities and move toward each other.
        // With elastic collisions (exchange velocities), the effective behavior is:
        // marbles pass through each other. So the number of collisions equals the number
        // of pairs (i,j) where they cross paths, which happens when:
        // pos_i < pos_j and vel_i > vel_j (i approaches j from left faster)
        // OR pos_i > pos_j and vel_i < vel_j.
        // 
        // But we can choose positions and directions freely!
        // So we want to maximize the number of pairs that can be made to collide.
        // Two marbles can collide iff they have different velocities.
        // With same velocity, they maintain relative distance forever.
        //
        // Wait, but with elastic collisions they exchange velocities.
        // So if marble A (vel=2) and marble B (vel=3) collide, after collision
        // A has vel=3 and B has vel=2. They separate.
        // 
        // The maximum number of collisions with n marbles:
        // Count pairs with different velocities.
        // But constraint: no 3 at same position at same time.
        // 
        // If all velocities are distinct: max collisions = n*(n-1)/2.
        // If some share velocities: pairs with same velocity can't collide.
        // So max = total pairs - sum of C(cnt[v], 2) for each velocity v.
        //
        // Wait, but two marbles with same velocity CAN collide if one catches up.
        // No - same velocity means they maintain distance. Can't catch up.
        // Unless one was initially behind and has same velocity - they never meet.
        // So pairs with same velocity: 0 collisions.
        // Pairs with different velocities: 1 collision max (after elastic collision, they separate).
        //
        // So answer = total_pairs - sum(C(freq[v], 2)).
        
        map<int, int> freq;
        for (int i = 0; i < n; i++) freq[v[i]]++;
        long long total = (long long)n * (n - 1) / 2;
        for (auto& p : freq) {
            long long f = p.second;
            total -= f * (f - 1) / 2;
        }
        cout << total << "\n";
    }
    return 0;
}
