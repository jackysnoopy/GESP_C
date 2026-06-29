#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> elsie(n);
    for (int i = 0; i < n; i++) {
        cin >> elsie[i];
    }
    
    // Determine Bessie's cards
    set<int> all_cards;
    for (int i = 1; i <= 2 * n; i++) {
        all_cards.insert(i);
    }
    
    for (int card : elsie) {
        all_cards.erase(card);
    }
    
    vector<int> bessie(all_cards.begin(), all_cards.end());
    sort(bessie.begin(), bessie.end());
    sort(elsie.begin(), elsie.end());
    
    // For each possible switch point, calculate points
    int max_points = 0;
    
    for (int switch_point = 0; switch_point <= n; switch_point++) {
        // High card wins for first switch_point rounds
        // Low card wins for remaining rounds
        
        int points = 0;
        
        // High card wins
        int b_ptr = bessie.size() - 1;
        int e_ptr = 0;
        
        for (int i = 0; i < switch_point && b_ptr >= 0; i++) {
            if (bessie[b_ptr] > elsie[e_ptr]) {
                points++;
                b_ptr--;
                e_ptr++;
            } else {
                b_ptr--;
            }
        }
        
        // Low card wins
        for (int i = switch_point; i < n; i++) {
            if (bessie[b_ptr] < elsie[e_ptr]) {
                points++;
                b_ptr--;
                e_ptr++;
            } else {
                b_ptr--;
            }
        }
        
        max_points = max(max_points, points);
    }
    
    cout << max_points << "\n";
    return 0;
}
