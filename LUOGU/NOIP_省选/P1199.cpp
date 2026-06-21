#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    
    // The computer's strategy: when it's the computer's turn, it finds the max value among
    // (all pairs of human's generals x all free generals), and picks that free general.
    
    // Key insight: sort all values. The player wants to guarantee that his best pair > computer's best pair.
    // The computer always picks the best available pairing.
    
    // Strategy: sort all values in decreasing order. The player can guarantee to get the 
    // (n/2 + 1)-th largest value as his best pair (the computer steals the top n/2 pairs).
    // Actually more precisely: after sorting all C(n,2) pairs in decreasing order,
    // the player's best possible pair value is the (n/2+1)-th value in the sorted list.
    
    // Because each round, the computer picks the best pairing with player's general.
    // The player picks first, then computer.
    // In each round of picking (player then computer), one pair is "consumed" by the computer.
    // After n rounds, the computer has taken n/2 pairs, and the player has n/2 generals.
    // The computer's best pair will be at most the (n/2)-th largest in some sense...
    
    // Actually the answer is simpler: sort all C(n,2) values in decreasing order.
    // The answer is the (n/2 + 1)-th value (1-indexed).
    // The player can always achieve this by picking the two generals that form this pair.
    // The computer can steal at most n/2 of the top values.
    
    vector<int> all;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            all.push_back(a[i][j]);
    sort(all.begin(), all.end(), greater<int>());
    
    // Player's best guaranteed pair: the (n/2 + 1)-th largest
    cout << 1 << "\n";
    cout << all[n / 2] << "\n";
    return 0;
}
