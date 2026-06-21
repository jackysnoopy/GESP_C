#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    set<int> elsie;
    for (int i = 0; i < n; i++) { int x; cin >> x; elsie.insert(x); }
    set<int> bessie;
    for (int i = 1; i <= 2*n; i++)
        if (!elsie.count(i)) bessie.insert(i);
    // First half: high card wins
    int ans = 0;
    auto eit = elsie.begin();
    for (auto bit = bessie.begin(); bit != bessie.end(); bit++) {
        if (eit == elsie.end()) break;
        if (*bit > *eit) { ans++; eit++; }
    }
    // Second half: low card wins - use remaining cards
    set<int> brem = bessie;
    set<int> erem = elsie;
    // Actually need to split into first n/2 and last n/2 rounds
    // First n/2 rounds: maximize high card wins
    // Last n/2 rounds: maximize low card wins
    // Process separately
    
    // Reset and do properly
    bessie.clear(); elsie.clear();
    vector<int> evec;
    for (int i = 0; i < n; i++) { int x; cin >> x; elsie.insert(x); evec.push_back(x); }
    for (int i = 1; i <= 2*n; i++)
        if (!elsie.count(i)) bessie.insert(i);
    
    // First half: high wins. Pick n/2 of Elsie's cards (she plays them in order)
    // Actually Elsie plays them in given order. First n/2 are high rounds.
    int half = n/2;
    // For first half: match Bessie's smallest beating card to each Elsie card
    int score1 = 0;
    set<int> b1 = bessie;
    for (int i = 0; i < half; i++) {
        auto it = b1.upper_bound(evec[i]);
        if (it != b1.end()) { score1++; b1.erase(it); }
    }
    // For second half: low wins. Match Bessie's largest losing card
    int score2 = 0;
    set<int> b2 = bessie;
    for (int i = half; i < n; i++) {
        auto it = b2.lower_bound(evec[i]);
        if (it != b2.begin()) { it--; score2++; b2.erase(it); }
    }
    cout << score1 + score2 << "\n";
    return 0;
}
