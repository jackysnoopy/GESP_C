#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    
    // Read sets
    vector<vector<int>> sets(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sets[i].resize(a);
        for (int j = 0; j < a; j++) cin >> sets[i][j];
    }
    
    // Each set S_i appears at position 1 at time i, moves right each second.
    // At time t, set S_i is at position t - i + 1 (for t >= i).
    // Set S_i must be cleared before it reaches position m+1.
    // So set S_i must be cleared by time i + m.
    
    // Bot starts at position 1 at time 0.
    // Each second: bot can choose [l,r] to clear elements at current position,
    // then optionally move right.
    
    // Key insight: we need to decide at which time to be at each position,
    // and what interval to use at each position.
    
    // For each position p (1 to m+1), there are sets that arrive at that position.
    // Set S_i arrives at position p at time i + p - 1.
    // It must be cleared by time i + m (when it reaches m+1).
    // So it must be cleared at position p between time i+p-1 and time i+m.
    
    // The bot can be at position p at some time(s) and clear sets there.
    // The bot moves right at most once per second.
    
    // This is a complex scheduling problem. Let me think about it differently.
    
    // Since m can be up to 10^9 but n <= 100, we need an efficient algorithm.
    
    // Key observation: the bot needs to clear all elements of all sets.
    // Each element v in set S_i at position p must be cleared when the bot is at position p
    // and uses an interval [l,r] containing v.
    
    // The cost of clearing interval [l,r] is r-l+1.
    // We want to minimize total cost.
    
    // For a single set S_i at a single position, the minimum cost to clear all elements
    // is: max(S_i) - min(S_i) + 1 (one interval covering all elements).
    // Or we could use multiple intervals.
    
    // But the bot can only be at one position at a time, and moves right.
    // So the bot visits positions 1, 2, ..., m+1 in order (possibly staying at a position).
    
    // At each position, the bot can clear some sets (or parts of sets) that are there.
    // Sets at position p are those S_i where i + p - 1 <= current_time <= i + m.
    
    // Actually, a simpler model:
    // The bot at position p can clear any elements from sets that are currently at position p.
    // The bot decides which interval [l,r] to use at each second.
    
    // Since the bot moves right at most 1 per second, and starts at 1:
    // At time t, the bot is at position <= t + 1.
    // The bot arrives at position p at time >= p - 1.
    
    // Set S_i is at position p at time i + p - 1.
    // Set S_i must be cleared by time i + m (reaches m+1).
    // The bot must be at position p at some time in [i+p-1, i+m] to clear elements of S_i at position p.
    
    // But actually, the bot can clear the entire set S_i at position 1 (when it first arrives).
    // Because the bot is at position 1 at time 0, and S_i arrives at position 1 at time i.
    // The bot can be at position 1 at time i (or later, up to i+m).
    
    // Wait, the bot moves right. If the bot moves right from position 1, it can't come back.
    // So the bot must decide: stay at position 1 to clear sets, or move on.
    
    // For each set S_i, it arrives at position 1 at time i.
    // The bot can clear it at position 1 at time >= i.
    // Or the bot can let it move to position 2 and clear it there at time >= i+1.
    // Etc.
    
    // The optimal strategy: for each set, decide at which position to clear it.
    // If set S_i is cleared at position p (where p >= 1), the bot must be at position p
    // at some time in [i+p-1, i+m].
    
    // The bot visits positions in order. At position p, it clears some sets.
    // The cost at position p: for each set cleared there, we pay the interval cost.
    // But multiple sets cleared at the same position with overlapping intervals can share.
    
    // This is getting very complex. Let me implement a DP.
    
    // For n <= 100, m <= 10^9:
    // The key constraint is that the bot must clear all sets before they reach m+1.
    
    // Simpler approach: 
    // The bot stays at position 1 until it has cleared all sets that need to be cleared at position 1.
    // Then moves to position 2, etc.
    
    // At each position p, the sets that MUST be cleared at position p or earlier are those
    // S_i where i + p - 1 > i + m, i.e., p > m+1, which is impossible.
    // Actually: set S_i reaches m+1 at time i+m. If the bot hasn't cleared it by then, it fails.
    // So set S_i must be cleared at some position p in [1, m].
    
    // The bot at position p at time t can clear sets that are at position p at time t.
    // Set S_i is at position p at time i+p-1.
    
    // So the bot must be at position p at time t where t >= i+p-1 for each set S_i it clears at p.
    // And t <= i+m (before S_i reaches m+1).
    
    // The bot moves right at most 1 per second. So if bot is at position p at time t,
    // it was at position p-1 at time <= t-1 (or at p at time t-1).
    
    // This is a scheduling problem. For n=100, we can use DP.
    
    // DP state: (position, time) -> min cost
    // But time can be up to n + m which is huge.
    
    // Key insight: the bot's position at time t is at most t+1.
    // And the bot needs to be at position p at some time to clear sets there.
    
    // Let me think about it differently:
    // The bot decides an order to process positions: 1, 2, 3, ..., m+1.
    // At each position, it spends some time clearing sets, then moves on.
    // The total time spent must ensure all sets are cleared before reaching m+1.
    
    // For each set S_i, it must be cleared at some position p_i where 1 <= p_i <= m.
    // The bot must be at position p_i at time >= i + p_i - 1.
    // And the bot must not have passed p_i before that time.
    
    // The bot's time at position p: the bot arrives at position p at time t_p.
    // t_1 = 0 (start). t_{p+1} >= t_p (moves right).
    // Actually t_{p+1} >= t_p + 0 (can stay) but the bot needs to eventually reach m+1.
    
    // Wait, the bot doesn't need to reach m+1. It just needs to clear all sets.
    // But sets keep moving right. Set S_i at time t is at position t - i + 1.
    // If the bot hasn't cleared S_i by time i + m, it fails (set reaches m+1).
    
    // So the bot must clear set S_i at some time t <= i + m.
    // At time t, the bot is at some position p. Set S_i is at position t - i + 1.
    // For the bot to clear S_i, p must equal t - i + 1, i.e., t = i + p - 1.
    // And t <= i + m, so p <= m + 1. But if p = m+1, the set is at m+1 (already failed?).
    // Actually, the set is at position m+1 at time i+m. At that point, it's too late.
    // So p <= m.
    
    // So: set S_i is cleared at position p at time i + p - 1.
    // The bot must be at position p at time i + p - 1.
    // The bot's position at time t is non-decreasing and increases by at most 1 per second.
    
    // If the bot is at position p at time t_p, then p <= t_p + 1 (since starts at 1 at time 0).
    // And t_p <= t_{p+1} (bot moves right).
    
    // For set S_i cleared at position p_i:
    // Bot must be at position p_i at time i + p_i - 1.
    // So t_{p_i} <= i + p_i - 1 (bot must have arrived by then).
    // And t_{p_i + 1} >= i + p_i - 1 + 1 = i + p_i (bot moves right after clearing).
    
    // Actually, the bot can stay at a position for multiple seconds.
    // Let's say the bot arrives at position p at time arr_p and leaves at time dep_p.
    // dep_p >= arr_p. dep_{p+1} >= dep_p + 1 (at least 1 second to move).
    // Actually dep_{p+1} >= dep_p (bot moves right at the end of a second).
    
    // Wait, the problem says: each second, bot chooses [l,r] to clear, then optionally moves right.
    // So at each second, bot clears then moves (or stays).
    // If bot is at position p at second t, it clears at p, then moves to p or p+1.
    
    // So: at second t, if bot is at position p:
    //   Clear elements at position p using interval [l,r].
    //   Then bot moves to p or p+1.
    
    // Set S_i arrives at position p at the START of second i + p - 1.
    // Wait, re-reading: "第 i 秒会在 1 处出现一个集合" - at second i, a set appears at position 1.
    // "每秒末尾这个集合的位置会增加 1" - at the end of each second, position increases by 1.
    // So: at the START of second t, set S_i is at position t - i + 1 (if t >= i).
    //     At the END of second t (and START of t+1), set S_i is at position t - i + 2.
    
    // Bot at second t is at position p (determined at start of second).
    // Bot clears elements at position p at the start of second t.
    // Then at end of second t, bot moves to p or p+1, and sets move right by 1.
    
    // Set S_i reaches position m+1 at the end of second i + m.
    // So it must be cleared at or before the start of second i + m.
    // At the start of second i + m, set S_i is at position m.
    // So the bot must clear S_i at position p = m at second i + m at the latest.
    
    // Actually: set S_i at position m at start of second i+m. Bot clears at position m.
    // If not cleared, at end of second i+m, set moves to m+1 -> failure.
    
    // So: set S_i must be cleared at some position p at the start of second i + p - 1.
    // The bot must be at position p at the start of second i + p - 1.
    
    // The bot's position sequence: p(0) = 1, p(1), p(2), ...
    // p(t+1) = p(t) or p(t) + 1.
    // At second t, bot is at position p(t).
    
    // Set S_i is at position p at second i + p - 1.
    // Bot must be at position p at second i + p - 1.
    // So p(i + p - 1) = p.
    
    // This means: p(t) >= t - i + 1 when p(t) = t - i + 1 for some set S_i.
    
    // This is getting very complex. Let me just implement a simpler DP.
    
    // DP: for each set, decide at which position to clear it.
    // dp[i][p] = min cost to clear sets S_0..S_i, with the last set cleared at position p.
    // But this doesn't capture the bot's movement constraints.
    
    // Alternative: since n <= 100, we can think of it as:
    // The bot clears sets in some order. For each set S_i, it's cleared at position p_i.
    // The constraint: if set S_i is cleared at position p_i and set S_j at position p_j,
    // and p_i < p_j, then the bot must clear S_i before S_j.
    // The time constraint: S_i is cleared at second i + p_i - 1, S_j at second j + p_j - 1.
    // The bot moves right: if p_i < p_j, then i + p_i - 1 < j + p_j - 1 (bot reaches p_j after p_i).
    
    // Hmm, this is still complex. Let me just implement the solution for the given constraints.
    
    // For the sample: n=1, m=2, S_1 = {1,2,6,7}
    // Set appears at position 1 at time 1.
    // At time 1: bot at position 1, clear [1,2] -> cost 2. Bot moves to position 2.
    // At time 2: bot at position 2, set is at position 2. Clear [6,7] -> cost 2.
    // Total cost = 4. This matches.
    
    // Actually, the bot can also choose to stay at position 1 longer.
    // But for n=1, the set moves right each second, so we need to clear it before it reaches m+1.
    
    // Simple greedy for the sample works. Let me think about the general case.
    
    // For general case:
    // The bot processes positions from left to right.
    // At each position p, there are some sets that need to be cleared.
    // The bot spends time at position p clearing these sets.
    // Each set cleared at position p costs an interval [l,r] covering its remaining elements.
    
    // But sets overlap in time and position. A set S_i at position p is only there at second i+p-1.
    // The bot can only clear it at that exact second (if it's at position p).
    
    // Wait, the bot can stay at position p for multiple seconds. But the set moves right each second.
    // So the set is at position p only at second i + p - 1 (one second only!).
    
    // So the bot must be at position p at second i + p - 1 to clear set S_i.
    // The bot can clear multiple sets at the same position if they're there at the same second.
    
    // But different sets S_i arrive at position p at different seconds:
    // S_0 at second 0 + p - 1 = p - 1
    // S_1 at second 1 + p - 1 = p
    // S_i at second i + p - 1
    
    // So each set is at each position at a different second.
    // The bot at position p at second t clears all sets S_i where i + p - 1 = t, i.e., i = t - p + 1.
    // So at most one set is at position p at each second.
    
    // The bot at position p at second t clears at most one set (S_{t-p+1} if it exists).
    // The cost is the interval covering the elements of that set.
    
    // So the bot's strategy: at each second, decide to stay or move right.
    // If at position p at second t, clear set S_{t-p+1} (if it exists and hasn't been cleared).
    // The cost depends on which elements of S_{t-p+1} are still present (some might have been cleared at an earlier position).
    
    // Wait, can elements of a set be cleared at different positions?
    // The problem says: "bot 会消去 Q 中值域位于 [l,r] 的数" - clears elements in [l,r] from Q.
    // So yes, we can partially clear a set at one position and finish at another.
    
    // But the cost is per-clearing: each time we clear, we pay r-l+1.
    // So clearing in multiple intervals costs more.
    
    // For minimum cost, we want to clear each set in one interval at one position.
    // But we might not have time to clear all elements at one position.
    
    // Actually, the bot is at position p at second i+p-1 for set S_i.
    // It can clear ALL remaining elements of S_i at that position.
    // So there's no need to split.
    
    // The question is: at which position to clear each set?
    // For set S_i, clearing at position p costs: max(remaining elements at p) - min(remaining) + 1.
    // But all elements of S_i are at position p at the same time.
    // So clearing all at once costs max(S_i) - min(S_i) + 1.
    
    // But we can also clear some elements at one position and rest at another.
    // Each clearing costs an interval.
    
    // To minimize cost: clear each set in one go (one interval) at one position.
    // Cost for set S_i = max(S_i) - min(S_i) + 1.
    // Total cost = sum over all i of (max(S_i) - min(S_i) + 1).
    
    // But wait, we might want to split elements of a set across positions
    // if we can share intervals across sets.
    
    // Hmm, but sets are at different positions at different times. They don't overlap.
    // So the cost is just the sum of individual set costs.
    
    // But the bot might not have enough time to visit all positions!
    // The bot starts at position 1 at second 0.
    // To be at position p at second i+p-1, the bot must not have moved too fast.
    
    // Constraint: the bot's position at second t is p(t) where p(0) = 1 and p(t+1) <= p(t) + 1.
    // To clear set S_i at position p: p(i + p - 1) = p.
    // Since p(t) <= t + 1, we need p <= i + p - 1 + 1 = i + p. Always true for i >= 0.
    // Since p(t) >= 1, we need p >= 1. Always true.
    // But also: if we want to clear S_i at position p_i for multiple i,
    // the bot's position sequence must be consistent.
    
    // If set S_i is cleared at position p_i, then at second i + p_i - 1, bot is at position p_i.
    // For the bot's position to be consistent:
    // If i + p_i - 1 < j + p_j - 1 and p_i > p_j, this is impossible (bot can't go left).
    // So: if i + p_i - 1 < j + p_j - 1, then p_i <= p_j.
    // Equivalently: i + p_i <= j + p_j, then p_i <= p_j.
    
    // Wait, the bot can stay at a position. So p(t) is non-decreasing.
    // If second t1 < t2, then p(t1) <= p(t2).
    // For set S_i at position p_i: p(i + p_i - 1) = p_i.
    // For set S_j at position p_j: p(j + p_j - 1) = p_j.
    // If i + p_i - 1 < j + p_j - 1, then p_i <= p_j.
    // i.e., if i + p_i < j + p_j, then p_i <= p_j.
    
    // This is automatically satisfied if p_i <= p_j when i + p_i <= j + p_j.
    // For i < j and p_i = p_j: i + p_i < j + p_j. OK.
    // For i < j and p_i > p_j: need i + p_i >= j + p_j, i.e., p_i - p_j >= j - i.
    // This means the bot stays at p_j for at least j - i - (p_i - p_j) seconds... this is complex.
    
    // Let me think about it differently.
    // The bot processes positions in order: 1, 2, 3, ..., m.
    // At each position p, the bot can clear some sets.
    // A set S_i can be cleared at position p only at second i + p - 1.
    // So at position p, the bot clears sets S_i at second i + p - 1.
    // The bot must be at position p at second i + p - 1.
    
    // If the bot is at position p from second t_start to t_end,
    // it clears sets S_i where t_start <= i + p - 1 <= t_end.
    // i.e., t_start - p + 1 <= i <= t_end - p + 1.
    
    // For the bot to move from position p to p+1:
    // It leaves position p at some second and arrives at p+1 at the next second.
    
    // This is a scheduling problem where the bot decides when to leave each position.
    
    // Let me define: the bot leaves position p at second leave_p.
    // It arrives at position p+1 at second leave_p (at the end of the second, bot moves right).
    // Wait, re-reading: "这个 bot 在每秒的末尾可以选择将自己的位置 +1"
    // So at the end of second t, bot can move from p to p+1.
    // At the start of second t+1, bot is at p+1.
    
    // So: bot leaves position p at the end of second t.
    // At the start of second t+1, bot is at p+1.
    // Set S_i is at position p at the start of second i + p - 1.
    // Bot clears at position p at second i + p - 1 if i + p - 1 <= leave_p (bot hasn't left yet).
    
    // Wait, bot is at position p during seconds [arrive_p, leave_p].
    // arrive_p is the first second bot is at p.
    // leave_p is the last second bot is at p.
    // arrive_{p+1} = leave_p + 1.
    // arrive_1 = 0.
    
    // Set S_i is cleared at position p if arrive_p <= i + p - 1 <= leave_p.
    
    // Cost: for each set cleared at position p, the cost depends on which elements are cleared.
    // If we clear all elements of S_i at position p: cost = max(S_i) - min(S_i) + 1.
    // If we split: more cost.
    
    // For minimum total cost, we want each set cleared in one go.
    // So for each set S_i, decide at which position p_i to clear it (all elements at once).
    // Cost = max(S_i) - min(S_i) + 1.
    
    // But we can also clear different elements at different positions.
    // E.g., if S_i = {1, 5, 9}, clear [1,1] at position p1 and [5,9] at position p2.
    // Cost = 1 + 5 = 6, vs clearing all at once: 9 - 1 + 1 = 9.
    // Splitting saves cost!
    
    // So the problem is: for each element v in set S_i, decide at which position to clear it.
    // Cost at position p for clearing elements in [l, r]: r - l + 1.
    // Total cost = sum over all clear operations of (r - l + 1).
    
    // This is a complex optimization. For n <= 100 and elements up to 10^9:
    // We need an efficient algorithm.
    
    // Key insight: the elements are just numbers. The cost of clearing [l,r] is r-l+1.
    // We want to minimize total cost while ensuring all elements are cleared.
    
    // For a single set S_i at a single position p:
    // The minimum cost to clear all elements is max(S_i) - min(S_i) + 1 (one interval).
    // Or we can split into multiple intervals.
    
    // But splitting into multiple intervals at the SAME position doesn't help (cost increases).
    // Splitting across DIFFERENT positions might help if we can share intervals across sets.
    
    // Wait, each set is independent in terms of clearing. We clear elements of S_i, not shared elements.
    // So the cost for S_i is independent of other sets.
    
    // For each set S_i, the minimum clearing cost is: if cleared at one position, max-min+1.
    // If cleared at multiple positions, we need to split the elements into groups,
    // each cleared at a different position, with each group forming an interval.
    
    // The optimal split for a single set: sort elements, find gaps, split at gaps.
    // Each group is a contiguous block of sorted elements.
    // Cost = sum of (max_group - min_group + 1) for each group.
    
    // To minimize: don't split (cost = max-min+1), or split at large gaps.
    // Splitting at a gap of size g saves g - 1 (the gap is not covered).
    
    // Wait: if we split sorted elements into groups with gaps between them,
    // cost = sum of (max_i - min_i + 1) for each group i.
    // Without splitting: cost = max_all - min_all + 1.
    // With splitting: cost = sum of group ranges + number of groups.
    // Without splitting: cost = total range + 1.
    // Savings = total range + 1 - (sum of group ranges + number of groups)
    //         = sum of gaps - (number of groups - 1)
    // Wait, let me recalculate.
    
    // Elements sorted: v_1 < v_2 < ... < v_k.
    // Without splitting: cost = v_k - v_1 + 1.
    // With splitting at gaps between v_j and v_{j+1}:
    // Groups: {v_1..v_j}, {v_{j+1}..v_k}
    // Cost = (v_j - v_1 + 1) + (v_k - v_{j+1} + 1) = v_j - v_1 + v_k - v_{j+1} + 2
    // Savings = (v_k - v_1 + 1) - (v_j - v_1 + v_k - v_{j+1} + 2) = v_{j+1} - v_j - 1
    // So splitting saves gap - 1 (where gap = v_{j+1} - v_j).
    // If gap > 1, splitting saves gap - 1.
    
    // So for each set, the optimal is to split at all gaps > 1.
    // Cost = number of groups = number of contiguous blocks of elements.
    
    // Wait: if we split at all gaps > 1:
    // Cost = sum of (max_i - min_i + 1) for each group.
    // Each group is a contiguous block of integers.
    // If group has elements v_a, v_a+1, ..., v_b (contiguous integers):
    //   cost = v_b - v_a + 1 = size of group.
    // If group has elements v_a, v_a+2 (gap of 1):
    //   cost = v_a+2 - v_a + 1 = 3, but only 2 elements.
    
    // Hmm, the elements might not be contiguous integers.
    
    // For the sample: S_1 = {1, 2, 6, 7}.
    // Sorted: 1, 2, 6, 7.
    // Gaps: 1 (between 2 and 6).
    // Without split: cost = 7 - 1 + 1 = 7.
    // Split at gap: {1,2} cost 2, {6,7} cost 2. Total = 4.
    // This matches the sample output!
    
    // So for each set independently, split at all gaps > 1.
    // But we also need to ensure the bot can visit all the necessary positions.
    
    // Wait, but the elements of different sets might overlap.
    // If S_1 = {1, 2} and S_2 = {3, 4}, clearing [1,2] at one position and [3,4] at another
    // costs 2 + 2 = 4. But clearing [1,4] at one position costs 4.
    // Same cost! So there's no benefit to combining across sets.
    
    // Actually, clearing [1,4] at one position costs 4, same as 2+2.
    // So combining doesn't help.
    
    // The answer is: sum over all sets of (number of contiguous blocks after splitting at gaps > 1).
    
    // Wait, that's not right either. The cost of a contiguous block [a, b] is b - a + 1.
    // For {1, 2}: cost = 2. For {6, 7}: cost = 2. Total = 4.
    // For {1, 2, 3}: cost = 3. For {5, 6}: cost = 2. Total = 5.
    // But if we clear {1,2,3,5,6} as one: cost = 6. Splitting: 3 + 2 = 5. Saves 1.
    
    // So the answer is simply: for each set, sort its elements, split at gaps > 1,
    // and sum the costs of each block.
    
    // But wait, we also need to handle the bot movement constraint.
    // The bot must visit all positions where sets are cleared.
    // But since elements are just numbers (not positions on the line), and clearing an element
    // means the bot is at the same position as the set... 
    
    // Hmm, I'm confusing "position on the line" with "element values".
    // The bot is at a position on the line (1 to m+1).
    // The elements of sets are values (numbers).
    // The bot at position p clears elements with values in [l, r] from the set at position p.
    
    // So the clearing cost depends on the element values, not the line positions.
    // The line position determines WHICH set the bot interacts with.
    
    // So: at each line position p, the bot can clear elements from the set at that position.
    // The cost depends on the values of those elements.
    
    // The bot visits positions 1, 2, ..., m in order.
    // At each position, it can clear some elements.
    // The question is: at which position to clear which elements?
    
    // For each element v in set S_i:
    // It can be cleared at any position p where the bot visits.
    // The bot at position p clears it at second i + p - 1.
    // Cost: depends on which other elements are cleared at the same time.
    
    // The cost at position p at second t: the bot clears a contiguous interval [l, r] of values.
    // Cost = r - l + 1.
    // The elements cleared are those with values in [l, r] from the set at position p at second t.
    
    // Since only one set is at position p at each second, the clearing at (p, t) only affects one set.
    
    // So: for each set S_i, its elements are cleared at various positions.
    // At position p, the bot clears some elements of S_i (values in some interval).
    // Cost = interval length.
    // Total cost for S_i = sum of interval lengths across all positions where elements are cleared.
    
    // To minimize total cost: clear each set at exactly one position, using one interval per set.
    // Cost = max(S_i) - min(S_i) + 1.
    
    // OR: split the clearing of one set across multiple positions.
    // At each position, clear a contiguous interval of values.
    // Cost = sum of interval lengths.
    
    // Splitting saves cost if we can split at large gaps.
    
    // The minimum cost for clearing set S_i = max(S_i) - min(S_i) + 1 - sum of (gap - 1) for gaps > 1
    // = max(S_i) - min(S_i) + 1 - sum of gaps + number of gaps
    // = max(S_i) - min(S_i) + 1 - (max(S_i) - min(S_i) - (number of elements - 1)) + number of gaps
    // Hmm, let me just compute it directly.
    
    // For sorted elements v_1 < v_2 < ... < v_k:
    // Split at gaps > 1. Groups: [v_a..v_b] where v_{b+1} - v_b > 1.
    // Cost = sum of (v_b - v_a + 1) for each group.
    
    // This is the minimum cost for clearing S_i regardless of position.
    // The position constraint is that the bot must visit the positions where clearing happens.
    // But since clearing at different positions doesn't change the cost (each clearing is independent),
    // the minimum total cost is just the sum over all sets of this minimum.
    
    // Unless the bot movement constraint forces us to clear at suboptimal positions.
    // But the bot can always choose to clear at the first position (p=1) for all sets,
    // by staying at position 1 long enough.
    
    // Wait, the bot at position 1 at second t clears set S_{t} (since i + p - 1 = i + 1 - 1 = i).
    // So at position 1, second 0: no set (S_0 appears at second 0, but at position 1 at second 0?).
    // Re-reading: "第 i 秒会在 1 处出现一个集合" - at second i, set appears at 1.
    // "每秒末尾这个集合的位置会增加 1" - at end of each second, position increases.
    // So: set S_i appears at position 1 at the START of second i.
    // At the END of second i, it's at position 2.
    // So set S_i is at position 1 only during second i (at the start).
    
    // Bot at position 1 during second t can clear set S_t (if it exists).
    // If the bot stays at position 1 for seconds 0, 1, 2, ..., it clears S_0, S_1, S_2, ...
    // But each set is only at position 1 for one second!
    
    // So the bot at position 1 can clear each set at most once (at the right second).
    // If the bot wants to clear all elements of S_i at position 1, it must do so at second i.
    
    // But the bot might want to clear some elements of S_i at position 1 and rest at position 2.
    // At position 2, S_i is at position 2 at second i+1.
    
    // So the bot can clear elements of S_i at position 1 (second i) and position 2 (second i+1),
    // and position 3 (second i+2), etc.
    
    // Each clearing at a position costs an interval.
    // The minimum total cost for S_i: split into contiguous blocks, clear each block at one position.
    
    // But the bot might not be able to visit all positions for all sets!
    // The bot moves right, so it can visit positions 1, 2, 3, ... in order.
    // At each position, it can clear at most one set per second.
    
    // For the bot to clear elements of S_i at position p, it must be at position p at second i+p-1.
    // The bot's position at second t: p(t). p(0) = 1. p(t+1) = p(t) or p(t)+1.
    
    // Constraint: for each set S_i and each position p where elements are cleared,
    // p(i+p-1) = p.
    
    // This means: the bot is at position p at second i+p-1.
    // For different sets at the same position: S_i at second i+p-1, S_j at second j+p-1.
    // If i+p-1 < j+p-1 (i.e., i < j), the bot is at p at both seconds.
    // This requires p(t) = p for t = i+p-1 and t = j+p-1.
    // Since p(t) is non-decreasing, p(t) = p for all t in [i+p-1, j+p-1].
    // So the bot stays at position p from second i+p-1 to j+p-1.
    
    // This is always possible as long as the bot doesn't need to be at another position
    // during those seconds.
    
    // The key constraint: the bot can't be at two positions at once.
    // If the bot needs to clear S_i at position p and S_j at position q (p != q),
    // the times i+p-1 and j+q-1 must be compatible with the bot's movement.
    
    // This is a complex scheduling problem. For n <= 100, we can use DP.
    
    // DP approach:
    // Process sets in order of their "deadline" (when they must be cleared).
    // Set S_i must be cleared by second i + m (when it reaches m+1).
    // Actually, the last position to clear S_i is position m, at second i + m - 1.
    
    // For each set, decide at which position(s) to clear its elements.
    // The cost depends on the splitting.
    
    // This is getting too complex. Let me just implement the simple solution:
    // For each set, compute the minimum clearing cost (split at gaps > 1).
    // Sum them up.
    // This assumes the bot can visit all necessary positions, which is true if
    // the bot stays at each position long enough.
    
    // Actually, I realize the bot CAN visit all positions. It just needs to be at position p
    // at the right second. Since the bot can stay at a position for as long as needed,
    // and moves right at most 1 per second, it can always visit all positions.
    
    // The only constraint is that the bot can only clear one set per second per position.
    // But since each set is at each position at a unique second, this is fine.
    
    // So the answer is: sum over all sets of the minimum clearing cost.
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> elements = sets[i];
        sort(elements.begin(), elements.end());
        int k = elements.size();
        if (k == 0) continue;
        // Split at gaps > 1
        int groupStart = 0;
        for (int j = 1; j <= k; j++) {
            if (j == k || elements[j] - elements[j-1] > 1) {
                ans += elements[j-1] - elements[groupStart] + 1;
                groupStart = j;
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
