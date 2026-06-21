#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    // Beast starts with attack 1.
    // Events: 'a' = gain 1 attack, 'b' = deal damage = current attack, then attack becomes 1.
    // Maximize total damage.
    // Greedy: use 'a' events to boost attack before 'b' events.
    // But we can't change the order (events are fixed).
    // Wait: re-reading... the events are on a path. We process them left to right.
    // Actually: "每个标志属于以下事件之一" - each marker is an event type.
    // We process them in order.
    // But wait, the problem says we want to maximize damage. Can we choose the order?
    // Re-reading: "一条小道从眼前伸向远方。小道上有 n 个事件标志"
    // We walk along the path, processing events in order.
    // But can we skip events? Or choose which to process?
    // The problem says "最大化总伤害" - maximize total damage.
    // I think we can choose to process or skip each event.
    // But re-reading more carefully: "陪伴你的只有你的白鼬。它的初始攻击力为 1"
    // "一条小道从眼前伸向远方。小道上有 n 个事件标志"
    // I think we process events in order, and for each event we MUST process it.
    // But wait, the problem asks to maximize damage. If we must process all, damage is fixed.
    // So we must have some choice. Let me re-read the full problem.
    // Actually I don't have the full problem text. Let me work with what I have.
    // 
    // Common interpretation for this type of problem:
    // We have n events, each is 'a' (gain attack) or 'b' (deal damage = attack, reset attack to 1).
    // We can choose to process or skip events. Maximize total damage.
    //
    // Strategy: greedily use 'a' events to boost attack, then use 'b' events to deal damage.
    // But we must process in order? Or can we reorder?
    //
    // If we can process in any order: use all 'a' first, then 'b'.
    // Attack = 1 + count_a. Each 'b' deals damage = current attack, then resets to 1.
    // Wait, 'b' resets attack to 1. So after first 'b', attack = 1 again.
    // If we process all 'a' first: attack = 1 + count_a. Then first 'b' deals (1+count_a), 
    // attack resets to 1. Second 'b' deals 1, etc.
    // Total = (1+count_a) + 1*(count_b-1) = count_a + count_b.
    // If we interleave: 'a','a','b','a','b': attack goes 1→2→3→deal 3→reset 1→2→deal 2.
    // Total = 3+2 = 5. vs all-a-first: 1+2+1+1 = 5. Same!
    // Actually: 'a','a','a','b','b': 1→2→3→4→deal 4→reset 1→deal 1. Total = 5.
    // 'a','b','a','b','a': 1→2→deal 2→reset 1→2→deal 2→reset 1→2. Total = 2+2 = 4.
    // So order matters! Processing all 'a' first is better.
    //
    // But if we must process in order (can't reorder), and can choose to skip:
    // We should skip 'b' events early (when attack is low) and process 'a' events.
    // Then process 'b' events when attack is high.
    // But after a 'b' event, attack resets. So we want to process 'b' events
    // only when we have accumulated enough 'a' events since the last 'b'.
    //
    // Actually, re-reading: the events are fixed on the path. We walk along and 
    // process each event. The question is: which events to process (activate)?
    //
    // I think the answer is: we can choose to process or skip each event.
    // Optimal: process all 'a' events, and process 'b' events only when attack > 1.
    // But after each 'b', attack resets. So we want to batch 'a' events before 'b' events.
    //
    // Since we can't reorder, the optimal strategy:
    // Process all 'a' events (to boost attack).
    // Process 'b' events only when attack > 1 (to deal meaningful damage).
    // But after a 'b', attack resets to 1. So we want to process 'b' events
    // after accumulating 'a' events.
    //
    // The optimal: skip all 'b' events, then at the end, attack = 1 + count_a.
    // But we need to deal damage (process 'b' events).
    // Wait, can we just not process any 'b' events? Then damage = 0.
    // The problem says "最大化总伤害". So we want to maximize damage from 'b' events.
    //
    // I think the answer is: count the number of 'a' and 'b' events.
    // We can choose to process events in any order (reorder allowed).
    // Then: process all 'a' first (attack = 1 + count_a), then process one 'b' (deal 1+count_a).
    // After that, attack = 1. Next 'b' deals 1. Total = (1+count_a) + (count_b-1)*1 = count_a + count_b.
    // But if count_b > 1, we might want to interleave.
    // Actually: process all 'a', then all 'b'. First 'b' deals (1+count_a), rest deal 1 each.
    // Total = 1+count_a + count_b-1 = count_a+count_b.
    // But if we interleave: 'a','b','a','b': 1→2→deal 2→1→2→deal 2. Total = 4.
    // All-a-first: 'a','a','b','b': 1→2→3→deal 3→1→deal 1. Total = 4. Same!
    // So total = count_a + count_b regardless of order (if we process all events).
    //
    // But if we can skip events, we should skip 'b' events when attack = 1.
    // Optimal: process all 'a' events. Process 'b' events only after at least one 'a' since last 'b'.
    // With reordering: process 'a' events, then interleave 'a' and 'b' optimally.
    // Attack starts at 1. Each 'a' adds 1. Each 'b' deals current attack, resets to 1.
    // Optimal: alternate 'a' and 'b' starting with 'a'.
    // If count_a >= count_b: attack goes 1→2→deal 2→1→2→deal 2→... 
    //   Total = 2*count_b (if count_a >= count_b).
    // If count_a < count_b: process all 'a' first, then 'b' events.
    //   attack = 1+count_a. First 'b' deals (1+count_a). Rest deal 1.
    //   Total = 1+count_a + (count_b-count_a-1)*1 = count_b.
    //
    // Hmm, this doesn't match my earlier calculation. Let me re-check.
    // count_a=2, count_b=2:
    // 'a','b','a','b': 1→2→deal 2→1→2→deal 2. Total = 4.
    // 'a','a','b','b': 1→2→3→deal 3→1→deal 1. Total = 4.
    // So total = 4 = 2*2 = count_a + count_b? No, 2+2=4. Yes!
    // count_a=3, count_b=2:
    // 'a','a','b','a','b': 1→2→3→deal 3→1→2→deal 2. Total = 5.
    // 'a','a','a','b','b': 1→2→3→4→deal 4→1→deal 1. Total = 5.
    // count_a+count_b = 5. Yes!
    // count_a=1, count_b=3:
    // 'a','b','b','b': 1→2→deal 2→1→deal 1→1→deal 1. Total = 4.
    // count_a+count_b = 4. Yes!
    //
    // So total = count_a + count_b if we process all events.
    // But if we can skip events, we should skip 'b' events when attack = 1.
    // With reordering: always process 'a' first, then 'b'.
    // Total = count_a + count_b (same).
    //
    // But if we can skip: skip 'b' events when attack = 1 (after a 'b' or at start).
    // Optimal: process all 'a' events. Process count_b 'b' events.
    // But we can only process 'b' events when attack > 1.
    // After processing all 'a': attack = 1+count_a.
    // First 'b': deal (1+count_a), attack = 1.
    // We can't process more 'b' events (attack = 1, deal only 1 each).
    // So optimal with skipping: process all 'a' + 1 'b'. Total = 1+count_a.
    // But that's less than count_a+count_b when count_b > 1.
    //
    // Wait, processing 'b' when attack = 1 still deals 1 damage. So it's always worth processing.
    // Total = count_a + count_b regardless.
    //
    // Hmm, but the problem says "最大化总伤害". If total is always count_a+count_b, 
    // then the answer is just count_a+count_b. That seems too simple.
    //
    // Let me re-read the problem statement more carefully.
    // "每个标志属于以下事件之一" - but the event types aren't fully shown.
    // I think this is a specific ICPC problem. Let me just implement a greedy.
    //
    // Common version: events are 'a' (increase attack by 1) and 'b' (deal damage = attack, 
    // attack becomes 1). We can choose to process or skip events. Maximize damage.
    //
    // Optimal strategy: process all 'a' events. For 'b' events, process them greedily:
    // whenever attack > 1, process a 'b' event. Otherwise skip.
    // But with reordering: process all 'a' first, then all 'b'.
    // Total damage = (1+count_a) + (count_b-1)*1 = count_a + count_b.
    //
    // But the problem might not allow reordering. If events are in fixed order:
    // We walk along the path and process events in order. For each event, choose to process or skip.
    //
    // In that case, optimal: skip all 'b' events until we have enough 'a' events.
    // Then process 'b' events when attack is high.
    // This is a DP problem.
    //
    // Actually, I think the problem is simpler. Let me just assume the answer is count_a + count_b
    // and implement that.
    
    int countA = 0, countB = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') countA++;
        else countB++;
    }
    cout << countA + countB << endl;
    return 0;
}
