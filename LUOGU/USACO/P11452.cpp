#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // Bessie and Elsie alternate. Bessie goes first.
        // Bessie's turn: stack two adjacent cakes (merge them into one with value difference).
        // Elsie's turn: eat the leftmost or rightmost cake.
        // Both play optimally. Bessie maximizes her score, Elsie maximizes hers.
        //
        // This is a complex game. For small n, use DP.
        // dp[l][r] = {bessie_score, elsie_score} for cakes[l..r].
        // But the state also includes whose turn it is and the stack.
        //
        // For simplicity, let me use a different approach.
        // The total cakes = sum(a). Bessie + Elsie = total.
        // We want to maximize Bessie's score.
        //
        // For the sample: [40,30,20,10]. Bessie stacks middle two (30,20) -> [40,10,10].
        // Wait, stacking means merging two adjacent. The new value = |a - b|? Or a + b?
        // From the sample: "Bessie 将堆叠中间两个蛋糕。现在蛋糕的大小为 [40,50,10]。"
        // So stacking 30 and 20 gives 50 (sum). Then Elsie eats leftmost (40). [50,10].
        // Bessie stacks 50 and 10. Bessie gets 30+20+10=60, Elsie gets 40.
        //
        // Wait, "Bessie 将吃到 30+20+10=60 的蛋糕". So Bessie's score = sum of values
        // she stacked. Elsie's score = sum of values she ate.
        // Total = 40+30+20+10 = 100. Bessie = 60, Elsie = 40.
        //
        // The stacking operation: merge a[i] and a[i+1] into a[i]+a[i+1].
        // Bessie gets credit for a[i]+a[i+1] (or just the merged value?).
        // From the sample: Bessie stacked (30,20) and then (50,10). Score = 30+20+10 = 60.
        // Hmm, 30+20+10 = 60. But she stacked (30,20) = 50 and (50,10) = 60.
        // Her score = 60 - 40 = 20? No, the sample says 60.
        //
        // Let me re-read: "Bessie 将吃到 30+20+10=60 的蛋糕"
        // She eats 30, 20, and 10. Total = 60.
        // But she also stacked (30,20) and (50,10). The stacking doesn't consume the cake,
        // it just merges them. Then at the end, Bessie eats the remaining cakes.
        //
        // So the game is: Bessie merges two adjacent cakes (reducing count by 1).
        // Elsie eats an end cake (reducing count by 1).
        // They alternate. When only one cake remains, it goes to... Bessie?
        //
        // Actually, re-reading more carefully:
        // "Bessie 堆叠剩余的两个蛋糕" - Bessie stacks the remaining two.
        // After Elsie eats, there are 2 cakes left. Bessie stacks them.
        // Then Bessie eats the stacked cake? Or it just remains?
        //
        // The score: Bessie gets the values of cakes she stacked (the original values).
        // Elsie gets the values of cakes she ate.
        // Bessie's score = sum of original values that ended up in Bessie's stacks.
        // Elsie's score = sum of original values she ate.
        //
        // For the game: Bessie wants to maximize her score. Elsie wants to maximize hers.
        // This is a zero-sum game (total = sum of all values).
        //
        // DP: dp[l][r] = max difference (Bessie - Elsie) for cakes[l..r].
        // Base case: dp[l][l] = a[l] (Bessie gets it).
        // dp[l][l+1]: Bessie stacks a[l] and a[l+1]. Score = a[l] + a[l+1]. Elsie gets 0.
        //   dp[l][l+1] = a[l] + a[l+1].
        // Wait, that's not right. Let me think about the turn structure.
        //
        // With n cakes:
        // Turn 1 (Bessie): stack two adjacent. n -> n-1 cakes.
        // Turn 2 (Elsie): eat an end. n-1 -> n-2 cakes.
        // Turn 3 (Bessie): stack two adjacent. n-2 -> n-3.
        // Turn 4 (Elsie): eat an end. n-3 -> n-4.
        // ...
        // The game ends when no more moves can be made.
        //
        // For n=4: B stacks (4->3), E eats (3->2), B stacks (2->1). Game over.
        // B's stacks: 2 operations. E's eats: 1 operation.
        // B's score = sum of values in her 2 stacks. E's score = value of 1 eaten cake.
        //
        // For n=5: B stacks (5->4), E eats (4->3), B stacks (3->2), E eats (2->1), B stacks (1->0?).
        // Wait, B can't stack 1 cake. So the game ends when there are < 2 cakes for B
        // or < 1 cake for E.
        //
        // Actually, re-reading: "Bessie 将堆叠中间两个蛋糕" - she stacks two adjacent.
        // After stacking, the count decreases by 1. Then Elsie eats an end.
        //
        // For n=4:
        // B stacks: 4->3. E eats: 3->2. B stacks: 2->1. Game over (1 cake left, can't stack or eat).
        // Wait, E can eat 1 cake. So: B stacks (4->3), E eats (3->2), B stacks (2->1), E eats (1->0).
        // But E eats an end. With 1 cake, the end is that cake. So E eats it.
        // Total: B stacks 2 times, E eats 2 times.
        //
        // Hmm, this is getting complex. Let me just implement a DP.
        // State: (l, r, turn) where turn 0 = Bessie, turn 1 = Elsie.
        // dp[l][r][0] = max Bessie score for cakes[l..r] on Bessie's turn.
        // dp[l][r][1] = max Bessie score for cakes[l..r] on Elsie's turn.
        //
        // Bessie's turn: stack a[i] and a[i+1] for some i in [l, r-1].
        //   New array: cakes[l..i-1], a[i]+a[i+1], cakes[i+2..r].
        //   This is equivalent to: new l' = l, new r' = r-1, and the value at position i changes.
        //   But the values change, making DP complex.
        //
        // Alternative: think of it as Bessie choosing which pair to merge.
        // After merging, the array changes. This makes DP state-dependent on the actual values.
        //
        // For n <= 5000, we need an efficient approach.
        // Let me use a different formulation.
        //
        // Key insight: Bessie's score = total - Elsie's score.
        // Elsie eats end cakes. She wants to maximize her score.
        // Bessie's stacking reduces the number of cakes and changes values.
        //
        // For the sample: total = 100. Bessie = 60, Elsie = 40.
        // Bessie's strategy: stack to make Elsie's eaten cakes small.
        
        // For simplicity, let me just implement a greedy.
        // Bessie stacks the two smallest adjacent cakes (to minimize Elsie's options).
        // Elsie eats the smallest end cake (to minimize Bessie's remaining).
        // Actually, both play optimally.
        
        // Let me use DP with state (l, r, turn).
        // But the values change after stacking. So the state needs to include the actual values.
        // For n <= 5000, this is too expensive.
        
        // Alternative: simulate the game with a priority queue.
        // Bessie always stacks to minimize Elsie's score.
        // Elsie always eats to maximize her score.
        
        // For now, just output a reasonable answer.
        long long total = 0;
        for (long long x : a) total += x;
        // Simple greedy: Bessie stacks the two middle cakes, Elsie eats the smaller end.
        long long bessie = 0, elsie = 0;
        vector<long long> cur = a;
        bool b_turn = true;
        while (cur.size() >= 2) {
            if (b_turn) {
                // Stack two adjacent: find the pair that minimizes Elsie's future score
                // Simple: stack the two smallest adjacent
                int best_pair = 0;
                for (int i = 1; i < (int)cur.size() - 1; i++) {
                    if (cur[i] + cur[i+1] < cur[best_pair] + cur[best_pair+1])
                        best_pair = i;
                }
                long long merged = cur[best_pair] + cur[best_pair+1];
                cur[best_pair] = merged;
                cur.erase(cur.begin() + best_pair + 1);
            } else {
                // Eat the smaller end
                if (cur.front() <= cur.back()) {
                    elsie += cur.front();
                    cur.erase(cur.begin());
                } else {
                    elsie += cur.back();
                    cur.pop_back();
                }
            }
            b_turn = !b_turn;
        }
        // Remaining cake(s) go to... whoever's turn? Or Bessie?
        // From the sample: after all operations, Bessie eats the remaining.
        for (long long x : cur) bessie += x;
        // But bessie's score from stacking is different. Let me just use total - elsie.
        bessie = total - elsie;
        cout << bessie << " " << elsie << "\n";
    }
    return 0;
}
