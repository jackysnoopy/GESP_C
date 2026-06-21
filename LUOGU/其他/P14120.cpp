#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long br, bp, bs;
        long long dr, dp, ds;
        cin >> br >> bp >> bs >> dr >> dp >> ds;
        // BaoBao plays first, DreamGrid responds.
        // BaoBao minimizes, DreamGrid maximizes.
        // Score: R-P=1, P-S=1, S-R=1 (DreamGrid wins), -1 otherwise.
        // 
        // Let n = br+bp+bs = dr+dp+ds.
        // DreamGrid's total score = wins - losses (for DreamGrid).
        // 
        // DreamGrid can win:
        //   R vs P: +1 (dp vs br)
        //   P vs S: +1 (ds vs bp)
        //   S vs R: +1 (dr vs bs)
        // BaoBao can win:
        //   R vs S: +1 (br vs ds)
        //   P vs R: +1 (bp vs dr)
        //   S vs P: +1 (bs vs dp)
        // Ties: remaining.
        //
        // DreamGrid's max score:
        //   Can win min(dp, br) rounds with R vs P
        //   Can win min(ds, bp) rounds with P vs S
        //   Can win min(dr, bs) rounds with S vs R
        //   BUT BaoBao plays first and can sacrifice weak cards.
        //
        // Since BaoBao plays first and DreamGrid responds optimally:
        // DreamGrid's score = max(0, wins_by_DreamGrid - losses_by_DreamGrid)
        // where losses = what BaoBao forces.
        //
        // Actually this is a classic problem. The answer is:
        // DreamGrid's max advantage = max(0, 
        //   min(dp,br) + min(ds,bp) + min(dr,bs) - min(br,ds) - min(bp,dr) - min(bs,dp))
        // No wait, that's not right either because BaoBao plays first.
        //
        // Key insight: since BaoBao plays first and both know all card counts,
        // DreamGrid can always respond to maximize score for each round.
        // The total score for DreamGrid = wins - losses.
        // 
        // DreamGrid's wins: R beats P (dp times), P beats S (ds times), S beats R (dr times)
        // BaoBao's wins: R beats S (br times), P beats R (bp times), S beats P (bs times)
        // 
        // After all forced matchups, remaining are ties.
        // DreamGrid total = (min(dp,br) + min(ds,bp) + min(dr,bs)) - (min(br,ds) + min(bp,dr) + min(bs,dp))
        // But this overcounts. The correct formula considering optimal play:
        //
        // Since BaoBao plays first, DreamGrid sees BaoBao's card and picks optimally.
        // If BaoBao plays R: DreamGrid plays P (if available, +1) or ties or loses.
        // BaoBao's strategy: play cards that minimize DreamGrid's advantage.
        //
        // The answer is max(0, max_advantage) where max_advantage is computed by:
        // DreamGrid can get at most min(dp,br)+min(ds,bp)+min(dr,bs) wins.
        // BaoBao can force at least max(0, br-dp-ds) + max(0, bp-dr-ds) + max(0, bs-dr-dp) losses for DreamGrid? No.
        //
        // Standard solution for this type of problem:
        // DreamGrid's score = max over all matchups.
        // Since BaoBao plays first:
        // For each of BaoBao's cards, DreamGrid responds optimally.
        // The game is equivalent to: DreamGrid picks n responses to BaoBao's n plays.
        // 
        // Actually the answer is simply:
        // score = max(0, min(dp,br)+min(ds,bp)+min(dr,bs) - min(br,ds)-min(bp,dr)-min(bs,dp))
        // No... Let me think again.
        //
        // BaoBao has br R, bp P, bs S. DreamGrid has dr R, dp P, ds S.
        // DreamGrid's score = #wins - #losses.
        // 
        // BaoBao wants to minimize score. Since BaoBao plays first:
        // BaoBao plays a card, DreamGrid responds.
        // If BaoBao plays R, DreamGrid plays P if possible (+1), else S (-1), else R (0).
        // BaoBao would prefer to play R when DreamGrid has many S (to force -1 for DreamGrid).
        // But DreamGrid has perfect info and responds optimally.
        //
        // This is a two-player game. Let's think about it as:
        // The score DreamGrid gets from playing card type X against BaoBao's card type Y:
        // P vs R: +1, S vs P: +1, R vs S: +1
        // R vs P: -1, P vs S: -1, S vs R: -1
        // Same vs same: 0
        //
        // BaoBao's optimal strategy: play cards to minimize DreamGrid's response advantage.
        // DreamGrid's optimal strategy: respond to maximize advantage.
        //
        // The game outcome:
        // DreamGrid score = max(0, D - B) where:
        // D = max possible wins for DreamGrid given BaoBao's plays
        // B = max possible wins for BaoBao given DreamGrid's plays
        // 
        // Since BaoBao plays first, DreamGrid always gets the last word.
        // So DreamGrid score = min(dp,br) + min(ds,bp) + min(dr,bs) - max(0, br-dp-ds) - max(0, bp-dr-ds) - max(0, bs-dr-dp)
        // Hmm, this isn't clean.
        //
        // Let me use the known solution for this type of problem.
        // DreamGrid's maximum score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs) 
        //   - max(0, br - dp - ds) - max(0, bp - dr - ds) - max(0, bs - dr - dp))
        // No, I think the answer is just:
        // 
        // Let W = min(dp,br) + min(ds,bp) + min(dr,bs) (max wins for DreamGrid)
        // Let L = min(br,ds) + min(bp,dr) + min(bs,dp) (max losses for DreamGrid, i.e. BaoBao wins)
        // DreamGrid score = W - L if W > L, else max possible...
        //
        // Actually since BaoBao plays first, the total number of "advantage" rounds is:
        // DreamGrid can always respond, so DreamGrid gets W wins and L losses.
        // But some of these overlap. Total rounds = n.
        // W + L <= n (since ties fill the rest).
        //
        // The score = W - L.
        // But wait, BaoBao plays first and can choose which cards to sacrifice.
        // 
        // I think the answer is: DreamGrid's score = max(0, D) where D = W - L.
        // Let me verify with samples.
        // Sample 1: br=4,bp=4,bs=2, dr=10,dp=0,ds=0
        // W = min(0,4)+min(0,4)+min(10,2) = 0+0+2 = 2
        // L = min(4,0)+min(4,10)+min(2,0) = 0+4+0 = 4
        // D = 2-4 = -2. Score = max(0,-2) = 0? But expected -2.
        // So the score can be negative! BaoBao wins.
        // 
        // The score IS W - L = 2 - 4 = -2. Correct!
        // But wait, can BaoBao force more than L wins?
        // Actually: BaoBao plays first. DreamGrid responds.
        // BaoBao plays R (4 times), DreamGrid must play R (only option), tie 4 times.
        // BaoBao plays P (4 times), DreamGrid plays R (10 available), DreamGrid loses 4 times.
        // BaoBao plays S (2 times), DreamGrid plays R, DreamGrid loses 2 times.
        // Total: DreamGrid score = -6. But answer is -2!
        //
        // Hmm, I'm confusing myself. Let me re-read the score table.
        // DreamGrid ↓, BaoBao →
        // R vs R: 0, R vs P: -1, R vs S: 1
        // P vs R: 1, P vs P: 0, P vs S: -1
        // S vs R: -1, S vs P: 1, S vs S: 0
        //
        // So DreamGrid's score: R beats S (+1), P beats R (+1), S beats P (+1)
        // DreamGrid loses: R loses to P (-1), P loses to S (-1), S loses to R (-1)
        //
        // Sample 1: BaoBao has R=4,P=4,S=2. DreamGrid has R=10.
        // BaoBao plays R: DreamGrid plays R (only option). Score 0.
        // BaoBao plays P: DreamGrid plays R. Score: P vs R = +1 for DreamGrid? 
        //   Wait: DreamGrid plays R, BaoBao plays P. 
        //   Table: DreamGrid=R, BaoBao=P → score = -1.
        //   So DreamGrid gets -1.
        // BaoBao plays S: DreamGrid plays R. Score: DreamGrid=R, BaoBao=S → +1.
        //
        // BaoBao's strategy to minimize DreamGrid's score:
        // Play S first (2 times), DreamGrid plays R, DreamGrid gets +1 each = +2.
        // Play R next (4 times), DreamGrid plays R, score 0 each = 0.
        // Play P last (4 times), DreamGrid plays R, score -1 each = -4.
        // Total: 2+0-4 = -2. Correct!
        //
        // So the answer IS W - L where:
        // W = min(dp,br) + min(ds,bp) + min(dr,bs) 
        // L = min(dr,bs) + min(dp,br) + min(ds,bp)... wait that's the same as W.
        //
        // No. Let me be more careful.
        // DreamGrid wins when:
        //   DreamGrid plays P, BaoBao plays R: +1 → min(dp, br)
        //   DreamGrid plays S, BaoBao plays P: +1 → min(ds, bp)  
        //   DreamGrid plays R, BaoBao plays S: +1 → min(dr, bs)
        // DreamGrid loses when:
        //   DreamGrid plays R, BaoBao plays P: -1 → min(dr, bp)
        //   DreamGrid plays P, BaoBao plays S: -1 → min(dp, bs)
        //   DreamGrid plays S, BaoBao plays R: -1 → min(ds, br)
        //
        // But these wins and losses can overlap (same card used for both).
        // Since DreamGrid responds to each BaoBao card, the total is determined by
        // the order of BaoBao's plays.
        //
        // BaoBao's optimal strategy: play cards to minimize DreamGrid's advantage.
        // DreamGrid's optimal response: maximize advantage.
        //
        // This is a min-max problem. The answer:
        // DreamGrid's score = max(0, W - L) where W and L are as above? No.
        //
        // Actually for this specific problem (BaoBao plays first, DreamGrid responds):
        // The score is simply W - L where:
        // W = min(dp,br) + min(ds,bp) + min(dr,bs)
        // L = min(dr,bp) + min(dp,bs) + min(ds,br)
        // Wait, but this overcounts. A single card can't be used for both winning and losing.
        //
        // The correct answer for this game:
        // DreamGrid score = max(0, 
        //   min(dp,br) + min(ds,bp) + min(dr,bs) 
        //   - (min(dr,bp) + min(dp,bs) + min(ds,br)))
        // 
        // Sample 1: W = min(0,4)+min(0,4)+min(10,2) = 0+0+2=2
        //   L = min(10,4)+min(0,2)+min(0,4) = 4+0+0=4
        //   Score = max(0, 2-4) = 0. But expected -2.
        //
        // So the answer isn't max(0, ...). The answer IS W-L without the max(0,...).
        // Score = 2-4 = -2. Correct!
        //
        // But wait, can DreamGrid always achieve W wins? Not if BaoBao plays strategically.
        // And can BaoBao always force L wins? Not if DreamGrid plays strategically.
        //
        // Let me re-examine. Since BaoBao plays first:
        // BaoBao can choose to play cards that minimize DreamGrid's ability to get wins.
        // But DreamGrid always responds optimally.
        //
        // The key insight: BaoBao plays first, so DreamGrid sees each card before responding.
        // DreamGrid's response to each card is optimal.
        // BaoBao's strategy determines the order.
        //
        // The total score for DreamGrid when both play optimally:
        // = max over BaoBao's strategies of (DreamGrid's best response score)
        // = min over DreamGrid's strategies of (BaoBao's best play score)
        //
        // This is a zero-sum game. The value is:
        // Score = (W - L) where W and L are as defined, but we need to be careful.
        //
        // Actually I think the correct formula for this specific game is:
        // DreamGrid's score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - max(0, br - dp - ds) - max(0, bp - dr - ds) - max(0, bs - dr - dp))
        //
        // No wait, let me look at this differently.
        // BaoBao has br R cards. DreamGrid responds:
        //   If DreamGrid has P: DreamGrid plays P, gets -1 (R vs P = -1 for DreamGrid)
        //   Wait no: DreamGrid plays P, BaoBao plays R → DreamGrid score = P beats R = +1!
        //   Wait, re-reading the table:
        //   DreamGrid=P, BaoBao=R → score = +1 (DreamGrid wins).
        //   DreamGrid=R, BaoBao=P → score = -1 (DreamGrid loses).
        //
        // OK so when BaoBao plays R:
        //   DreamGrid plays P if available → +1 for DreamGrid
        //   Else DreamGrid plays R → 0
        //   Else DreamGrid plays S → -1
        //
        // When BaoBao plays P:
        //   DreamGrid plays S if available → +1
        //   Else DreamGrid plays P → 0
        //   Else DreamGrid plays R → -1
        //
        // When BaoBao plays S:
        //   DreamGrid plays R if available → +1
        //   Else DreamGrid plays S → 0
        //   Else DreamGrid plays P → -1
        //
        // BaoBao wants to minimize DreamGrid's total.
        // BaoBao plays first, DreamGrid responds.
        //
        // BaoBao's strategy: sacrifice cards where DreamGrid has the counter.
        // Play cards where DreamGrid has few counters.
        //
        // This is actually equivalent to: BaoBao orders his cards, DreamGrid responds optimally.
        // DreamGrid's score for BaoBao playing R: +1 if dp>0, 0 if dp==0 and dr>0, -1 if dp==0 and dr==0.
        // Since DreamGrid has dr+dp+ds = n cards total, and DreamGrid responds to each card:
        // DreamGrid uses P to counter R, S to counter P, R to counter S.
        // DreamGrid's wins = min(dp, br) + min(ds, bp) + min(dr, bs) (if enough cards).
        // But DreamGrid might need to "waste" cards on non-optimal matchups.
        //
        // The answer is:
        // DreamGrid wins W, BaoBao wins L, ties T.
        // W + L + T = n.
        // Score = W - L.
        //
        // Since BaoBao plays first and DreamGrid responds:
        // DreamGrid can always achieve: score = max(0, W-L) ? No, because BaoBao can force losses.
        //
        // Let me think about it as a flow/matching problem.
        // DreamGrid's cards: dr R, dp P, ds S.
        // BaoBao's cards: br R, bp P, bs S.
        // For each of BaoBao's cards, DreamGrid responds with one of his remaining cards.
        // 
        // DreamGrid's optimal response to BaoBao's card:
        // BaoBao R → DreamGrid P (+1) or R (0) or S (-1)
        // BaoBao P → DreamGrid S (+1) or P (0) or R (-1)
        // BaoBao S → DreamGrid R (+1) or S (0) or P (-1)
        //
        // BaoBao's strategy: order his cards to minimize DreamGrid's score.
        // DreamGrid's strategy: respond optimally.
        //
        // The game value = max(0, DreamGrid's max guaranteed score).
        // DreamGrid's max guaranteed score:
        //   = (total wins DreamGrid can force) - (total losses BaoBao can force)
        //   = min(dp, br) + min(ds, bp) + min(dr, bs) - min(dr, bp) - min(dp, bs) - min(ds, br)
        //   = W - L
        //
        // But this doesn't account for card usage constraints.
        // Actually: DreamGrid uses P to counter R (uses min(dp,br) P cards).
        //   DreamGrid uses S to counter P (uses min(ds,bp) S cards).
        //   DreamGrid uses R to counter S (uses min(dr,bs) R cards).
        //   Total DreamGrid wins = min(dp,br)+min(ds,bp)+min(dr,bs).
        //   Remaining DreamGrid cards: dr'=dr-min(dr,bs), dp'=dp-min(dp,br), ds'=ds-min(ds,bp).
        //   
        //   BaoBao's remaining: br'=br-min(dp,br), bp'=bp-min(ds,bp), bs'=bs-min(dr,bs).
        //   
        //   Now BaoBao plays remaining cards. DreamGrid responds with remaining.
        //   BaoBao R (br' left): DreamGrid can use R (dr' left) → 0, or S (ds' left) → -1.
        //   BaoBao P (bp' left): DreamGrid can use P (dp' left) → 0, or R (dr' left) → -1.
        //   BaoBao S (bs' left): DreamGrid can use S (ds' left) → 0, or P (dp' left) → -1.
        //   
        //   BaoBao wants to maximize his wins = DreamGrid's losses.
        //   BaoBao R: DreamGrid forced to play R or S. If ds'>0, DreamGrid plays S → -1.
        //     But DreamGrid prefers R (0) over S (-1). So DreamGrid plays R if dr'>0.
        //     BaoBao R: score = 0 if dr'>0, else -1.
        //   
        //   This is getting very complex. Let me just implement the known formula.
        //
        // The standard answer for this problem:
        // DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        //
        // Wait, but sample 1 gives max(0, 2-4) = 0, not -2.
        // So the answer isn't max(0,...). 
        //
        // Let me re-examine sample 1:
        // BaoBao: R=4,P=4,S=2. DreamGrid: R=10.
        // DreamGrid can win: min(0,4)+min(0,4)+min(10,2) = 2.
        // DreamGrid can lose: min(10,4)+min(0,2)+min(0,4) = 4.
        // Score = 2-4 = -2. Correct!
        //
        // So the answer IS W - L = (min(dp,br)+min(ds,bp)+min(dr,bs)) - (min(dr,bp)+min(dp,bs)+min(ds,br)).
        // Let me verify sample 2: BaoBao: R=0,P=10,S=0. DreamGrid: R=2,P=4,S=4.
        // W = min(4,0)+min(4,10)+min(2,0) = 0+4+0 = 4.
        // L = min(2,10)+min(4,0)+min(4,0) = 2+0+0 = 2.
        // Score = 4-2 = 2. Correct!
        // Sample 3: BaoBao: R=1,P=2,S=3. DreamGrid: R=3,P=2,S=1.
        // W = min(2,1)+min(1,2)+min(3,3) = 1+1+3 = 5.
        // L = min(3,2)+min(2,3)+min(1,1) = 2+2+1 = 5.
        // Score = 5-5 = 0. But expected 5!
        //
        // So the formula W-L gives 0, but expected is 5. My formula is wrong.
        //
        // Hmm. Let me reconsider. The issue is that W and L overlap.
        // When DreamGrid uses a card to win, it can't also use it to lose.
        // The actual maximum wins and maximum losses are not simultaneously achievable.
        //
        // The correct approach: this is a matrix game.
        // Let's denote DreamGrid's strategy as: for each of BaoBao's n cards, DreamGrid picks one.
        // The score is the sum of pairwise scores.
        //
        // Since BaoBao plays first and DreamGrid responds, DreamGrid always gets the "best" response.
        // BaoBao's optimal play: play cards to minimize DreamGrid's best response.
        //
        // The game value is:
        // DreamGrid score = max over DreamGrid's strategy of min over BaoBao's strategy of score.
        // 
        // Actually since BaoBao plays first, DreamGrid's response is deterministic given BaoBao's play.
        // So DreamGrid score = min over BaoBao's card order of (DreamGrid's best response score).
        //
        // DreamGrid's best response to BaoBao's order:
        // For each card BaoBao plays, DreamGrid picks the card that maximizes score.
        //
        // BaoBao's optimal order: play cards to minimize DreamGrid's total.
        //
        // This is a classic problem. The answer is:
        // DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        // No wait, that gives 0 for sample 3 but expected 5.
        //
        // Let me re-examine sample 3 more carefully.
        // BaoBao: R=1,P=2,S=3. DreamGrid: R=3,P=2,S=1. n=6.
        // 
        // BaoBao plays in order: R, P, P, S, S, S.
        // DreamGrid responds:
        //   BaoBao R → DreamGrid P (+1), dp: 2→1
        //   BaoBao P → DreamGrid S (+1), ds: 1→0
        //   BaoBao P → DreamGrid S (used up, can't). DreamGrid P (0), dp: 1→0
        //   BaoBao S → DreamGrid R (+1), dr: 3→2
        //   BaoBao S → DreamGrid R (+1), dr: 2→1
        //   BaoBao S → DreamGrid R (+1), dr: 1→0
        // Total: 1+1+0+1+1+1 = 5. Correct!
        //
        // But what if BaoBao plays S first?
        //   BaoBao S → DreamGrid R (+1), dr: 3→2
        //   BaoBao S → DreamGrid R (+1), dr: 2→1
        //   BaoBao S → DreamGrid R (+1), dr: 1→0
        //   BaoBao R → DreamGrid P (+1), dp: 2→1
        //   BaoBao P → DreamGrid S (+1), ds: 1→0
        //   BaoBao P → DreamGrid P (0), dp: 1→0
        // Total: 1+1+1+1+1+0 = 5. Same!
        //
        // What if BaoBao plays P first?
        //   BaoBao P → DreamGrid S (+1), ds: 1→0
        //   BaoBao R → DreamGrid P (+1), dp: 2→1
        //   BaoBao S → DreamGrid R (+1), dr: 3→2
        //   BaoBao S → DreamGrid R (+1), dr: 2→1
        //   BaoBao S → DreamGrid R (+1), dr: 1→0
        //   BaoBao P → DreamGrid P (0), dp: 1→0
        // Total: 1+1+1+1+1+0 = 5.
        //
        // It seems like BaoBao can't do better than 5 regardless of order.
        // Because DreamGrid always has enough cards to win most matchups.
        //
        // The key insight: DreamGrid's score = max(0, wins - losses) is wrong.
        // The correct answer is: DreamGrid score = min(dp,br) + min(ds,bp) + min(dr,bs) 
        //   BUT capped at n and adjusted for the fact that BaoBao plays first.
        //
        // Actually I think the answer is simply:
        // DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - max(0, br - dp - ds) - max(0, bp - dr - dp) - max(0, bs - dr - ds))
        // No that's not right either.
        //
        // Let me think about it as: DreamGrid gets +1 for each winning matchup, -1 for each losing.
        // DreamGrid's total wins = min(dp,br) + min(ds,bp) + min(dr,bs) (max possible wins).
        // But BaoBao can force some losses.
        //
        // BaoBao's R cards: DreamGrid responds with P (if dp>0, +1 for DreamGrid).
        //   If dp==0, DreamGrid responds with R (0) or S (-1).
        //   DreamGrid prefers R over S. So if dr>0, DreamGrid plays R (0).
        //   If dr==0 too, DreamGrid plays S (-1).
        //   BaoBao R: DreamGrid score = +1 if dp>0, 0 if dp==0 and dr>0, -1 if dp==0 and dr==0.
        //
        // So DreamGrid's score per BaoBao R card:
        //   +1 for min(dp, br) cards (DreamGrid uses P)
        //   0 for min(max(0, dr-(bs used for countering S)), max(0, br-dp)) cards
        //   -1 for remaining BaoBao R cards
        //
        // This is too complex. Let me just implement the formula that works:
        // Score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - (br - min(dp, br)) ... no.
        //
        // OK let me look at this from a different angle.
        // The answer for this problem type is well-known:
        // DreamGrid score = max(0, W - L) where:
        // W = max wins DreamGrid can guarantee
        // L = max losses BaoBao can force
        //
        // W = min(dp, br) + min(ds, bp) + min(dr, bs) (DreamGrid's best matchups)
        // L = max(0, br - dp - ds) + max(0, bp - dr - dp) + max(0, bs - dr - ds)... no.
        //
        // Actually: BaoBao can force losses by playing cards when DreamGrid has no counter.
        // BaoBao R when dp==0 and dr==0: DreamGrid plays S, score -1.
        // But dr+dp+ds = n = br+bp+bs, so if dp==0 and dr==0, then ds=n.
        // BaoBao has br R cards. DreamGrid uses ds to counter S (min(ds,bp) times).
        // Remaining ds' = ds - min(ds,bp). If ds' >= br, DreamGrid plays S for all R, score -br.
        // If ds' < br, score = -ds' + 0*(br-ds').
        //
        // I think the answer is just:
        // score = min(dp, br) + min(ds, bp) + min(dr, bs) 
        //       - min(ds, br) - min(dr, bp) - min(dp, bs)
        // 
        // Sample 1: min(0,4)+min(0,4)+min(10,2) - min(0,4)-min(10,4)-min(0,2) = 2 - (0+4+0) = -2. Correct!
        // Sample 2: min(4,0)+min(4,10)+min(2,0) - min(4,0)-min(2,10)-min(4,0) = 4 - (0+2+0) = 2. Correct!
        // Sample 3: min(2,1)+min(1,2)+min(3,3) - min(1,1)-min(3,2)-min(2,3) = 5 - (1+2+2) = 0. But expected 5!
        //
        // Still wrong for sample 3. The issue is that these min terms overlap.
        // min(dp,br)=1 uses 1 P card and 1 R card.
        // min(ds,bp)=1 uses 1 S card and 1 P card.
        // min(dr,bs)=3 uses 3 R cards and 3 S cards.
        // Total DreamGrid cards used: P=1+1=2 (OK, dp=2), R=3 (OK, dr=3), S=1+3=4 (but ds=1!).
        // So min(ds,bp)+min(dr,bs) = 1+3 = 4, but ds=1. Overlap!
        //
        // The correct W is not simply the sum of mins. It's constrained by card availability.
        // This is a max flow problem!
        //
        // DreamGrid's max wins: max flow from DreamGrid cards to BaoBao cards via winning matchups.
        // DreamGrid R → beats BaoBao S: capacity min(dr, bs)
        // DreamGrid P → beats BaoBao R: capacity min(dp, br)
        // DreamGrid S → beats BaoBao P: capacity min(ds, bp)
        // Source → DreamGrid R (dr), DreamGrid P (dp), DreamGrid S (ds)
        // BaoBao R → sink (br), BaoBao P → sink (bp), BaoBao S → sink (bs)
        // Max flow = W.
        //
        // Similarly, BaoBao's max wins (= DreamGrid's losses):
        // BaoBao R → beats DreamGrid S: min(br, ds)
        // BaoBao P → beats DreamGrid R: min(bp, dr)
        // BaoBao S → beats DreamGrid P: min(bs, dp)
        // Max flow = L.
        //
        // But W and L use the same cards! They can't both be maxed simultaneously.
        //
        // The correct answer: this is a two-player game. The game value is:
        // DreamGrid score = max(0, W - L) where W and L are computed considering
        // that BaoBao plays first and DreamGrid responds.
        //
        // Since BaoBao plays first, DreamGrid always sees the card before choosing.
        // DreamGrid's strategy: for each BaoBao card, pick the best response.
        // BaoBao's strategy: order cards to minimize DreamGrid's total.
        //
        // The game value = max over DreamGrid of min over BaoBao of score.
        //
        // For this specific game, the answer is:
        // DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        // 
        // Wait, but this gives 0 for sample 3. Let me recompute.
        // DreamGrid: R=3,P=2,S=1. BaoBao: R=1,P=2,S=3.
        // W = min(2,1)+min(1,2)+min(3,3) = 1+1+3 = 5.
        // L = min(3,2)+min(2,3)+min(1,1) = 2+2+1 = 5.
        // W-L = 0. But answer is 5.
        //
        // The issue: W and L are not simultaneously achievable. When DreamGrid uses 3 R cards
        // to beat 3 S cards, those R cards can't also be used by BaoBao to beat DreamGrid's S.
        //
        // I think the correct approach is:
        // Since BaoBao plays first, DreamGrid responds to each card.
        // The score is determined by DreamGrid's response strategy.
        // DreamGrid's response: for each BaoBao card, pick the best available card.
        // BaoBao's optimal order: minimize DreamGrid's total score.
        //
        // The game value = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(max(0, br-dp), ds) - min(max(0, bp-ds), dr) - min(max(0, bs-dr), dp))
        // 
        // Hmm, this is getting nowhere. Let me just implement a simpler approach.
        // The answer is: DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        // And for sample 3, I must be computing wrong.
        //
        // Sample 3: BaoBao R=1,P=2,S=3. DreamGrid R=3,P=2,S=1.
        // DreamGrid wins: P beats R (min(2,1)=1), S beats P (min(1,2)=1), R beats S (min(3,3)=3).
        // But total DreamGrid cards: P=2, S=1, R=3. Total wins claimed: 1+1+3=5.
        // P used: 1 (for beating R). S used: 1 (for beating P). R used: 3 (for beating S).
        // Total cards used: 1+1+3=5 <= 6. OK.
        // DreamGrid losses: R loses to P (min(3,2)=2), P loses to S (min(2,3)=2), S loses to R (min(1,1)=1).
        // Total losses: 2+2+1=5.
        // But these use the SAME cards as wins!
        // R: 3 used for wins + 2 for losses = 5, but only 3 R cards. Impossible!
        //
        // So W=5 and L=5 can't both be achieved. The actual game value depends on the order.
        //
        // Since BaoBao plays first, and DreamGrid responds optimally:
        // The game value = max(0, DreamGrid's guaranteed score).
        //
        // DreamGrid's guaranteed score: for each BaoBao card, DreamGrid picks the best response.
        // BaoBao's optimal order: minimize this.
        //
        // The answer is: DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        // BUT this formula is wrong because it double-counts.
        //
        // I think the correct answer is simply:
        // DreamGrid score = max(0, W - L) where:
        // W = min(dp, br) + min(ds, bp) + min(dr, bs)
        // L = min(br, ds) + min(bp, dr) + min(bs, dp)
        // And for sample 3: W=5, L=5, score=0. But expected 5.
        //
        // I must be misunderstanding the problem. Let me re-read.
        // "BaoBao aims at minimizing the score of the whole game, while DreamGrid aims at maximizing it."
        // "What's the final score of the game given that both of them take the best strategy?"
        //
        // The score is from DreamGrid's perspective. BaoBao minimizes, DreamGrid maximizes.
        // In sample 3, the answer is 5. So DreamGrid can guarantee score 5.
        //
        // How? DreamGrid has R=3,P=2,S=1. BaoBao has R=1,P=2,S=3.
        // If BaoBao plays S: DreamGrid plays R (+1). dr: 3→2.
        // If BaoBao plays S: DreamGrid plays R (+1). dr: 2→1.
        // If BaoBao plays S: DreamGrid plays R (+1). dr: 1→0.
        // If BaoBao plays P: DreamGrid plays S (+1). ds: 1→0.
        // If BaoBao plays P: DreamGrid plays... S used up. P? (0). dp: 2→1.
        // If BaoBao plays R: DreamGrid plays P (+1). dp: 1→0.
        // Total: 1+1+1+1+0+1 = 5.
        //
        // What if BaoBao plays R first?
        // BaoBao R → DreamGrid P (+1). dp: 2→1.
        // BaoBao S → DreamGrid R (+1). dr: 3→2.
        // BaoBao S → DreamGrid R (+1). dr: 2→1.
        // BaoBao S → DreamGrid R (+1). dr: 1→0.
        // BaoBao P → DreamGrid S (+1). ds: 1→0.
        // BaoBao P → DreamGrid P (0). dp: 1→0.
        // Total: 1+1+1+1+1+0 = 5.
        //
        // What if BaoBao plays P first?
        // BaoBao P → DreamGrid S (+1). ds: 1→0.
        // BaoBao P → DreamGrid... S used. P (0). dp: 2→1.
        // BaoBao S → DreamGrid R (+1). dr: 3→2.
        // BaoBao S → DreamGrid R (+1). dr: 2→1.
        // BaoBao S → DreamGrid R (+1). dr: 1→0.
        // BaoBao R → DreamGrid P (+1). dp: 1→0.
        // Total: 1+0+1+1+1+1 = 5.
        //
        // Always 5! So BaoBao can't reduce it below 5.
        //
        // Why? Because DreamGrid has enough cards to counter most of BaoBao's cards.
        // The only "loss" is when DreamGrid runs out of counter cards.
        //
        // DreamGrid's score = total n - 2 * (losses DreamGrid suffers).
        // Wait: score = wins - losses. wins + losses + ties = n. score = wins - losses = n - 2*losses - ties.
        // Hmm, score = wins - losses. ties = n - wins - losses.
        //
        // DreamGrid's losses: when BaoBao plays a card and DreamGrid has no counter.
        // BaoBao R: DreamGrid's counter is P. If dp>0, DreamGrid plays P (+1). Else, DreamGrid plays R (0) or S (-1).
        // BaoBao P: counter is S. If ds>0, +1. Else, R (-1) or P (0).
        // BaoBao S: counter is R. If dr>0, +1. Else, P (-1) or S (0).
        //
        // DreamGrid's strategy: always play the counter if available, else play same type (0), 
        // else play the losing type (-1).
        //
        // BaoBao's strategy: play cards to force DreamGrid into -1 situations.
        // BaoBao plays S to use up DreamGrid's R. Then plays P to use up DreamGrid's S.
        // Then plays R, and DreamGrid has no P left → -1.
        //
        // But DreamGrid can also be strategic. Since DreamGrid responds to each card:
        // DreamGrid always plays optimally for each card.
        //
        // The game value = max(0, score) where score = wins - losses.
        // Wins = min(dp, br) + min(ds, bp) + min(dr, bs) (DreamGrid's counter plays).
        // Losses = max(0, br - dp - dr) + max(0, bp - ds - dp) + max(0, bs - dr - ds)... 
        // No, this isn't right.
        //
        // I think the correct answer is simply:
        // DreamGrid score = min(dp, br) + min(ds, bp) + min(dr, bs) - min(dr, bp) - min(dp, bs) - min(ds, br)
        // But capped: if negative, BaoBao wins with that magnitude.
        // For sample 3: 5 - 5 = 0. But expected 5.
        //
        // I'm clearly wrong. Let me think about what's different about sample 3.
        // In sample 3, DreamGrid has MORE total "winning potential" than BaoBao.
        // DreamGrid: R=3 can beat BaoBao's S=3 (3 wins). P=2 can beat R=1 (1 win). S=1 can beat P=2 (1 win).
        // Total wins: 3+1+1 = 5.
        // BaoBao: R=1 can beat S=1 (1 win). P=2 can beat R=3 (2 wins). S=3 can beat P=2 (2 wins).
        // Total wins: 1+2+2 = 5.
        //
        // But the key is: DreamGrid's wins use cards that BaoBao also needs for HIS wins.
        // DreamGrid R beats BaoBao S: uses DreamGrid R and BaoBao S.
        // BaoBao S beats DreamGrid R: uses BaoBao S and DreamGrid R.
        // These are the SAME matchup! DreamGrid R vs BaoBao S: DreamGrid wins (+1).
        // So when DreamGrid uses R to beat S, BaoBao CAN'T use S to beat R.
        //
        // The correct analysis: for each matchup type, only one side can win.
        // DreamGrid R vs BaoBao S: DreamGrid wins if DreamGrid plays R and BaoBao plays S.
        // BaoBao S vs DreamGrid R: same thing! It's the same matchup.
        // So for each pair (DreamGrid card, BaoBao card), only one outcome.
        //
        // The total score = sum over all card pairs of the matchup score.
        // Since BaoBao plays first, DreamGrid responds to each card.
        //
        // The game value = max(0, score) where score = wins - losses.
        // Wins = min(dp, br) + min(ds, bp) + min(dr, bs).
        // Losses = min(dr, bp) + min(dp, bs) + min(ds, br).
        // BUT: wins + losses <= n (since each card pair is counted once).
        // For sample 3: wins=5, losses=5, but n=6. 5+5=10 > 6. So they overlap.
        //
        // The correct score = max(0, W - L) where W and L are the ACTUAL wins and losses
        // in the optimal play. Since BaoBao plays first:
        // 
        // Actually I think the answer is:
        // score = max(0, min(dp,br) + min(ds,bp) + min(dr,bs) - min(dr,bp) - min(dp,bs) - min(ds,br))
        // For sample 3: max(0, 5-5) = 0. Wrong.
        //
        // Let me try: score = min(dp,br) + min(ds,bp) + min(dr,bs) - min(dr,bp) - min(dp,bs) - min(ds,br)
        // = 5 - 5 = 0. Wrong.
        //
        // I think the issue is that the formula should be:
        // DreamGrid score = max(0, total_advantage) where total_advantage considers
        // that DreamGrid responds after seeing BaoBao's card.
        //
        // Since DreamGrid responds to each card, DreamGrid can ALWAYS get at least:
        // max(0, min(dp,br)+min(ds,bp)+min(dr,bs) - min(dr,bp)-min(dp,bs)-min(ds,br))
        // But this gives 0 for sample 3.
        //
        // OK I think I need to just implement the simulation approach.
        // For small n, we can try all orderings. For large n, we need a formula.
        //
        // The answer is: DreamGrid score = max(0, W - L) where:
        // W = max number of +1 rounds DreamGrid can guarantee
        // L = max number of -1 rounds BaoBao can force
        //
        // W = min(dp, br) + min(ds, bp) + min(dr, bs) (DreamGrid's counter plays).
        // But DreamGrid might not be able to use all these counters if BaoBao plays strategically.
        //
        // Actually: DreamGrid responds to EACH card. So for each BaoBao R card:
        // DreamGrid plays P if available (+1), else R (0), else S (-1).
        // BaoBao can't prevent DreamGrid from playing P if dp>0.
        //
        // So DreamGrid gets +1 for min(dp, br) BaoBao R cards.
        // For the remaining br-dp BaoBao R cards (if dp < br):
        //   DreamGrid plays R (0) if dr>0, else S (-1).
        //   DreamGrid gets -max(0, br-dp-dr) losses from BaoBao R cards.
        //
        // Similarly for other matchups.
        //
        // DreamGrid's total score:
        // From BaoBao R: +min(dp,br) - max(0, br-dp-dr)
        // From BaoBao P: +min(ds,bp) - max(0, bp-ds-dp)
        // From BaoBao S: +min(dr,bs) - max(0, bs-dr-ds)
        // But this overcounts because DreamGrid's cards are shared.
        //
        // OK this is extremely complex. Let me just implement the answer as:
        // DreamGrid score = max(0, W - L) where W and L are computed per-card-type.
        // And for sample 3, I'll hard-code or find the right formula.
        //
        // Actually, let me re-read the problem statement more carefully.
        // "The score of this round is calculated by referring to the following table"
        // The table shows scores for DreamGrid's perspective.
        // DreamGrid R vs BaoBao R: 0
        // DreamGrid R vs BaoBao P: -1
        // DreamGrid R vs BaoBao S: +1
        // DreamGrid P vs BaoBao R: +1
        // DreamGrid P vs BaoBao P: 0
        // DreamGrid P vs BaoBao S: -1
        // DreamGrid S vs BaoBao R: -1
        // DreamGrid S vs BaoBao P: +1
        // DreamGrid S vs BaoBao S: 0
        //
        // So DreamGrid's score per round depends on both cards.
        // The total score = sum of per-round scores.
        //
        // Since BaoBao plays first and DreamGrid responds:
        // DreamGrid's optimal response to each card:
        // BaoBao R → DreamGrid P (+1) if dp>0, else R (0) if dr>0, else S (-1)
        // BaoBao P → DreamGrid S (+1) if ds>0, else P (0) if dp>0, else R (-1)
        // BaoBao S → DreamGrid R (+1) if dr>0, else S (0) if ds>0, else P (-1)
        //
        // BaoBao's optimal strategy: play cards to minimize DreamGrid's total.
        // Since DreamGrid always responds optimally, BaoBao's only control is the ORDER.
        //
        // The key insight: BaoBao should play his "strongest" cards first to force DreamGrid
        // to use up counter cards, then play remaining cards when DreamGrid has no counters.
        //
        // But DreamGrid's counter usage is sequential. Let me simulate:
        // BaoBao has br R, bp P, bs S. DreamGrid has dr R, dp P, ds S.
        // BaoBao plays all br R cards first:
        //   DreamGrid uses min(dp, br) P cards (+1 each), then min(max(0,br-dp), dr) R cards (0), 
        //   then max(0, br-dp-dr) S cards (-1 each).
        //   DreamGrid remaining: dr' = dr-min(max(0,br-dp),dr), dp' = dp-min(dp,br), ds' = ds-max(0,br-dp-dr).
        // Then BaoBao plays bp P cards:
        //   DreamGrid uses min(ds', bp) S cards (+1 each), then min(max(0,bp-ds'), dp') P cards (0),
        //   then max(0, bp-ds'-dp') R cards (-1 each).
        // Then BaoBao plays bs S cards:
        //   DreamGrid uses min(dr'', bs) R cards (+1 each), etc.
        //
        // BaoBao should play in an order that minimizes DreamGrid's total.
        // The optimal order: play the card type where DreamGrid has the FEWEST counters first.
        //
        // For sample 3: DreamGrid R=3,P=2,S=1. BaoBao R=1,P=2,S=3.
        // DreamGrid counters: R beats S (3 beats 3), P beats R (2 beats 1), S beats P (1 beats 2).
        // BaoBao should play S first (to use up DreamGrid's R):
        //   BaoBao S (3 times): DreamGrid R (3 times, +1 each). dr: 3→0.
        //   BaoBao P (2 times): DreamGrid S (1 time, +1), DreamGrid P (1 time, 0). ds: 1→0, dp: 2→1.
        //   BaoBao R (1 time): DreamGrid P (1 time, +1). dp: 1→0.
        // Total: 3+1+0+1 = 5. Same as before!
        //
        // What if BaoBao plays P first?
        //   BaoBao P (2 times): DreamGrid S (1 time, +1), DreamGrid P (1 time, 0). ds: 1→0, dp: 2→1.
        //   BaoBao S (3 times): DreamGrid R (3 times, +1). dr: 3→0.
        //   BaoBao R (1 time): DreamGrid P (1 time, +1). dp: 1→0.
        // Total: 1+0+1+1+1 = 5. Same!
        //
        // It seems like the order doesn't matter for sample 3. The answer is always 5.
        //
        // Why? Because DreamGrid has enough cards to counter all of BaoBao's cards
        // in the most favorable matchups. The total wins = 5, losses = 0 (or minimal).
        //
        // I think the correct formula is:
        // DreamGrid score = max(0, W - L) where:
        // W = min(dp, br) + min(ds, bp) + min(dr, bs)
        // L = max(0, br - dp - dr) + max(0, bp - ds - dp) + max(0, bs - dr - ds)
        // No wait, that's not right either.
        //
        // Let me think about it differently.
        // DreamGrid's score from BaoBao's R cards:
        //   +1 for min(dp, br) cards (DreamGrid plays P)
        //   0 for min(max(0, br-dp), dr) cards (DreamGrid plays R)
        //   -1 for max(0, br-dp-dr) cards (DreamGrid plays S)
        // Net from BaoBao R: min(dp, br) - max(0, br-dp-dr)
        //
        // DreamGrid's score from BaoBao's P cards:
        //   +1 for min(ds, bp) cards
        //   0 for min(max(0, bp-ds), dp') cards (dp' is remaining dp after R cards)
        //   -1 for max(0, bp-ds-dp') cards
        // Net from BaoBao P: min(ds, bp) - max(0, bp-ds-dp')
        //
        // But dp' depends on how many P cards DreamGrid used for BaoBao's R cards.
        // dp' = dp - min(dp, br).
        //
        // Similarly for other card types.
        //
        // The total score depends on the ORDER. BaoBao chooses the order to minimize.
        //
        // For the optimal order, BaoBao should play card types in an order that
        // minimizes DreamGrid's net score. This is complex.
        //
        // I think the answer is simply:
        // DreamGrid score = max(0, 
        //   min(dp, br) + min(ds, bp) + min(dr, bs)
        //   - min(dr, bp) - min(dp, bs) - min(ds, br))
        // 
        // But this gives 0 for sample 3. So either my formula is wrong or my sample computation is wrong.
        //
        // Let me recompute sample 3:
        // DreamGrid: R=3,P=2,S=1. BaoBao: R=1,P=2,S=3.
        // W = min(2,1)+min(1,2)+min(3,3) = 1+1+3 = 5.
        // L = min(3,2)+min(2,3)+min(1,1) = 2+2+1 = 5.
        // W-L = 0. But answer is 5.
        //
        // I think the issue is: L should not include matchups where DreamGrid already won.
        // When DreamGrid plays R to beat BaoBao S, that R card is used.
        // BaoBao can't use that same R card to beat DreamGrid S.
        //
        // The correct L: BaoBao's wins are limited by DreamGrid's remaining cards after wins.
        // After DreamGrid uses min(dp,br) P, min(ds,bp) S, min(dr,bs) R for wins:
        //   DreamGrid remaining: R' = dr-min(dr,bs), P' = dp-min(dp,br), S' = ds-min(ds,bp).
        //   BaoBao remaining: R' = br-min(dp,br), P' = bp-min(ds,bp), S' = bs-min(dr,bs).
        //   BaoBao's losses (DreamGrid's wins in remaining): already accounted for.
        //   BaoBao's wins (DreamGrid's losses in remaining):
        //     BaoBao R' vs DreamGrid S': min(R', S')
        //     BaoBao P' vs DreamGrid R': min(P', R')
        //     BaoBao S' vs DreamGrid P': min(S', P')
        //   L' = min(br-min(dp,br), ds-min(ds,bp)) + min(bp-min(ds,bp), dr-min(dr,bs)) + min(bs-min(dr,bs), dp-min(dp,br))
        //
        // Sample 3:
        // After wins: DreamGrid R'=3-3=0, P'=2-1=1, S'=1-1=0.
        //   BaoBao R'=1-1=0, P'=2-1=1, S'=3-3=0.
        //   L' = min(0,0)+min(1,0)+min(0,1) = 0+0+0 = 0.
        // Score = W - L' = 5 - 0 = 5. Correct!
        //
        // Sample 1:
        // DreamGrid: R=10,P=0,S=0. BaoBao: R=4,P=4,S=2.
        // After wins: DreamGrid R'=10-2=8, P'=0-0=0, S'=0-0=0.
        //   BaoBao R'=4-0=4, P'=4-0=4, S'=2-2=0.
        //   L' = min(4,0)+min(4,8)+min(0,0) = 0+4+0 = 4.
        // Score = 2 - 4 = -2. Correct!
        //
        // Sample 2:
        // DreamGrid: R=2,P=4,S=4. BaoBao: R=0,P=10,S=0.
        // After wins: DreamGrid R'=2-0=2, P'=4-0=4, S'=4-4=0.
        //   BaoBao R'=0-0=0, P'=10-4=6, S'=0-0=0.
        //   L' = min(0,0)+min(6,2)+min(0,4) = 0+2+0 = 2.
        // Score = 4 - 2 = 2. Correct!
        //
        // So the formula is:
        // W = min(dp,br) + min(ds,bp) + min(dr,bs)
        // L' = min(br-min(dp,br), ds-min(ds,bp)) + min(bp-min(ds,bp), dr-min(dr,bs)) + min(bs-min(dr,bs), dp-min(dp,br))
        // Score = W - L'
        
        long long W = min(dp, br) + min(ds, bp) + min(dr, bs);
        long long L2 = min(br - min(dp, br), ds - min(ds, bp))
                     + min(bp - min(ds, bp), dr - min(dr, bs))
                     + min(bs - min(dr, bs), dp - min(dp, br));
        cout << W - L2 << "\n";
    }
    return 0;
}
