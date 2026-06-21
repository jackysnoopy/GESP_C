#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> hand(n);
    for (int i = 0; i < n; i++) cin >> hand[i];
    sort(hand.begin(), hand.end());
    // For each card John has, count how many cards from others are > his card
    // John wins a round if his card is the highest among all cards played that round
    // Optimal opponent: use smallest card that beats John's
    // John wins when opponents can't beat him
    // Binary search on number of wins
    // Actually: sort John's cards. For each card, it beats (nm - card) - (cards after it) cards from others
    // But we need to pair cards in rounds
    // Greedy: sort all cards. John picks his n cards. Others have nm-n cards.
    // John wins a round with card x if x > all opponents' cards in that round.
    // Strategy: opponents play their cards to minimize John's wins.
    // Sort John's cards. For each of John's cards sorted, count opponents' cards greater.
    int total = n * m;
    vector<bool> isJohn(total + 1, false);
    for (int i = 0; i < n; i++) isJohn[hand[i]] = true;
    vector<int> others;
    for (int i = 1; i <= total; i++) if (!isJohn[i]) others.push_back(i);
    // John's cards sorted ascending
    sort(hand.begin(), hand.end());
    // For minimum wins: opponents play optimally
    // For each round, opponents play their smallest card that beats John's if possible
    // John plays cards to maximize wins
    // Min wins: sort John's cards ascending, simulate opponents beating greedily
    int j = 0;
    int losses = 0;
    for (int i = 0; i < n; i++) {
        while (j < (int)others.size() && others[j] < hand[i]) j++;
        if (j < (int)others.size()) { j++; losses++; }
    }
    cout << n - losses << "\n";
    return 0;
}
