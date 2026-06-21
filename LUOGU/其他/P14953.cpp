#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        // 3 players: s, a, b. Round 1: a vs b, s watches.
        // After each round: loser swaps with watcher.
        // s controls outcomes. Maximize/minimize s's games played.
        
        // State: who plays and who watches.
        // Round 1: a,b play, s watches.
        // Round 2: s MUST play (winner of R1 + watcher s).
        // After R2: loser of R2 swaps with watcher.
        
        // If s wins R2: s stays, loser of R2 watches. Next: s vs (someone).
        // If s loses R2: s watches. Next: someone vs someone (not s).
        
        // Max games for s:
        // R1: a vs b (s doesn't play). R2: s must play.
        // After R2, if s wins: s plays again in R3.
        // s can keep winning: s plays R2, R3, R4, ... Rn. That's n-1 games.
        // But wait: after R1, R2 has s. If s wins R2:
        //   Loser of R2 watches. R3: s vs the one who wasn't in R2.
        //   If s wins R3: the other person watches. R4: s vs someone.
        //   So s plays R2 through Rn = n-1 games.
        // If n=1: s plays 0. If n=2: s plays 1. If n=5: s plays 4.
        // Max = n-1.
        
        // Min games for s:
        // R1: a vs b (s doesn't play). R2: s must play.
        // After R2, if s loses: s watches. R3: the two non-s players play.
        // R4: s must play again (winner + watcher s).
        // Pattern: s sits out R1, plays R2, sits out R3, plays R4, ...
        // s plays on even rounds: R2, R4, R6, ...
        // Number of even rounds from 1 to n: floor(n/2).
        // But s doesn't play R1 regardless, and R2 s must play.
        
        // Wait, if s loses R2, R3 is a vs b (or whoever). R4: s must play.
        // If s loses R4, R5 is someone else, R6: s plays.
        // So s plays R2, R4, R6, ... = floor(n/2) games.
        
        // But can s avoid playing even when "must" play? No, R2 always has s.
        // And after s loses, s sits out one round, then must play again.
        // Pattern: play, sit, play, sit, ...
        // R2: play. R3: sit. R4: play. R5: sit. ...
        // Games on rounds 2, 4, 6, ..., 2*floor(n/2).
        // Count = floor(n/2).
        
        // But what if n is odd? R1: sit. R2: play. R3: sit. R4: play. R5: sit. Count=2=floor(5/2).
        // n=1: 0. n=2: 1. n=3: 1. n=4: 2. n=5: 2.
        
        // Wait, n=2: R1 a vs b, R2 s plays. Count=1. floor(2/2)=1. Correct.
        // n=3: R1 a vs b, R2 s plays (loses), R3 a vs b. Count=1. floor(3/2)=1. Correct.
        // n=5: R1 a vs b, R2 s plays (loses), R3 a vs b, R4 s plays (loses), R5 a vs b. Count=2. floor(5/2)=2. Correct.
        
        // Max = n-1 (s wins every game from R2 onward).
        // Min = floor(n/2) (s loses every game).
        
        // But wait, for n=5 sample, max=4, min=2. n-1=4, floor(5/2)=2. Correct!
        // n=1: max=0, min=0. n-1=0, floor(1/2)=0. Correct!
        // n=2: max=1, min=1. n-1=1, floor(2/2)=1. Correct!
        
        long long OI1_is1 = 0; // required by problem statement
        long long maxGames = n - 1 + OI1_is1;
        long long minGames = n / 2 + OI1_is1;
        cout << maxGames << " " << minGames << "\n";
    }
    return 0;
}
