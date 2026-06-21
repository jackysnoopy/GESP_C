#include <iostream>
#include <vector>
#include <map>
using namespace std;

// [MX-S1-T2] 催化剂
// Candy distribution. Each candy has a type.
// Operations: add candy of type x, remove candy of type x, query with k.
// Query: divide all candies into k non-empty sequences, minimize anger.
// Anger of a kid = number of times they get the same candy type in sequence.
// Key: for type with count c, if distributed across k sequences:
// anger = max(0, c - k) per type. Total = sum over types of max(0, count - k).
// 
// Wait, actually: if we have count c of type x and k kids, we put them in k sequences.
// Each sequence can have at most 1 of type x without anger.
// So anger = max(0, c - k) for type x.
// Total anger = sum_x max(0, count_x - k).
//
// With add/remove operations, maintain frequency counts and the answer.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    
    map<int, int> freq;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        freq[x]++;
    }
    
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            freq[x]++;
        } else if (op == 2) {
            freq[x]--;
            if (freq[x] == 0) freq.erase(x);
        } else {
            // Query: k = x
            int k = x;
            long long anger = 0;
            for (auto& p : freq) {
                if (p.second > k) anger += p.second - k;
            }
            cout << anger << "\n";
        }
    }
    return 0;
}
