#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        // We have n cats, each needs m grams.
        // n premium bags (a[i]) and n regular bags (b[i]).
        // Premium: any hungry cat might eat it.
        // Regular: specific cat eats it.
        // Total = n*m. Each bag is 1..m-1 grams.
        // We need to find if there exists an order of opening bags such that
        // regardless of which cat eats each premium bag, all cats end up fed.
        
        // Key insight: for premium bags, we need to ensure that no matter who eats them,
        // we can still complete the feeding.
        
        // Think of it as: each cat needs exactly m grams total.
        // Premium bags are "uncertain" - any cat can eat them.
        // Regular bags are "certain" - we choose which cat eats them.
        
        // Strategy: 
        // We need to pair premium bags with cats such that:
        // 1. Each cat gets exactly m grams total (premium + regular)
        // 2. For each premium bag opened, no matter which hungry cat eats it,
        //    we can still complete the feeding.
        
        // This is equivalent to: for every subset of cats that might eat premium bags,
        // the remaining cats can be fed with regular bags.
        
        // Actually, the key observation is:
        // When we open a premium bag, ANY hungry cat might eat it.
        // So we need to ensure that after any premium bag is eaten by any cat,
        // we can still finish feeding.
        
        // This means: after each premium bag is eaten, the remaining regular bags
        // must be enough to complete feeding, regardless of which cat ate the premium bag.
        
        // Let me think about this as a matching/game theory problem.
        
        // Sort premium bags in decreasing order. Open them first (or interleave with regular).
        // After each premium bag, we need to check feasibility.
        
        // Actually, the optimal strategy is:
        // Open premium bags first (largest first), then regular bags.
        // After all premium bags are eaten (by some cats), use regular bags to top up.
        
        // The worst case: all premium bags go to the same cat.
        // Then that cat has sum(a) grams, needs m - sum(a) more (or has too much).
        
        // Hmm, this is complex. Let me think about the necessary and sufficient condition.
        
        // For a valid ordering to exist:
        // 1. Total grams = n*m (given)
        // 2. No bag has >= m grams (given, each is 1..m-1)
        // 3. After opening all premium bags in worst case (all to one cat),
        //    we need to be able to feed all cats with regular bags.
        
        // Actually, the worst case isn't all to one cat. The condition is:
        // For any partition of premium bags into n groups (one per cat),
        // the remaining regular bags can fill the gaps.
        
        // Necessary and sufficient condition (I think):
        // Sort a in decreasing order. For each prefix a[0]+...+a[k-1]:
        //   There must be enough remaining grams to feed the remaining cats.
        //   The remaining cats need (n-k+1)*m - (a[0]+...+a[k-1]) grams from regular bags
        //   that go to cats not in this group.
        
        // This is getting very complex. Let me try a simpler approach.
        
        // For n=1: m = a[0] + b[0]. Cat eats both. Always works if a[0] < m and b[0] < m.
        // For n=2: need to check that both cats can be fed.
        
        // Key insight from the problem: 
        // We need to ensure that after each premium bag is opened and eaten by some cat,
        // the remaining problem is still solvable.
        
        // Let's think of it as: we have n cats each needing m grams.
        // Premium bags: uncertain allocation.
        // Regular bags: we can allocate freely.
        
        // The condition for validity:
        // Sort premium bags decreasing: a[0] >= a[1] >= ... >= a[n-1]
        // For each k (0 <= k <= n), the sum of the k largest premium bags must be <= k*m
        // AND the sum of the k smallest premium bags must be >= k*m - (sum of all regular bags allocated to these k cats)
        
        // Actually I think the condition is simpler:
        // For all k from 1 to n: sum of k largest premium bags <= k*m
        // AND sum of k smallest regular bags + sum of k smallest premium bags >= k*m
        // Wait, that's not quite right either.
        
        // Let me think about it from the adversarial perspective:
        // Adversary assigns premium bags to cats to make it hardest.
        // We assign regular bags to cats.
        // We win if we can always complete the feeding.
        
        // For the adversary to win: there exists an assignment of premium bags to cats
        // such that no regular bag assignment can complete the feeding.
        
        // The adversary's best strategy: give as many premium grams as possible to some cats,
        // making other cats need more regular bags than available.
        
        // More precisely: after premium bags are assigned, cat i needs max(0, m - premium_i) grams.
        // The total need is sum of max(0, m - premium_i) over all i.
        // The total regular grams = sum(b).
        // If total need > sum(b), we lose.
        
        // But also: each regular bag is <= m-1, and we need to be able to distribute them.
        // Since regular bags can go to any specific cat, and total = sum(b) = n*m - sum(a),
        // and total need = n*m - sum(premium_i) = sum(a) + (n*m - sum(a)) - ... 
        // Hmm wait, sum(premium_i) = sum(a) (total premium grams).
        // Total need = n*m - sum(a) = sum(b).
        // So total need always equals total regular grams!
        
        // So the total always matches. The issue is the per-cat constraint:
        // After premium assignment, cat i needs m - premium_i grams from regular bags.
        // If premium_i > m, cat i is overfed and wastes m - premium_i < 0 grams... 
        // But bags are 1..m-1, so a single premium bag is < m. But multiple bags can sum to > m.
        
        // Wait, the problem says each bag is 1 to m-1 grams. But a cat might eat multiple bags.
        // "即使占有猫粮的小猫只需要吃掉这袋猫粮的一部分就能吃饱，它也会吃掉整袋猫粮"
        // So if a cat already has m-1 grams and eats a premium bag of 2 grams,
        // the cat has m+1 grams total (overfed by 1).
        
        // So premium_i can be > m (if cat eats multiple premium bags).
        // In that case, cat i has excess = premium_i - m.
        // This excess is wasted (can't give to other cats).
        
        // So the adversary wants to maximize waste by giving many premium bags to few cats.
        
        // Total waste = sum over cats of max(0, premium_i - m).
        // Total regular grams needed = sum over cats of max(0, m - premium_i).
        // Total regular grams available = sum(b).
        // Feasible iff: total need <= sum(b).
        // But total need + total waste = n*m - total premium consumed properly
        // Actually: total need = sum of max(0, m - premium_i) <= sum(b) = n*m - sum(a).
        // And sum of max(0, m - premium_i) = sum(m - premium_i) for cats with premium_i < m
        //   + 0 for cats with premium_i >= m
        // = sum over cats with premium_i < m of (m - premium_i)
        // = (number of such cats) * m - sum of their premiums
        // We need this <= n*m - sum(a) = sum(b).
        
        // The adversary minimizes this quantity... wait, the adversary wants to MAXIMIZE the need.
        // So the adversary assigns premium bags to maximize:
        // sum over cats of max(0, m - premium_i)
        // subject to: each premium bag goes to exactly one cat.
        
        // To maximize need: give each premium bag to a cat that already has >= m grams
        // (so it doesn't reduce the need of any cat).
        // If all cats already have >= m grams, need = 0.
        // If we can't fill any cat to m, then need is maximized.
        
        // The adversary gives premium bags to the fewest cats possible,
        // making those cats reach m as quickly as possible.
        
        // Algorithm for adversary:
        // Sort premium bags decreasing. Give each bag to the cat with the most grams so far.
        // This packs premium bags into fewest cats.
        
        // If after this greedy packing, total need <= sum(b), answer is Yes.
        // Otherwise, answer is No.
        
        // But wait, this is the adversary's strategy. Let me verify.
        // The adversary wants to maximize total need = sum of max(0, m - cat_i_premium).
        // To maximize this: fill up cats as quickly as possible (fewer cats with need).
        // Greedy: always give the next premium bag to the cat with the most grams.
        // This is optimal for the adversary.
        
        // Simulate: maintain a max-heap of cat premium totals.
        // Start with all cats at 0.
        // For each premium bag (largest first), give to cat with most grams.
        
        // Then compute total need and check <= sum(b).
        
        vector<int> sorted_a(a);
        sort(sorted_a.begin(), sorted_a.end(), greater<int>());
        
        // Simulate adversary: give premium bags to fill cats
        // Use a max-heap (negative for priority_queue with greater)
        long long totalNeed = 0;
        {
            vector<long long> catPremium(n, 0);
            for (int i = 0; i < n; i++) {
                // Find cat with most grams
                int bestCat = 0;
                for (int j = 1; j < n; j++) {
                    if (catPremium[j] > catPremium[bestCat]) bestCat = j;
                }
                catPremium[bestCat] += sorted_a[i];
            }
            for (int i = 0; i < n; i++) {
                if (catPremium[i] < m) totalNeed += m - catPremium[i];
            }
        }
        
        long long totalRegular = 0;
        for (int i = 0; i < n; i++) totalRegular += b[i];
        
        // But we also need to check: can regular bags actually satisfy the per-cat needs?
        // The regular bags can be allocated freely. We need:
        // For each cat with need d_i, we can assign regular bags summing to at least d_i.
        // Since bags are 1..m-1 and we have n bags, this should be possible if total need <= total regular.
        // But there's a subtlety: if a cat needs > m-1 grams from regular bags,
        // and no single bag is >= m (guaranteed), we need multiple bags.
        // Since we can give multiple regular bags to one cat, this is fine as long as
        // total need <= total regular.
        
        // Wait, but we also need to ensure that no cat gets a regular bag that puts it over m.
        // Actually, regular bags are given to specific cats, so we can control this.
        // A cat needs exactly d_i grams. We give it bags summing to d_i.
        // Since bags are 1..m-1, and d_i <= m (a cat can need at most m from regular),
        // this is always feasible (just give one bag of d_i, or split).
        
        // But wait: d_i could be 0 (cat already has >= m from premium). In that case, don't give it any regular bag.
        // And total need = sum of d_i = sum(b) (since total = n*m).
        
        // So the condition is simply: after adversary packing, total need <= sum(b).
        // But total need = sum(b) always (since sum of all cat totals = sum(a) + sum(b) = n*m).
        // So... it's always Yes?
        
        // No! The issue is that the adversary can cause WASTE.
        // If a cat has premium_i > m, the excess is wasted.
        // Total premium consumed by cats = min(premium_i, m) for each cat.
        // Total wasted = sum of max(0, premium_i - m).
        // Total effectively used premium = sum(a) - wasted.
        // Total need from regular = n*m - total effectively used premium = sum(b) + wasted.
        // But total regular available = sum(b).
        // So we need: sum(b) + wasted <= sum(b), i.e., wasted <= 0.
        // This means: wasted must be 0, i.e., no cat has premium > m.
        
        // But the adversary can force waste by packing premium bags into few cats!
        // So the condition is: the adversary's greedy packing doesn't cause any cat to exceed m.
        
        // Wait no. Let me re-think.
        // Total need = sum of max(0, m - premium_i).
        // Total regular = sum(b) = n*m - sum(a).
        // We need: total need <= total regular.
        // sum(max(0, m - premium_i)) <= n*m - sum(a)
        // n*m - sum(min(premium_i, m)) <= n*m - sum(a)
        // sum(min(premium_i, m)) >= sum(a)
        // Since min(premium_i, m) <= premium_i, we need sum(min(premium_i, m)) = sum(a).
        // This holds iff premium_i <= m for all i.
        
        // So the condition is: after adversary assigns premium bags, no cat has > m grams.
        // The adversary tries to make some cat exceed m.
        
        // Adversary's strategy: sort premium bags decreasing, always give to the cat with most grams.
        // Check if any cat exceeds m after all assignments.
        
        bool feasible = true;
        {
            vector<long long> catPremium(n, 0);
            for (int i = 0; i < n; i++) {
                int bestCat = 0;
                for (int j = 1; j < n; j++) {
                    if (catPremium[j] > catPremium[bestCat]) bestCat = j;
                }
                catPremium[bestCat] += sorted_a[i];
                if (catPremium[bestCat] > m) { feasible = false; break; }
            }
        }
        
        cout << (feasible ? "Yes" : "No") << "\n";
    }
    return 0;
}
