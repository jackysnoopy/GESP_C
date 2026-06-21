#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // Circular game: Jerry starts at box 1, picks at least 1 coin.
        // Next player picks from next box, etc.
        // If a box has 0 coins when it's your turn, you lose.
        // Both play optimally.
        //
        // This is a Nim-like game on a circle.
        // Key insight: the game is determined by the pattern of coin counts.
        // If all boxes have the same count, Jerry loses (by symmetry, Tom can mirror).
        // Actually, let me think more carefully.
        //
        // The game proceeds in order: box 1, box 2, ..., box n, box 1, box 2, ...
        // Each player must take at least 1 coin from the current box.
        // The player who can't (box is empty) loses.
        //
        // This is equivalent to: the game ends when a box reaches 0.
        // The player whose turn it is when box i is reached and it's 0 loses.
        //
        // Strategy: each player can control how many coins to take from each box.
        // The key is: who is forced to empty a box?
        //
        // If all boxes have the same count k: Jerry takes some from box 1, Tom takes from box 2, etc.
        // After one full round, each box has been reduced. The game continues.
        // By symmetry, if all boxes are equal, the second player (Tom) can always mirror Jerry.
        // So Tom wins. Jerry loses.
        //
        // If boxes are not all equal: Jerry can try to force a win.
        //
        // Actually, let me think about this differently.
        // The game is: players alternate taking from boxes in order.
        // The game ends when a player faces an empty box.
        // 
        // Consider the minimum value m = min(a[i]).
        // After m full rounds of taking 1 from each box, all boxes are reduced by m.
        // The remaining game has boxes with values a[i] - m.
        // Some boxes might be 0.
        //
        // Actually, the key insight is:
        // If all a[i] are equal, Tom wins (second player wins by symmetry).
        // If not all equal, Jerry wins (first player can force a win).
        //
        // Let me verify with samples:
        // n=1, a=[10]: Jerry takes 10, box empty. Tom faces empty box 1. Tom loses. Jerry wins.
        //   But all boxes are equal (only 1 box). So "all equal" => Tom wins. But Jerry wins!
        //   Contradiction! So my rule is wrong.
        //
        // Let me reconsider. For n=1: Jerry takes all coins from box 1. Then it's Tom's turn,
        // box 1 is empty. Tom loses. Jerry wins.
        //
        // For n=2, a=[30,50]: 
        // Round 1: Jerry takes from box 1 (at least 1). Tom takes from box 2.
        // Round 2: Jerry takes from box 1 again. Tom takes from box 2.
        // ...
        // The game continues until one box is empty.
        // If Jerry takes all 30 from box 1 over 30 rounds, and Tom takes from box 2:
        // After 30 rounds, box 1 is empty. It's Jerry's turn at box 1 (round 31). Jerry loses.
        // But Jerry doesn't have to take all from box 1. He can take 1 each time.
        // 
        // Actually, the game is more complex. Let me think about it as a combinatorial game.
        //
        // The state is: (current box index, remaining coins in each box).
        // This is too complex for n up to 1000.
        //
        // Key insight: the game is determined by the parities of the box values.
        // Actually, let me think about it as: each box is a "pile" in a take-away game,
        // but the piles are played in order.
        //
        // The game: players alternate. On your turn, you MUST take from the current box.
        // The current box advances after each move.
        // If the current box is empty, you lose.
        //
        // This is equivalent to: the game ends after a certain number of moves.
        // The number of moves is determined by when a box reaches 0.
        //
        // Consider: each box i has a[i] coins. Over the course of the game,
        // box i is visited ceil(a[i] / k_i) times, where k_i is the number of coins
        // taken each visit. But k_i can vary.
        //
        // Actually, the game is simpler than I thought.
        // The total number of moves before the game ends is:
        // sum of (number of times each box is visited before being emptied).
        // Each box i is visited some number of times v_i, and the total coins taken from it is a[i].
        // The game ends when a box is visited and found empty.
        //
        // The key: the player who makes the last move (empties the last box) wins,
        // because the next player faces an empty box.
        //
        // Wait, that's not right either. The player who empties a box doesn't necessarily win.
        // The player who faces an empty box loses.
        //
        // Let me think about it as: the game has a fixed sequence of moves.
        // Move 1: Jerry at box 1. Move 2: Tom at box 2. ... Move n: Tom/Jerry at box n.
        // Move n+1: Jerry/Tom at box 1. Etc.
        //
        // The game ends at the first move where the current box is empty.
        // The player making that move loses.
        //
        // So the question is: how many moves happen before a box is emptied?
        // Each player controls how many coins to take from each box.
        // A player wants to either:
        // 1. Force the opponent to face an empty box (win).
        // 2. Avoid being the one to face an empty box (don't lose).
        //
        // Strategy: if it's your turn at box i and box i has k coins:
        // - If you take all k coins, box i is empty. The next player at box i loses.
        //   But the next player at box i is after a full round, so it's n moves later.
        // - If you take k-1 coins, box i has 1 left. The next player at box i must take 1.
        //   Then box i is empty, and the player after that loses.
        //
        // This is getting complex. Let me try to find a pattern.
        //
        // For n=1, a=[k]: Jerry takes all k. Tom faces empty box. Tom loses. Jerry wins.
        // For n=1, a=[1]: Jerry takes 1. Tom faces empty. Tom loses. Jerry wins.
        //
        // For n=2, a=[1,1]: Jerry takes 1 from box 1. Tom takes 1 from box 2.
        //   Jerry faces empty box 1. Jerry loses. Tom wins.
        // For n=2, a=[1,2]: Jerry takes 1 from box 1 (box 1 empty).
        //   Tom takes 1 from box 2 (box 2 has 1 left).
        //   Jerry faces empty box 1. Jerry loses. Tom wins.
        //   OR: Jerry takes 1 from box 1. Tom takes 2 from box 2 (box 2 empty).
        //   Jerry faces empty box 1. Jerry loses.
        //   So Tom wins regardless.
        //
        // For n=2, a=[2,1]: Jerry takes 1 from box 1 (box 1 has 1 left).
        //   Tom takes 1 from box 2 (box 2 empty).
        //   Jerry takes 1 from box 1 (box 1 empty).
        //   Tom faces empty box 2. Tom loses. Jerry wins.
        //   OR: Jerry takes 2 from box 1 (box 1 empty).
        //   Tom takes 1 from box 2 (box 2 empty).
        //   Jerry faces empty box 1. Jerry loses.
        //   So Jerry should take 1, not 2. Then Jerry wins.
        //
        // Hmm, so the strategy depends on the specific values.
        //
        // For n=2, a=[30,50]: Sample says Tom wins.
        // Jerry at box 1 (30 coins). Tom at box 2 (50 coins).
        // If Jerry takes 1 from box 1: Tom at box 2.
        // The game continues. Eventually one box is emptied.
        //
        // Let me think about it as: the game is won by the player who doesn't have to
        // empty a box first. 
        //
        // Actually, I think the key insight is:
        // The game is equivalent to a Nim game where each box is a pile, and players
        // take turns removing from piles in order. The player who can't move loses.
        //
        // For a linear game (not circular), this is well-studied.
        // For a circular game, it's more complex.
        //
        // Let me think about it differently:
        // The game ends when a box is emptied and the next player at that box loses.
        // The total number of moves is determined by when the first box is emptied.
        //
        // If all boxes have the same value k:
        // Each player takes 1 from each box per round. After k rounds, all boxes are empty.
        // The last move is by the player at box n (round k). After that, the next player
        // (at box 1) faces an empty box. 
        // If k*n is even: last move by Tom (since Jerry starts, even moves = Tom).
        //   Next player is Jerry at box 1 (empty). Jerry loses. Tom wins.
        // If k*n is odd: last move by Jerry. Next player is Tom at box 1. Tom loses. Jerry wins.
        //
        // For n=2, a=[10,10]: k=10, k*n=20 (even). Tom wins. 
        // For n=1, a=[10]: k=10, k*n=10 (even). Tom wins? But we said Jerry wins!
        //
        // Wait, for n=1: Jerry takes from box 1. If Jerry takes all 10, box is empty.
        // Tom faces empty box 1. Tom loses. Jerry wins.
        // But k*n = 10 (even), so Tom should win. Contradiction!
        //
        // The issue: Jerry doesn't have to take 1 each time. He can take all 10 at once.
        // So the "take 1 each time" strategy is not optimal.
        //
        // For n=1: Jerry takes all 10. Game ends immediately. Tom loses. Jerry wins.
        // For n=2, a=[10,10]: 
        // Jerry takes some from box 1. Tom takes from box 2.
        // If Jerry takes all 10 from box 1: box 1 empty.
        //   Tom at box 2. Tom takes some. Jerry at box 1 (empty). Jerry loses.
        //   So Jerry shouldn't take all from box 1.
        // Jerry takes 9 from box 1. Box 1 has 1 left.
        //   Tom at box 2. Tom takes some. Jerry at box 1 (takes 1, box empty).
        //   Tom at box 2. Tom takes some. Jerry at box 1 (empty). Jerry loses.
        //   Wait, after Jerry empties box 1, the next player at box 1 is Tom (after n-1=1 more move).
        //   Tom at box 2. Tom takes some. Jerry at box 1 (empty). Jerry loses.
        //   
        // Hmm, so for n=2, a=[10,10], Jerry always loses?
        // Let me think more carefully.
        //
        // The game: moves alternate between boxes 1 and 2.
        // Jerry at box 1, Tom at box 2, Jerry at box 1, Tom at box 2, ...
        // The game ends when a player faces an empty box.
        //
        // If Jerry empties box 1 on his move: the next move is Tom at box 2.
        //   Tom takes from box 2. Then Jerry at box 1 (empty). Jerry loses.
        //   So emptying box 1 is bad for Jerry.
        //
        // If Tom empties box 2 on his move: the next move is Jerry at box 1.
        //   Jerry takes from box 1. Then Tom at box 2 (empty). Tom loses.
        //   So emptying box 2 is bad for Tom.
        //
        // So both players want to avoid emptying their box.
        // But eventually, someone must empty a box.
        //
        // The key: the player who is forced to empty a box loses (indirectly).
        // Actually, the player who empties a box doesn't lose immediately.
        // The loser is the player who faces the empty box AFTER it's emptied.
        //
        // For n=2:
        // Jerry at box 1. If Jerry empties box 1, Tom at box 2, Jerry at box 1 (empty). Jerry loses.
        // Tom at box 2. If Tom empties box 2, Jerry at box 1, Tom at box 2 (empty). Tom loses.
        //
        // So: emptying box 1 causes Jerry to lose (2 moves later).
        // Emptying box 2 causes Tom to lose (2 moves later).
        //
        // The game: both players try to force the other to empty a box.
        // But they can control how many coins to take.
        //
        // If a[1] > a[2]: Jerry can take 1 from box 1 each time. Tom must take from box 2.
        //   After a[2] rounds, box 2 is empty (Tom emptied it). Tom loses.
        //   But Jerry also takes from box 1 each round. After a[2] rounds, box 1 has a[1]-a[2] left.
        //   Then Tom at box 2 (empty). Tom loses. Jerry wins.
        //   
        // If a[1] < a[2]: Tom can take 1 from box 2 each time. Jerry must take from box 1.
        //   After a[1] rounds, box 1 is empty (Jerry emptied it). Jerry loses.
        //   
        // If a[1] = a[2]: Both take 1 each round. After a[1] rounds, both empty.
        //   The last move: if a[1] is odd, Jerry empties box 1. Tom at box 2 (empty). Tom loses.
        //   If a[1] is even, Tom empties box 2. Jerry at box 1 (empty). Jerry loses.
        //
        // Wait, let me re-examine. For n=2, a=[10,10]:
        // Both take 1 each round. Round 1: Jerry takes 1 from box 1 (9 left). Tom takes 1 from box 2 (9 left).
        // Round 2: Jerry takes 1 from box 1 (8 left). Tom takes 1 from box 2 (8 left).
        // ...
        // Round 10: Jerry takes 1 from box 1 (0 left). Tom takes 1 from box 2 (0 left).
        // Round 11: Jerry at box 1 (empty). Jerry loses.
        //
        // But Jerry could take 2 from box 1 in round 1:
        // Round 1: Jerry takes 2 from box 1 (8 left). Tom takes 1 from box 2 (9 left).
        // Round 2: Jerry takes 1 from box 1 (7 left). Tom takes 1 from box 2 (8 left).
        // ...
        // This doesn't help Jerry.
        //
        // What if Jerry takes 10 from box 1 in round 1 (empties it)?
        // Round 1: Jerry empties box 1. Tom takes from box 2 (9 left).
        // Round 2: Jerry at box 1 (empty). Jerry loses.
        //
        // So for n=2, a=[10,10], Jerry always loses. Tom wins. Matches sample!
        //
        // For n=2, a=[30,50]:
        // Jerry takes 1 from box 1 each time. Tom takes from box 2.
        // After 30 rounds: box 1 empty (Jerry emptied it). Box 2 has 50-30=20 left.
        // Tom at box 2. Tom takes from box 2. Jerry at box 1 (empty). Jerry loses.
        //
        // But what if Jerry takes more from box 1?
        // Jerry takes 2 from box 1 each time. After 15 rounds: box 1 empty.
        // Tom takes 1 from box 2 each time. After 15 rounds: box 2 has 35 left.
        // Tom at box 2. Jerry at box 1 (empty). Jerry loses.
        //
        // It seems like Jerry always loses for n=2 when a[1] <= a[2].
        //
        // What about n=2, a=[50,30]?
        // Jerry takes 1 from box 1 each time. Tom takes from box 2.
        // After 30 rounds: box 2 empty (Tom emptied it). Box 1 has 20 left.
        // Jerry at box 1. Tom at box 2 (empty). Tom loses. Jerry wins!
        //
        // So for n=2: Jerry wins iff a[1] > a[2].
        //
        // For general n: this is more complex. Let me think about it.
        //
        // For n=1: Jerry wins (always, since he can empty the only box).
        // For n=2: Jerry wins iff a[1] > a[2].
        // For n=3: ?
        //
        // Actually, I think the pattern is:
        // Jerry wins iff the first element is the unique maximum.
        // No, that's not right either.
        //
        // Let me think about it as a race: each player tries to force the other to empty a box.
        // The "rate" at which each player empties boxes depends on their strategy.
        //
        // For general n: the game is played in rounds. In each round, each box is visited once.
        // The player at box i in round r is determined by (i-1+r-1) % n.
        // Jerry is at odd positions in the sequence (1st, 3rd, 5th, ...).
        // Tom is at even positions (2nd, 4th, 6th, ...).
        //
        // The key: who empties which box?
        // Box i is visited by Jerry if (i-1) is even (i is odd), or by Tom if (i-1) is odd (i is even).
        // Wait, that's only for the first round. In subsequent rounds, the pattern shifts.
        //
        // Actually, the pattern is:
        // Move 1: Jerry at box 1.
        // Move 2: Tom at box 2.
        // ...
        // Move n: (n is odd? Jerry : Tom) at box n.
        // Move n+1: (n+1 is odd? Jerry : Tom) at box 1.
        // ...
        //
        // So Jerry visits boxes 1, 3, 5, ... (odd-indexed) in the first round,
        // and then boxes 2, 4, 6, ... (even-indexed) in the second round, etc.
        //
        // This is getting complex. Let me try a different approach.
        //
        // Observation: the game is equivalent to a "token" moving around the circle.
        // The token starts at box 1. Each move, the current player takes from the current box
        // and the token moves to the next box.
        // The game ends when the token reaches an empty box.
        //
        // The total number of moves is: the first time the token reaches a box that's been emptied.
        //
        // Each player controls how many coins to take from each box they visit.
        // A player wants to maximize the number of moves before an empty box is reached
        // (if they're winning) or minimize it (if they're losing).
        //
        // Actually, both players play optimally. The outcome depends on the initial configuration.
        //
        // Let me think about it as: the game is determined by the "critical box" - the box
        // that gets emptied first. The player who empties it doesn't lose; the player who
        // faces it after it's emptied loses.
        //
        // For the game to end at box i: box i must be emptied on some move, and the next
        // player at box i (after n-1 more moves) faces an empty box.
        //
        // The player who empties box i is determined by the move number.
        // Move k empties box ((k-1) % n + 1). The player at move k is Jerry if k is odd,
        // Tom if k is even.
        //
        // After box i is emptied at move k, the next player at box i is at move k+n.
        // The player at move k+n is Jerry if k+n is odd, Tom if k+n is even.
        // Since n can be odd or even: if n is even, k and k+n have the same parity.
        //   So the same player who emptied box i faces it again. That player loses!
        // If n is odd, k and k+n have different parity. The other player faces it and loses.
        //
        // So:
        // If n is even: the player who empties a box loses (faces it again after n moves).
        // If n is odd: the player who empties a box wins (the other player faces it).
        //
        // For n even: both players try to avoid emptying a box. The game continues until
        // someone is forced to empty a box. The player forced to empty loses.
        //
        // For n odd: both players try to empty a box. The player who empties first wins.
        //
        // This changes the strategy significantly!
        //
        // For n even:
        // The game is a "misère" game: players try to avoid emptying a box.
        // Each player takes 1 coin from each box they visit (to avoid emptying).
        // The game continues until a box has only 1 coin left and it's a player's turn.
        // That player must empty it (take the last coin) and loses.
        //
        // The player who faces a box with 1 coin is determined by the parity of the
        // number of visits to that box.
        //
        // For box i with a[i] coins: it's visited every n moves. After a[i]-1 visits
        // (taking 1 each time), it has 1 coin left. The a[i]-th visit empties it.
        // The move number of the a[i]-th visit to box i is: (a[i]-1)*n + i.
        // The player at that move is Jerry if it's odd, Tom if even.
        // Since n is even: (a[i]-1)*n is even. So the parity is determined by i.
        // If i is odd: Jerry empties box i. Jerry loses.
        // If i is even: Tom empties box i. Tom loses.
        //
        // But wait, the game might end before all boxes are visited a[i] times.
        // The game ends when the first box is emptied.
        //
        // For n even: the first box to be emptied determines the loser.
        // The box with the smallest a[i] is emptied first.
        // If multiple boxes have the same minimum, the one with the smallest index is emptied first.
        //
        // Actually, all boxes are visited at the same rate (once per n moves).
        // So the box with the smallest a[i] is emptied first.
        // If a[i] is the minimum, the move number of emptying is (a[i]-1)*n + i.
        // The player at that move loses.
        //
        // But players can take more than 1 coin per visit! This changes the timing.
        //
        // If a player takes more than 1 coin, they empty the box sooner, which might
        // cause them to lose (if n is even) or win (if n is odd).
        //
        // For n even: players take 1 coin per visit to delay emptying.
        // The game is determined by: which box has the smallest a[i], and who empties it.
        //
        // For n odd: players take as many coins as possible to empty boxes quickly.
        // The game is determined by: which box can be emptied first, and by whom.
        //
        // This is getting very complex. Let me just look at the sample outputs and try
        // to find a pattern.
        //
        // Sample 1: n=1, a=[10]. Jerry wins.
        // Sample 1: n=2, a=[30,50]. Tom wins.
        // Sample 1: n=2, a=[30,50]. Tom wins.
        //
        // For n=2, a=[30,50]: n is even. Both players take 1 per visit.
        // Box 1 (30 coins): emptied at move 29*2+1 = 59. Jerry (odd) loses.
        // Box 2 (50 coins): emptied at move 49*2+2 = 100. Tom (even) loses.
        // First to be emptied: box 1 at move 59. Jerry loses. Tom wins. Matches!
        //
        // For n=2, a=[10,10]: Box 1 emptied at move 19. Jerry loses. Box 2 at move 20. Tom loses.
        // First: box 1. Jerry loses. Tom wins.
        //
        // For n=1, a=[10]: n is odd. Jerry can empty box 1 immediately. Jerry wins.
        //
        // So for n even: find the box with the smallest a[i]. The player who empties it loses.
        // Box i is emptied at move (a[i]-1)*n + i.
        // If (a[i]-1)*n + i is odd: Jerry empties it. Jerry loses.
        // If even: Tom empties it. Tom loses.
        //
        // But if multiple boxes have the same minimum, we need to check all of them.
        // The first one to be emptied determines the loser.
        //
        // For n even: (a[i]-1)*n + i. Since n is even, (a[i]-1)*n is even.
        // So the parity is just i. If i is odd: Jerry loses. If i is even: Tom loses.
        // The box with the smallest a[i] (and smallest i if tied) is emptied first.
        // If that box has odd index: Jerry loses (Tom wins).
        // If even index: Tom loses (Jerry wins).
        //
        // For n odd: players try to empty boxes quickly. The first box to be emptied
        // determines the winner (the emptier wins).
        // Box i with a[i] coins: can be emptied in a[i] visits.
        // The move number: depends on strategy.
        // Actually, for n odd, the player who empties a box wins (the other faces it).
        // So both players try to empty boxes. The game is a race.
        //
        // For n odd: the player who empties the first box wins.
        // The first box to be emptied is the one with the smallest a[i].
        // Box i is emptied at move (a[i]-1)*n + i.
        // If this move is odd: Jerry empties it. Jerry wins.
        // If even: Tom empties it. Tom wins.
        //
        // Wait, but players can take more than 1 coin. For n odd, a player might want to
        // empty a box on their turn to win immediately.
        //
        // For n odd, box i with a[i] coins: the player at box i on the a[i]-th visit empties it.
        // The a[i]-th visit to box i is at move (a[i]-1)*n + i.
        // If this move is odd (Jerry's turn): Jerry empties it and wins.
        // If even (Tom's turn): Tom empties it and wins.
        //
        // But a player can also empty a box earlier by taking more coins.
        // For example, if box i has 5 coins and it's Jerry's turn (move k):
        // Jerry can take all 5, emptying the box. The next player at box i (move k+n) loses.
        // Since n is odd, k+n has different parity. So the other player loses. Jerry wins.
        //
        // So for n odd, the player who first gets a chance to empty a box can win.
        // The first chance to empty box i is at move i (first visit).
        // If i is odd: Jerry can empty box i on move i. Jerry wins.
        // If i is even: Tom can empty box i on move i. Tom wins.
        //
        // But the player might not want to empty a box immediately if it causes them to lose
        // in the long run. Actually, for n odd, emptying a box always wins (the other player
        // faces the empty box).
        //
        // So for n odd: the player with the first move (Jerry) can always win by emptying
        // box 1 on move 1. Unless box 1 is empty (but a[i] >= 1).
        //
        // Wait, Jerry can empty box 1 on move 1. The next player at box 1 is at move n+1.
        // If n is odd, n+1 is even (Tom's turn). Tom faces empty box 1. Tom loses. Jerry wins.
        //
        // So for n odd: Jerry always wins!
        //
        // But sample 2 says: n=3, a=[9,10,15]. Answer: Angry_Waston (Tom wins).
        // n=3 is odd. Jerry should always win. But the answer says Tom wins!
        //
        // So my analysis is wrong. Let me reconsider.
        //
        // For n=3, a=[9,10,15]:
        // Jerry at box 1 (move 1). If Jerry empties box 1 (takes 9):
        //   Tom at box 2 (move 2). Tom takes from box 2.
        //   Jerry at box 3 (move 3). Jerry takes from box 3.
        //   Tom at box 1 (move 4). Box 1 is empty. Tom loses. Jerry wins.
        //
        // So Jerry CAN win by emptying box 1. But the answer says Tom wins!
        //
        // Let me re-read the problem. Maybe I misunderstood the rules.
        //
        // "选择场上的一个数 a_i，将其除以其最大的质因子"
        // "选择场上的一个数 a_i，将其改为它自身的平方"
        //
        // Wait, these are different operations! Let me re-read.
        //
        // Oh wait, I was reading the wrong problem! Let me re-read B4379.
        // B4379 is about coins in boxes, not about dividing by prime factors.
        // The dividing by prime factor is P11899.
        //
        // Let me re-read B4379.
        
        // B4379: Jerry and Tom play a game with n boxes in a circle.
        // Jerry starts at box 1. Each turn, take at least 1 coin from current box.
        // Next player takes from next box. If box is empty on your turn, you lose.
        //
        // For n=2, a=[30,50]: Tom wins.
        // For n=1, a=[10]: Jerry wins.
        //
        // Let me reconsider my analysis for n odd.
        // For n=3, a=[9,10,15]:
        // If Jerry empties box 1 on move 1:
        //   Move 2: Tom at box 2. Tom takes some from box 2.
        //   Move 3: Jerry at box 3. Jerry takes some from box 3.
        //   Move 4: Tom at box 1 (empty). Tom loses. Jerry wins.
        //
        // So Jerry wins by emptying box 1. But the answer says Tom wins!
        //
        // Unless... the problem says Jerry MUST take from box 1 first, and the answer
        // depends on whether Jerry has a winning strategy.
        //
        // Wait, let me re-check the sample. The input is:
        // 4 (test cases)
        // 3
        // 9 10 15
        // Output: Angry_Waston (Tom wins)
        //
        // If Jerry empties box 1, Tom at box 2, Jerry at box 3, Tom at box 1 (empty). Tom loses.
        // So Jerry wins. But the answer says Tom wins!
        //
        // I must be misunderstanding the problem. Let me re-read carefully.
        
        // "初始场上有 n 个整数 a_1~a_n。两人轮流行动，某人行动时需从下面两种操作中选择一种执行：
        // - 选择场上的一个数 a_i，将其除以其最大的质因子。
        // - 选择场上的一个数 a_i，将其改为它自身的平方。"
        //
        // OH WAIT. This is P11899, not B4379! Let me re-read B4379.
        
        // B4379: "Jerry 和 Tom 正在进行一局游戏。他们准备了 n 个盒子...
        // Jerry 先手从 1 号盒子开始取；
        // 如果前一个玩家取的是 i 号盒子中的硬币，那么当前玩家必须从 i+1 号盒子中取硬币。
        // 如果轮到某位玩家时对应盒子中没有硬币，则该玩家失败。"
        //
        // OK so B4379 is the coin game. Let me re-examine the sample.
        // n=2, a=[30,50]. Jerry starts at box 1.
        // Jerry takes some from box 1. Tom takes from box 2. Jerry takes from box 1. Etc.
        //
        // For n=2: Jerry at boxes 1, 3, 5, ... (odd visits to box 1)
        //          Tom at boxes 2, 4, 6, ... (even visits to box 2)
        // Wait, the boxes alternate: 1, 2, 1, 2, 1, 2, ...
        // Jerry at box 1, Tom at box 2, Jerry at box 1, Tom at box 2, ...
        //
        // So Jerry only visits box 1, Tom only visits box 2.
        // Jerry can take at most 30 coins from box 1 (over multiple visits).
        // Tom can take at most 50 coins from box 2.
        //
        // The game ends when someone faces an empty box.
        // Jerry faces box 1. If box 1 is empty when Jerry's turn comes, Jerry loses.
        // Tom faces box 2. If box 2 is empty when Tom's turn comes, Tom loses.
        //
        // The number of visits to each box:
        // Box 1 is visited on moves 1, 3, 5, ... (Jerry's moves).
        // Box 2 is visited on moves 2, 4, 6, ... (Tom's moves).
        //
        // After k full rounds (2k moves): box 1 has been visited k times, box 2 has been visited k times.
        // If Jerry takes 1 from box 1 each time and Tom takes 1 from box 2 each time:
        // After 30 rounds: box 1 is empty (Jerry emptied it on move 59).
        //   Move 60: Tom at box 2 (has 20 left). Tom takes some.
        //   Move 61: Jerry at box 1 (empty). Jerry loses.
        //
        // So Jerry loses if he takes 1 from box 1 each time.
        // Can Jerry do better?
        //
        // If Jerry takes 2 from box 1 each time:
        // After 15 rounds: box 1 is empty (Jerry emptied it on move 29).
        //   Move 30: Tom at box 2 (has 35 left). Tom takes some.
        //   Move 31: Jerry at box 1 (empty). Jerry loses.
        //
        // If Jerry takes 30 from box 1 on move 1 (empties it):
        //   Move 2: Tom at box 2 (50). Tom takes some.
        //   Move 3: Jerry at box 1 (empty). Jerry loses.
        //
        // So Jerry always loses for n=2, a=[30,50]. Tom wins. Matches!
        //
        // The key: for n=2, Jerry always visits box 1, Tom always visits box 2.
        // Jerry is forced to empty box 1 eventually (he must take at least 1 each visit).
        // After Jerry empties box 1, Tom visits box 2, then Jerry faces empty box 1 and loses.
        //
        // So for n=2: Jerry always loses (Tom always wins)?
        // What about n=2, a=[50,30]?
        // Jerry at box 1 (50). Tom at box 2 (30).
        // If Tom empties box 2 first: Jerry at box 1, Tom at box 2 (empty). Tom loses.
        // Tom takes 1 from box 2 each time. After 30 rounds: box 2 empty.
        //   Move 60: Tom empties box 2. Move 61: Jerry at box 1 (has 20 left). Jerry takes some.
        //   Move 62: Tom at box 2 (empty). Tom loses. Jerry wins!
        //
        // So for n=2: Jerry wins iff a[1] > a[2].
        // Because Jerry empties box 1 after a[1] visits, Tom empties box 2 after a[2] visits.
        // The first to be emptied loses (because the other player faces the empty box after a full round).
        // Actually, the one who empties doesn't lose immediately. The one who faces the empty box loses.
        // After Jerry empties box 1 at move 2*a[1]-1: Tom at box 2, Jerry at box 1 (empty). Jerry loses.
        // After Tom empties box 2 at move 2*a[2]: Jerry at box 1, Tom at box 2 (empty). Tom loses.
        // First event: min(2*a[1]-1, 2*a[2]).
        // If 2*a[1]-1 < 2*a[2]: Jerry empties first. Jerry loses.
        //   2*a[1]-1 < 2*a[2] => a[1] <= a[2].
        // If 2*a[2] < 2*a[1]-1: Tom empties first. Tom loses.
        //   2*a[2] < 2*a[1]-1 => a[2] < a[1] - 0.5 => a[2] < a[1] => a[1] > a[2].
        // If equal: 2*a[1]-1 = 2*a[2] => a[1] = a[2] + 0.5. Not possible for integers.
        //
        // So for n=2: Jerry wins iff a[1] > a[2]. Tom wins iff a[1] <= a[2].
        // But what if a[1] = a[2]? Then 2*a[1]-1 = 2*a[2]-1 < 2*a[2]. Jerry empties first. Jerry loses.
        // So Tom wins when a[1] <= a[2]. Matches sample!
        //
        // For general n: the game is more complex because players visit multiple boxes.
        // But the key insight is: the player who is forced to empty a box first loses
        // (for even n) or wins (for odd n).
        //
        // Actually, let me reconsider for general n.
        // The token moves: box 1, 2, 3, ..., n, 1, 2, ...
        // Jerry at moves 1, 3, 5, ... Tom at moves 2, 4, 6, ...
        // Box i is visited at moves i, i+n, i+2n, ...
        // The player at move k is Jerry if k is odd, Tom if k is even.
        //
        // Box i is visited by Jerry if i is odd (first visit), or if i+n is odd (second visit), etc.
        // Since n can be odd or even, the pattern varies.
        //
        // For n even: box i is always visited by the same player.
        //   If i is odd: Jerry always visits box i.
        //   If i is even: Tom always visits box i.
        //   Each player is responsible for their own boxes.
        //   Jerry must empty all odd-indexed boxes. Tom must empty all even-indexed boxes.
        //   The game ends when the first box is emptied. The player who emptied it loses
        //   (because the other player faces the empty box after a full round).
        //   Wait, that's not right. After box i is emptied, the next player at box i is
        //   n moves later. If n is even, the same player faces it. That player loses.
        //   
        //   So for n even: each player empties their own boxes. The player who empties first loses.
        //   Jerry empties box i (odd) after a[i] visits. Move number: (a[i]-1)*n + i.
        //   Tom empties box j (even) after a[j] visits. Move number: (a[j]-1)*n + j.
        //   First empty: min over all boxes of (a[i]-1)*n + i.
        //   If the first empty is by Jerry (odd i): Jerry loses. Tom wins.
        //   If by Tom (even i): Tom loses. Jerry wins.
        //
        // For n odd: the player who visits a box alternates.
        //   Box i: first visit by player based on i's parity.
        //   Second visit: i+n. Since n is odd, parity flips.
        //   So box i is visited alternately by Jerry and Tom.
        //   
        //   After k visits to box i: the player who empties it is the one making the a[i]-th visit.
        //   The a[i]-th visit is at move (a[i]-1)*n + i.
        //   Player: Jerry if odd, Tom if even.
        //   
        //   After box i is emptied, the next player at box i is at move a[i]*n + i.
        //   Since n is odd, a[i]*n has the same parity as a[i].
        //   If a[i] is even: a[i]*n is even. Move a[i]*n + i: parity = i's parity.
        //   If a[i] is odd: a[i]*n is odd. Move a[i]*n + i: parity = 1-i's parity.
        //   
        //   This is getting complex. Let me just handle the cases.
        //
        // For n odd, box i is emptied at move (a[i]-1)*n + i.
        // The player at that move loses if n is even (same player faces it again).
        // For n odd, the player at that move wins (other player faces it).
        //
        // So for n odd: the player who empties a box first wins.
        // For n even: the player who empties a box first loses.
        //
        // The first box to be emptied: min over i of (a[i]-1)*n + i.
        // Let m = min a[i]. The first box to be emptied has a[i] = m.
        // Among boxes with a[i] = m, the one with the smallest i is emptied first.
        // Move number: (m-1)*n + i_min.
        // Player: Jerry if odd, Tom if even.
        //
        // For n odd: that player wins.
        // For n even: that player loses.
        //
        // Let me verify:
        // n=1, a=[10]: m=10, i_min=1. Move = 9*1+1 = 10. Player: Tom (even).
        //   n is odd: Tom wins? But answer says Jerry wins!
        //
        // Hmm, that's wrong. For n=1, Jerry empties box 1 on move 1 (takes all 10).
        // Move 1 is Jerry's. n is odd. Jerry wins. Correct!
        //
        // But my formula says the first empty is at move (10-1)*1+1 = 10. That's wrong!
        // Jerry doesn't have to take 1 each time. He can take all 10 on move 1.
        //
        // Ah, I see the issue. Players can take ANY number of coins (at least 1).
        // So they can empty a box earlier than my formula suggests.
        //
        // For n odd: the player who gets to a box first can empty it immediately.
        // The first move is Jerry at box 1. Jerry can empty box 1. Jerry wins.
        // So for n odd, Jerry always wins!
        //
        // But sample 2 says n=3, a=[9,10,15], Tom wins. n=3 is odd!
        //
        // There must be something wrong with my analysis. Let me re-read the problem.
        //
        // "如果前一个玩家取的是 i 号盒子中的硬币，那么当前玩家必须从 i+1 号盒子中取硬币。"
        // So the boxes are visited in order: 1, 2, 3, ..., n, 1, 2, ...
        // Jerry at box 1 (move 1). Tom at box 2 (move 2). Jerry at box 3 (move 3).
        // Tom at box 1 (move 4). Jerry at box 2 (move 5). Tom at box 3 (move 6).
        // ...
        //
        // For n=3: Jerry visits boxes 1, 3, 2, 1, 3, 2, ...
        // Tom visits boxes 2, 1, 3, 2, 1, 3, ...
        //
        // So Jerry and Tom alternate visiting ALL boxes!
        // Jerry at box 1 (move 1). Tom at box 2 (move 2). Jerry at box 3 (move 3).
        // Tom at box 1 (move 4). Jerry at box 2 (move 5). Tom at box 3 (move 6).
        //
        // For n=3, a=[9,10,15]:
        // Jerry at box 1 (move 1). If Jerry empties box 1 (takes 9):
        //   Tom at box 2 (move 2). Tom takes from box 2.
        //   Jerry at box 3 (move 3). Jerry takes from box 3.
        //   Tom at box 1 (move 4). Box 1 is empty. Tom loses. Jerry wins!
        //
        // So Jerry CAN win by emptying box 1. But the answer says Tom wins!
        //
        // I must be misunderstanding something. Let me re-read the problem statement
        // for P11899 (not B4379).
        
        // OH WAIT. I'm looking at the wrong problem! P11899 is "必胜" which is about
        // dividing by prime factors and squaring. B4379 is the coin game.
        // Let me re-check which problem I'm solving.
        //
        // The sample output for P11899 is:
        // 3
        // 1
        // 2
        // 2 2
        // 1
        // 4
        // Output: Lucky_Holmes, Draw, Angry_Waston
        //
        // That's P11899, not B4379!
        //
        // For B4379, the sample is:
        // 2
        // 1
        // 10
        // 2
        // 30 50
        // Output: Jerry, Tom
        //
        // So for n=1, a=[10]: Jerry wins. For n=2, a=[30,50]: Tom wins.
        //
        // For n=3, a=[9,10,15] (from P11899, not B4379):
        // This is a different problem entirely!
        //
        // Let me focus on B4379.
        // For n=3, a=[any]: who wins?
        //
        // For n=3, a=[1,1,1]:
        // Jerry at box 1 (move 1). Jerry takes 1 (box 1 empty).
        // Tom at box 2 (move 2). Tom takes 1 (box 2 empty).
        // Jerry at box 3 (move 3). Jerry takes 1 (box 3 empty).
        // Tom at box 1 (move 4). Box 1 empty. Tom loses. Jerry wins.
        //
        // For n=3, a=[1,1,2]:
        // Jerry at box 1 (move 1). Jerry takes 1 (box 1 empty).
        // Tom at box 2 (move 2). Tom takes 1 (box 2 empty).
        // Jerry at box 3 (move 3). Jerry takes 1 (box 3 has 1 left).
        // Tom at box 1 (move 4). Box 1 empty. Tom loses. Jerry wins.
        //
        // For n=3, a=[2,1,1]:
        // Jerry at box 1 (move 1). Jerry takes 1 (box 1 has 1 left).
        // Tom at box 2 (move 2). Tom takes 1 (box 2 empty).
        // Jerry at box 3 (move 3). Jerry takes 1 (box 3 empty).
        // Tom at box 1 (move 4). Tom takes 1 (box 1 empty).
        // Jerry at box 2 (move 5). Box 2 empty. Jerry loses. Tom wins.
        //
        // So for n=3: Jerry doesn't always win!
        //
        // The key insight I was missing: after emptying a box, the game continues.
        // The empty box causes the NEXT player at that box to lose.
        // But the game might continue for several more moves before that happens.
        //
        // For n=3, a=[2,1,1]:
        // Jerry at box 1 (take 1). Tom at box 2 (take 1, empty). Jerry at box 3 (take 1, empty).
        // Tom at box 1 (take 1, empty). Jerry at box 2 (empty). Jerry loses.
        //
        // The critical box is box 2 (emptied by Tom on move 2).
        // After box 2 is emptied, the next player at box 2 is at move 2+3=5.
        // Move 5 is Jerry (odd). Jerry faces empty box 2. Jerry loses.
        //
        // So for n=3 (odd): the player who empties a box causes the OTHER player to lose
        // (because n is odd, the parity flips after n moves).
        //
        // So for n odd: emptying a box is GOOD (the other player loses).
        // For n even: emptying a box is BAD (you lose, because the same player faces it after n moves).
        //
        // For n=3, a=[2,1,1]:
        // Tom empties box 2 on move 2. n=3 (odd). Jerry faces box 2 on move 5. Jerry loses.
        // Tom wins. Correct!
        //
        // For n=3, a=[1,1,1]:
        // Jerry empties box 1 on move 1. n=3 (odd). Tom faces box 1 on move 4. Tom loses.
        // Jerry wins. Correct!
        //
        // For n=3, a=[9,10,15]:
        // Who empties which box first?
        // Jerry at box 1 (move 1). Tom at box 2 (move 2). Jerry at box 3 (move 3).
        // Tom at box 1 (move 4). Jerry at box 2 (move 5). Tom at box 3 (move 6).
        // ...
        // Box 1 is visited at moves 1, 4, 7, 10, ... (Jerry, Tom, Jerry, Tom, ...)
        // Box 2 is visited at moves 2, 5, 8, 11, ... (Tom, Jerry, Tom, Jerry, ...)
        // Box 3 is visited at moves 3, 6, 9, 12, ... (Jerry, Tom, Jerry, Tom, ...)
        //
        // For n=3 (odd): emptying a box is good. Both players want to empty boxes.
        // The game is: who can empty a box first?
        //
        // Jerry at box 1 (move 1). Jerry can empty box 1 (takes 9).
        // Tom faces box 1 on move 4. Tom loses. Jerry wins!
        //
        // But the sample says Tom wins for P11899 with n=3, a=[9,10,15].
        // Wait, that's P11899, not B4379!
        //
        // For B4379, there's no sample with n=3. Let me just implement the solution
        // based on my analysis and see if it works.
        
        // Summary:
        // For n even: the player who empties a box first loses.
        //   Each player is responsible for specific boxes (Jerry: odd, Tom: even).
        //   The first box to be emptied determines the loser.
        //   Box i (odd, Jerry's) is emptied after a[i] visits. Move: (a[i]-1)*n + i.
        //   Box j (even, Tom's) is emptied after a[j] visits. Move: (a[j]-1)*n + j.
        //   But players can take more than 1 coin! So they can empty boxes earlier.
        //   
        //   For n even: Jerry empties his boxes (odd indices), Tom empties his (even indices).
        //   The first empty: Jerry empties box i at move (a[i]-1)*n + i.
        //   Tom empties box j at move (a[j]-1)*n + j.
        //   First empty: min over all.
        //   If Jerry's box empties first: Jerry loses (n even, same player faces it).
        //   If Tom's box empties first: Tom loses.
        //   
        //   But players can accelerate emptying! Jerry can empty box i earlier by taking more.
        //   The earliest Jerry can empty box i is move i (take all a[i] on first visit).
        //   The earliest Tom can empty box j is move j (take all a[j] on first visit).
        //   
        //   For n even: emptying is bad. So players delay.
        //   The optimal strategy: take 1 coin per visit. This maximizes the number of visits
        //   before emptying.
        //   
        //   With "take 1 per visit":
        //   Jerry empties box i at move (a[i]-1)*n + i.
        //   Tom empties box j at move (a[j]-1)*n + j.
        //   First empty: min over all boxes.
        //   If it's a Jerry box (odd i): Jerry loses.
        //   If it's a Tom box (even j): Tom loses.
        //
        // For n odd: emptying is good. Both players want to empty boxes ASAP.
        //   The first empty: the player who empties wins.
        //   Jerry can empty box 1 on move 1. Jerry wins!
        //   But wait, Tom might be able to empty a box on move 2.
        //   If Jerry doesn't empty box 1, Tom at box 2 can empty it on move 2.
        //   Then Jerry faces box 2 on move 2+3=5. Jerry loses. Tom wins.
        //   
        //   So for n odd: Jerry must empty box 1 on move 1 to win.
        //   If Jerry empties box 1: Tom at box 2. Jerry at box 3. Tom at box 1 (empty). Tom loses.
        //   Jerry wins!
        //   
        //   But what if Jerry doesn't want to empty box 1?
        //   If Jerry takes 1 from box 1: Tom at box 2. Tom can empty box 2.
        //   Then Jerry at box 3. Tom at box 1. Jerry at box 2 (empty). Jerry loses.
        //   Tom wins.
        //   
        //   So for n odd: Jerry should empty box 1 on move 1. Jerry wins.
        //   Unless... there's a reason not to?
        //   
        //   For n=3, a=[2,1,1]:
        //   Jerry at box 1 (move 1). If Jerry empties box 1:
        //     Tom at box 2 (move 2). Tom empties box 2.
        //     Jerry at box 3 (move 3). Jerry empties box 3.
        //     Tom at box 1 (move 4). Box 1 empty. Tom loses. Jerry wins.
        //   
        //   But earlier I said Tom wins for a=[2,1,1]! Let me recheck.
        //   
        //   Jerry at box 1 (take 1, box 1 has 1 left). Tom at box 2 (take 1, empty).
        //   Jerry at box 3 (take 1, empty). Tom at box 1 (take 1, empty).
        //   Jerry at box 2 (empty). Jerry loses.
        //   
        //   In this case, Jerry didn't empty box 1 on move 1. He took only 1.
        //   Then Tom emptied box 2 on move 2. n=3 (odd). Jerry faces box 2 on move 5. Jerry loses.
        //   
        //   But if Jerry empties box 1 on move 1:
        //   Tom at box 2 (take 1, empty). Jerry at box 3 (take 1, empty).
        //   Tom at box 1 (empty). Tom loses. Jerry wins.
        //   
        //   So Jerry SHOULD empty box 1 on move 1. Then Jerry wins.
        //   
        //   But the "optimal" play for Tom: if Jerry empties box 1, Tom at box 2.
        //   Tom can take 1 from box 2 (not empty it). Then Jerry at box 3.
        //   Jerry can take 1 from box 3. Tom at box 1 (empty). Tom loses.
        //   
        //   So regardless of Tom's strategy, Jerry wins by emptying box 1 on move 1.
        //   
        //   But earlier I computed that for a=[2,1,1], Tom wins. Let me recheck.
        //   
        //   Jerry at box 1 (move 1). Jerry takes 1 (box 1 has 1 left).
        //   Tom at box 2 (move 2). Tom takes 1 (box 2 empty).
        //   Jerry at box 3 (move 3). Jerry takes 1 (box 3 empty).
        //   Tom at box 1 (move 4). Tom takes 1 (box 1 empty).
        //   Jerry at box 2 (move 5). Box 2 empty. Jerry loses.
        //   
        //   In this line, Jerry didn't empty box 1 on move 1. That was a mistake.
        //   If Jerry empties box 1 on move 1:
        //   Tom at box 2 (move 2). Tom takes 1 (box 2 empty).
        //   Jerry at box 3 (move 3). Jerry takes 1 (box 3 empty).
        //   Tom at box 1 (move 4). Box 1 empty. Tom loses. Jerry wins.
        //   
        //   So Jerry wins! Not Tom!
        //   
        //   Let me recheck my earlier claim that Tom wins for a=[2,1,1].
        //   I think I made an error. Let me retrace:
        //   Jerry at box 1. Jerry empties box 1 (takes 2).
        //   Tom at box 2. Tom takes 1 (box 2 empty).
        //   Jerry at box 3. Jerry takes 1 (box 3 empty).
        //   Tom at box 1 (empty). Tom loses. Jerry wins.
        //   
        //   Yes, Jerry wins! My earlier analysis was wrong because I assumed Jerry takes 1.
        //   
        //   So for n=3: Jerry always wins by emptying box 1 on move 1.
        //   Is this always true for n odd?
        //   
        //   For n=3, a=[1,1,1]: Jerry empties box 1. Tom at box 2 (empty). 
        //   Jerry at box 3 (empty). Tom at box 1 (empty). Tom loses. Jerry wins.
        //   
        //   For n=3, a=[1,100,100]: Jerry empties box 1. Tom at box 2.
        //   Tom takes from box 2. Jerry at box 3. Tom at box 1 (empty). Tom loses. Jerry wins.
        //   
        //   So for n odd: Jerry always wins!
        //   
        //   For n even: the outcome depends on the box values.
        //   Jerry is responsible for odd-indexed boxes, Tom for even-indexed.
        //   With "take 1 per visit" (optimal for delaying):
        //   Jerry empties box i (odd) at move (a[i]-1)*n + i.
        //   Tom empties box j (even) at move (a[j]-1)*n + j.
        //   First empty: min over all.
        //   If it's a Jerry box: Jerry loses.
        //   If it's a Tom box: Tom loses.
        //
        // Let me implement this.
        
        // Actually, wait. For n even, players might not take 1 per visit.
        // If Jerry takes more from a box, he empties it sooner, which is bad for him.
        // So Jerry takes 1 per visit. Similarly, Tom takes 1 per visit.
        // This is the optimal strategy for both.
        
        // For n even:
        // Compute the "emptying time" for each box: (a[i]-1)*n + i.
        // Find the minimum.
        // If it's an odd-indexed box: Jerry loses (Tom wins).
        // If it's an even-indexed box: Tom loses (Jerry wins).
        // If there's a tie: need to check who actually loses.
        //   If both empty at the same time: the one who empties first (lower move number) loses.
        //   But if they have the same move number, they empty simultaneously? No, moves are sequential.
        //   The minimum move number determines the first empty.
        
        // For n odd: Jerry always wins.
        
        if (n % 2 == 1) {
            cout << "Jerry\n";
        } else {
            long long minTime = 1e18;
            int minBox = -1;
            for (int i = 0; i < n; i++) {
                long long t = (a[i] - 1) * n + (i + 1);
                if (t < minTime) { minTime = t; minBox = i; }
            }
            // minBox is 0-indexed. Box (minBox+1) is 1-indexed.
            if ((minBox + 1) % 2 == 1) {
                // Odd-indexed box (Jerry's). Jerry empties it first. Jerry loses.
                cout << "Tom\n";
            } else {
                // Even-indexed box (Tom's). Tom empties it first. Tom loses.
                cout << "Jerry\n";
            }
        }
    }
    return 0;
}
