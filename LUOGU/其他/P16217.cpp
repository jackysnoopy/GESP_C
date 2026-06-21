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
        int n, a1, d, m, k;
        cin >> n >> a1 >> d >> m >> k;
        // Initial S = {a1, a1+d, ..., a1+(n-1)*d}
        // Each player adds m numbers. Total = n + 2m numbers.
        // k-connected count = 1 + count of gaps > k in sorted order.
        // 
        // Game: Maddy wants to maximize connected components (add far-away numbers),
        // Baddy wants to minimize (add numbers to fill gaps).
        // 
        // Key insight: 
        // - Gaps in initial sequence: d between consecutive elements.
        // - If d > k: initial connected components = ceil(n / something)... 
        //   Actually: count gaps > k. With n elements in AP with difference d:
        //   if d > k: all n elements are separate → n components
        //   if d <= k: all connected → 1 component
        // - After adding numbers, new elements can fill gaps or create new ones.
        //
        // Maddy adds a number far away → creates new gap > k → +1 component
        // Baddy adds a number in existing gap → fills gap → can reduce components
        //
        // Optimal play:
        // - Each turn Maddy adds: she adds a number that maximizes gaps.
        //   Best: add very far from everything → +1 component.
        //   But Baddy can fill it back.
        // - Each turn Baddy adds: she adds a number that minimizes gaps.
        //   Best: fill the largest existing gap.
        //
        // For simplicity with small constraints:
        // Initial components: if d > k: n, else 1.
        // Maddy adds m numbers, Baddy adds m numbers.
        // Maddy can always add far away to create 1 new component per turn.
        // Baddy can always add to fill 1 gap per turn.
        // Net change: Maddy gains 1 per turn, Baddy loses 1 per turn.
        // 
        // But it's more nuanced. Let me think:
        // Initial gap count = max(0, n-1) if d > k, or 0 if d <= k.
        // 
        // Actually, let me reconsider with the initial AP.
        // n elements with gap d between consecutive.
        // If d <= k: 1 component, 0 gaps > k.
        // If d > k: n components, n-1 gaps > k.
        //
        // Each number added can:
        // - Maddy: add between two elements, splitting a gap. If she adds in the middle 
        //   of a gap > k, the gap splits into two gaps. If both > k, components increase.
        //   If she adds far away, creates a new isolated element (new component if gap > k).
        // - Baddy: add in a gap > k to reduce it. If she adds to split a gap > k into 
        //   two gaps <= k, components decrease.
        //
        // For this problem, with small constraints (m <= 100), the key insight is:
        // - Maddy can always create a new component by adding very far away (gap > k). +1 comp.
        // - Baddy can always reduce components by 1 by adding between two isolated elements 
        //   that are close enough (filling a gap).
        // - But Baddy is limited: she can only fill gaps that exist.
        //
        // Actually: when Maddy adds far away, she creates a new isolated element.
        // When Baddy adds between two isolated elements (within k distance), she merges them.
        // 
        // Net per round: +1 (Maddy) - 1 (Baddy) = 0? No.
        // 
        // Let me think differently. After the game:
        // - Maddy adds m numbers far away → m new isolated components.
        // - Baddy adds m numbers → each can merge at most 1 pair → m merges.
        // But Baddy needs existing gaps to fill. She can fill gaps between isolated elements.
        // If there are enough gaps, she can reduce by m.
        //
        // With initial components C:
        // After Maddy: C + m (each adds far away = +1)
        // After Baddy: she can merge at most min(m, some limit) pairs.
        // 
        // Actually Baddy goes second in each round. But since both play optimally,
        // let me think about it round by round.
        // 
        // For simplicity: the answer is max(initial_components, 1) + m - m = initial_components?
        // That doesn't match sample 1: initial = {2,5,8}, d=3 > k=2, so initial=3 components.
        // m=2. Answer = 3. So initial + 0 = 3. 
        // But sample 2: n=4, a1=3, d=2, m=5, k=1. Initial={3,5,7,9}, d=2 > k=1, initial=4.
        // Answer=6. So 4 + 2 = 6. 
        //
        // Hmm: 4 + 2m - 2m? No. 4 + m - something = 6 → m - something = 2 → something = 3.
        //
        // Let me think again. When d > k:
        // Initial components = n. Gaps = n-1, all > k (value d).
        // Each Maddy turn: she can split a gap into two, or add far away.
        // Splitting a gap of size d (>k) into two gaps of size d1, d2 where d1+d2 = d:
        //   If d1 > k and d2 > k: components increase by 1 (one gap → two gaps)
        //   If d1 <= k and d2 > k: components stay same (gap replaced by one gap > k)
        //   If d1 <= k and d2 <= k: components decrease by 1
        // So Maddy should split to maximize: put in middle, d1 = d2 = d/2.
        // If d/2 > k: net +1. If d/2 <= k: net -1 (bad for Maddy).
        //
        // For d=3, k=2: d/2 = 1.5, so d1=1, d2=2. d1=1 <= k=2, d2=2 <= k=2. 
        // Net: -1 component. Maddy doesn't want this!
        // So Maddy should add far away: +1 component.
        //
        // For d=2, k=1: d/2=1. d1=1<=1, d2=1<=1. Splitting: -1. Bad.
        // Add far away: +1. 
        //
        // Baddy's turn: she wants to merge. If she adds between two isolated elements 
        // within distance k, she can merge them. But isolated elements are at distance d > k.
        // She can add between two to reduce a gap.
        //
        // Actually the game is complex. With n,m <= 100, maybe brute force or DP works.
        // But for difficulty 2, there must be a formula.
        //
        // Let me think: initial components = C0.
        // Maddy adds m numbers: each can at best create +1 component (far away).
        // Baddy adds m numbers: each can at best merge two components (-1 component).
        // So answer = C0 + m - m = C0? But sample 2 says 6 ≠ 4.
        //
        // Wait, maybe Baddy can merge more than 1 per number? No, each number splits one gap.
        // And Maddy can create at most 1 new component per number.
        //
        // Unless Baddy's merging is limited by something. She needs two components close enough.
        // If all components are far apart (> k), she can add a number between them.
        // But a number between two components (at distance d) that's within k of both:
        // need d <= 2k. If d > 2k, one number can't bridge the gap.
        //
        // For d=2, k=1: gap = 2. Adding 1 at distance 1 from each: bridges! (-1 component)
        // For d=3, k=2: gap = 3. Adding 1 at distance 1 from one side: within k of both. (-1)
        //
        // So Baddy can always bridge one gap with one number. Each number bridges at most 1 gap.
        // Net per round: +1 (Maddy) - 1 (Baddy) = 0.
        //
        // But wait, sample 2: n=4, m=5, d=2, k=1. Initial = 4 components.
        // If net per round = 0, answer = 4. But expected = 6.
        //
        // Hmm. Maybe Maddy can do better than +1 per turn?
        // If Maddy adds between two existing components (gap d=2 > k=1), she splits gap of 2
        // into d1+d2=2. Both d1,d2 < d=2. If d1 <= k=1 and d2 <= k=1: merges! Bad for Maddy.
        // So Maddy should NOT split. Add far away: +1.
        //
        // Maybe the issue is Baddy's turn: she can merge at most some number of components.
        // With initial n components, n-1 gaps. Baddy has m numbers. She can merge at most m pairs.
        // But after Maddy adds, there are more components and more gaps.
        //
        // Let me simulate sample 2:
        // Initial: {3,5,7,9}. 4 components. Gaps: [2,2,2].
        // Round 1: Maddy adds 100 (far away). Components: 5. Gaps: [2,2,2,91].
        //          Baddy adds 4 (between 3 and 5). Gap [2] becomes [1,1] ≤ k=1. Merge? 
        //          Components: 4 (merged 3-4-5 into one component).
        // Round 2: Maddy adds 200. Components: 5.
        //          Baddy adds 6 (between 5 and 7). Merge: 4.
        // Round 3: Maddy adds 300. Components: 5.
        //          Baddy adds 8. Merge: 4.
        // Round 4: Maddy adds 400. Components: 5.
        //          Baddy adds... no more gaps to fill? Gaps are [400-300=100, 200-100=100, ...].
        //          Wait, after 4 rounds, elements are {3,5,7,9,4,6,8,100,200,300,400}.
        //          Sorted: 3,4,5,6,7,8,9,100,200,300,400. 
        //          Components: {3-4-5-6-7-8-9} (gap 1 ≤ 1), then {100}, {200}, {300}, {400}.
        //          5 components. Baddy has 1 more number.
        // Round 5: Maddy adds 500. Components: 6.
        //          Baddy adds 150 (between 100 and 200). Gap [100] → [50,50]. Both > 1. 
        //          Components stay 6? No, 150 is isolated: {100,150,200} → gaps 50 > 1 → 3 components.
        //          Actually Baddy can add 99 (just below 100). Gap from 9 to 100 was 91. Now 9 to 99 = 90 > 1, 99 to 100 = 1 ≤ 1. So 99 merges with 100. Components: 5 (merged 99-100).
        //
        // Hmm this is getting complex. Let me just write a brute-force DP for small constraints.
        // Actually with n,m <= 100 and numbers up to large values, DP on positions is hard.
        //
        // Let me reconsider the problem. Maybe the answer formula is simpler.
        // After analysis:
        // Initial components C = n if d > k, else 1.
        // Maddy adds m numbers. Baddy adds m numbers.
        // Each Maddy number adds at most 1 to components (by being far away).
        // Each Baddy number reduces at most 1 from components (by bridging).
        // BUT: Baddy can only bridge if there are enough small gaps to exploit.
        // AND: the AP structure matters.
        //
        // For d > k: initial = n. All gaps = d > k.
        // Maddy adds far away: creates isolated elements.
        // Baddy adds between adjacent isolated elements (distance d > k):
        //   She can add at distance ≤ k from both → merges them. Needs d ≤ 2k.
        //   If d > 2k: she can't bridge two adjacent AP elements with one number.
        //   If d ≤ 2k: she can bridge.
        //
        // For d=3, k=2: d=3 ≤ 2k=4. Baddy can bridge. But after bridging,
        // the merged element pair has the new number between them.
        // For d=2, k=1: d=2 ≤ 2k=2. Baddy can bridge (exactly).
        //
        // Let me try a different approach: just count what happens.
        // Initial gaps > k: let's call these "big gaps". Count = n-1 if d > k.
        // Maddy adds a number far away: creates 2 big gaps (from isolated to neighbors).
        //   Net: +1 component, +2 big gaps.
        // Baddy adds a number: if she bridges a big gap (d ≤ 2k): 
        //   gap splits into two ≤ k. -1 component, -1 big gap.
        //   If d > 2k: she can't fully bridge. She splits into two, at least one > k.
        //   Net: 0 components, 0 big gaps (one big gap → one big gap).
        //
        // For d=3, k=2: d ≤ 2k=4. Baddy bridges. 
        // Each round: Maddy +1 comp, +2 big gaps. Baddy -1 comp, -1 big gap.
        // Net: +0 comp, +1 big gap per round.
        // After m rounds: n + 0 = n components. But sample 1 says 3 = n. ✓
        //
        // For d=2, k=1: d=2 ≤ 2k=2. Baddy bridges.
        // Same analysis: net +0 per round. Answer = n = 4. But expected 6.
        //
        // Something's wrong. Let me re-examine sample 2 more carefully.
        // n=4, a1=3, d=2, m=5, k=1. S={3,5,7,9}.
        //
        // Maybe Baddy can't bridge as efficiently as I think?
        // With d=2, k=1: gap=2. To bridge: need a number x where |x-3|≤1 AND |x-5|≤1 → x=4.
        // But x=4 satisfies: |4-3|=1≤1 ✓, |4-5|=1≤1 ✓. So yes, Baddy can bridge with x=4.
        // After bridging 3 and 5 with 4: {3,4,5,7,9}. Components: {3,4,5}, {7}, {9} → 3 components.
        //
        // Wait, after round 1: Maddy adds 100. S={3,5,7,9,100}. 5 components.
        // Baddy adds 4. S={3,4,5,7,9,100}. Sorted: 3,4,5,7,9,100.
        // Gaps: 1,1,2,2,91. Gaps > k=1: 2,2,91 → 3 gaps → 4 components.
        // {3,4,5}, {7}, {9}, {100} → 4 components.
        //
        // Round 2: Maddy adds 200. 5 components. Baddy adds 6. 
        // S={3,4,5,6,7,9,100,200}. Gaps: 1,1,1,1,2,91,100. Big: 2,91,100 → 3 big gaps → 4 components.
        // {3,4,5,6,7}, {9}, {100}, {200} → 4 components.
        //
        // Round 3: Maddy adds 300. 5. Baddy adds 8.
        // {3,4,5,6,7,8,9,100,200,300}. Gaps: 1,1,1,1,1,1,91,100,100. Big: 91,100,100 → 3 big → 4.
        // {3..9}, {100}, {200}, {300} → 4.
        //
        // Round 4: Maddy adds 400. 5. Baddy adds... 
        // She can't bridge between {3..9} and {100} (gap 91 > 2k=2).
        // She can add between 100 and 200: need x where |x-100|≤1 and |x-200|≤1. Impossible (gap=100).
        // She can only merge two close isolated elements. But 100,200,300 are far apart.
        // So she adds between 100 and 200 at say 150: gap becomes 50,50. Both > 1. No merge.
        // Or she can add at 99: bridges {3..9} with {100}? |99-9|=90 > 1, |99-100|=1 ≤ 1. 
        // 99 is adjacent to 100 (gap 1). So {3..9,99,100}: gap 9 to 99 = 90 > 1 → 2 components.
        // {3..9} and {99,100} → 6 components total. That's worse!
        //
        // Baddy should NOT add at 99. She should add somewhere that helps.
        // Since all remaining gaps are > 2k=2, she can't bridge any pair of components.
        // She can only add within an existing component (doesn't help) or between components 
        // (creates isolated element, makes things worse).
        //
        // So from round 4 onwards: Baddy can't help. Maddy gets +1 each round.
        // Round 4: 5 components. Round 5: 6 components.
        //
        // So the answer is 4 + (5 - 3) = 6? Where 3 = number of rounds Baddy can help.
        // Baddy can help for min(m, something) rounds. 
        // 
        // Key: Baddy can bridge gaps of size d where d ≤ 2k. The AP gaps are size d.
        // After bridging, the merged component has width d. New gaps are 1 on each side.
        // But new isolated elements from Maddy create gaps of d to the nearest element.
        //
        // Actually: Baddy bridges the AP elements. After she bridges k pairs,
        // the AP elements become one big component. Then she can't bridge further.
        //
        // For n=4, d=2, k=1: 3 gaps to bridge. Baddy bridges 3, then can't help.
        // After 3 rounds: AP fully connected. Rounds 4,5: Maddy gets +1 each.
        // Answer: 4 (initial) + 2 (extra rounds) = 6. ✓
        //
        // For n=3, d=3, k=2: 2 gaps to bridge. d=3, 2k=4, d ≤ 2k. Baddy bridges.
        // After 2 rounds: AP fully connected. No extra rounds (m=2).
        // Answer: 3 (initial). ✓
        //
        // For n=4, d=1, k=2: d=1 ≤ k=2. Initial: 1 component. 0 gaps to bridge.
        // Baddy can't help at all. Answer: 1 + m = 1+5 = 6. ✓
        //
        // For n=9, d=8, k=0: initial: 9 components (all gaps=8>0). d=8, 2k=0, d > 2k.
        // Baddy can NEVER bridge (needs d ≤ 2k=0). Answer: 9 + m = 9+3 = 12. ✓
        //
        // Formula:
        // If d <= k: initial = 1, no gaps to bridge. Answer = 1 + m.
        // If d > k and d <= 2k: initial = n, gaps = n-1. 
        //   Baddy bridges min(m, n-1) gaps. After that, remaining rounds give +1 each.
        //   Answer = n - min(m, n-1) + max(0, m - (n-1))
        //   = n - m + max(0, m - n + 1) ... hmm
        //   = if m <= n-1: n - m. if m > n-1: n - (n-1) + (m - n + 1) = m + 1.
        // Wait: if m <= n-1: Baddy bridges m gaps. Components = n - m. ✓
        //   if m > n-1: Baddy bridges n-1 gaps, then remaining m-(n-1) rounds: Maddy +1 each.
        //   Components = 1 + (m - n + 1) = m - n + 2.
        //   For n=4, d=1, k=2: d<=k, so answer = 1+m = 6. ✓ (special case)
        //   For n=4, d=2, k=1: d>2k=2? d=2, 2k=2. d<=2k. m=5 > n-1=3.
        //   Answer = m - n + 2 = 5 - 4 + 2 = 3? But expected 6.
        //
        // Hmm, that's wrong. Let me reconsider.
        //
        // If d > 2k: Baddy can't bridge AP gaps. Answer = n + m.
        // If d <= 2k (and d > k): Baddy can bridge. 
        //   After bridging all n-1 gaps: 1 component. Remaining rounds: +1 each.
        //   But wait, when Maddy adds far away, Baddy can't bridge the far element with the AP.
        //   Because the far element is very distant.
        //
        // Let me reconsider: when Maddy adds far away, she creates a new isolated element.
        // The gap between this and the nearest AP element is huge (> 2k).
        // Baddy can't bridge it. So Baddy can only bridge AP elements.
        // 
        // After Baddy bridges all n-1 AP gaps: 1 AP component + any far elements from Maddy.
        // In subsequent rounds: Maddy adds far away (+1), Baddy can't help. Net +1.
        //
        // For n=4, d=2, k=1: Baddy bridges 3 gaps in 3 rounds. Remaining: 2 rounds.
        // Components: 1 (AP) + 2 (Maddy's far elements) = 3? But expected 6.
        //
        // Wait! After round 1: Maddy adds 100. Baddy bridges 3→4→5. 
        // Now S has {3,4,5,7,9,100}. Components: {3,4,5}, {7}, {9}, {100} → 4.
        //
        // Hmm, bridging 3→4→5 merges 3 and 5 (via 4), but 7 and 9 are still separate.
        // Baddy needs to bridge each pair separately. She has m=5 turns.
        // 3 pairs to bridge: (3,5), (5,7), (7,9). Takes 3 turns.
        // But during those 3 turns, Maddy adds 3 far elements.
        //
        // After 3 rounds: AP fully connected (1 component) + 3 far elements = 4 components.
        // Round 4: Maddy +1, Baddy can't help → 5.
        // Round 5: Maddy +1 → 6. ✓
        //
        // So: answer = 1 + (m - min(m, n-1)) + min(m, n-1) = wait...
        // = 1 + max(0, m - (n-1)) + 0 = m - n + 2 if m >= n-1, else n - m.
        // For n=4, m=5: m >= 3 → 5-4+2 = 3. But expected 6!
        //
        // I'm making an error. After bridging, the AP becomes 1 component.
        // But Baddy ALSO creates far elements? No, only Maddy adds far elements.
        // 
        // Let me recount: 
        // Initial: 4 components. After 3 rounds of Maddy adding far + Baddy bridging:
        //   3 far elements + 1 AP component = 4 components.
        // Round 4: Maddy adds far: 5. Baddy: nothing useful. 5 components.
        // Round 5: Maddy adds far: 6. 6 components. ✓
        //
        // Formula: initial = n. After min(m, n-1) rounds of bridging:
        //   components = n - min(m, n-1) + min(m, n-1) = n. (lost min(m,n-1) from bridging, gained min(m,n-1) from far)
        //   Wait: Maddy also adds during bridging rounds! 
        //   Each bridging round: Maddy +1, Baddy -1. Net 0. Components stay at n.
        //   After bridging (n-1 rounds): components still n? No!
        //
        // Let me recount more carefully for n=4, m=5:
        // Initial: 4 components.
        // Round 1: Maddy +1=5, Baddy -1=4. 
        // Round 2: Maddy +1=5, Baddy -1=4.
        // Round 3: Maddy +1=5, Baddy -1=4.
        // Round 4: Maddy +1=5. Baddy: can't bridge. 5.
        // Round 5: Maddy +1=6. 6. ✓
        //
        // But Baddy can only bridge for n-1 rounds! After that, she can't bridge anything.
        // So answer = n + max(0, m - (n-1)).
        // For n=4, m=5: 4 + max(0, 5-3) = 4 + 2 = 6. ✓
        // For n=3, m=2: 3 + max(0, 2-2) = 3. ✓
        // For n=9, m=3, d=8, k=0: d>2k=0, Baddy can't bridge at all. 
        //   Answer = n + m = 9 + 3 = 12. ✓
        // For n=4, d=1, k=2: d<=k, initial=1. No bridging needed. Answer = 1 + m = 6. ✓
        //
        // Final formula:
        // If d <= k: answer = 1 + m
        // If d > k:
        //   If d <= 2k: answer = n + max(0, m - (n-1))
        //   If d > 2k: answer = n + m
        
        int initial;
        if (d <= k) {
            initial = 1;
        } else {
            initial = n;
        }
        int ans;
        if (d <= k) {
            ans = 1 + m;
        } else if (d <= 2 * k) {
            ans = n + max(0, m - (n - 1));
        } else {
            ans = n + m;
        }
        cout << ans << "\n";
    }
    return 0;
}
