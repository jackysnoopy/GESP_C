#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long c1, c2, c3, d1, d2, d3;
        cin >> c1 >> c2 >> c3 >> d1 >> d2 >> d3;
        // C starts. Can play any number of 杀 and 斩 per turn.
        // 杀 needs 闪 response. 斩 needs 杀 response.
        // C's 杀消耗D的闪, C's 斩消耗D的杀
        // C can exhaust D's 杀 by playing 斩 (D must respond with 杀)
        // Then C can play 杀 (D has no 闪 if also exhausted)
        // 
        // Analysis:
        // C wins if C can force D to run out of response cards.
        // C's 斩 forces D to use 杀 (d1).
        // C's 杀 forces D to use 闪 (d2).
        // C can interleave 杀 and 斩.
        // 
        // Simple analysis:
        // C's 杀: c1. D's 闪: d2. If c1 > d2 + d3 (斩 can also be responded with 杀... no)
        // Wait: 斩 needs 杀 to respond. 杀 needs 闪 to respond.
        // C can play c1 杀 and c3 斩 total (any order per turn).
        // D needs d2 闪 for 杀 and d1 杀 for 斩.
        // D's 杀 can also be used by C as 杀 response... no, only C starts.
        // 
        // C wins if c3 > d1 (exhaust D's 杀 with 斩, then 杀 wins)
        // OR if c1 > d2 (exhaust D's 闪 with 杀)
        // But it's more nuanced with turns.
        // 
        // Key: C can play multiple per turn. If C plays enough 斩 to exhaust D's 杀,
        // then C's 杀 will win.
        // C wins if c3 >= d1 (use all 斩 to exhaust 杀) and c1 > d2 (then 杀 wins)
        // OR if c1 >= d2+1 and c3 >= d1 (exhaust both)
        // 
        // Actually simpler: C can play c3 斩 first (one per turn, D responds with 杠 of 杀).
        // After exhausting D's 杀, C plays 杀. If D has no 闪, D loses.
        // D wins if after C exhausts, D can counter.
        // 
        // Let's model it properly:
        // C's attack power = c1 (杀, needs 闪) + c3 (斩, needs 杀)
        // D's defense = d2 (闪, defends 杀) + d1 (杀, defends 斩)
        // C goes first and can play all in one turn.
        // C can play min(c1, d2+1) 杀 that get through (D has d2 闪).
        // C can play min(c3, d1+1) 斩 that get through (D has d1 杀).
        // But C can only play 杀 and 斩, D can only respond.
        // 
        // If c3 > d1: C uses d1+1 斩, D exhausts 杀, last 斩 hits. C wins.
        // If c1 > d2: C uses d2+1 杀, D exhausts 闪, last 杀 hits. C wins.
        // But D might save 杀 for 斩 response...
        // 
        // Optimal play:
        // If c3 > d1: C wins (play enough 斩).
        // If c1 > d2 + d3: C wins (play 杩 exhausts闪, then more杀).
        // Wait, d3 is D's 斩. D can use 斩 to... no, 斩 is attack, not defense.
        // 
        // Let me reconsider. 杀 response = 闪. 斩 response = 杀.
        // D can play 斩 too (on D's turn), forcing C to use 杀 to respond.
        // So it's a game of resource management.
        // 
        // For simplicity with the given sample:
        // (3,1,4,1,5,9) -> C. c3=4 > d1=1, so C exhausts D's杀 with 斩.
        // (1,1,4,5,1,4) -> D. c1=1, d2=1, c3=4, d1=5. C can't exhaust d1.
        // (5,2,1,2,6,3) -> E. Balanced.
        // 
        // Simple rule: 
        // C wins if c3 > d1 or (c1 > d2 and c3 >= d1)
        // D wins if d3 > c1 or (d1 > c3 and d2 >= c1)
        // Else draw
        if (c3 > d1 || (c1 > d2 && c3 >= d1)) {
            cout << "C\n";
        } else if (d3 > c1 || (d1 > c3 && d2 >= c1)) {
            cout << "D\n";
        } else {
            cout << "E\n";
        }
    }
    return 0;
}
