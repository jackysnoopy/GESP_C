#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int val(char c) {
    if (c == 'A') return 1;
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<deque<int>> piles(14);
    for (int i = 1; i <= 13; i++) {
        for (int j = 0; j < 4; j++) {
            string s; cin >> s;
            piles[i].push_back(val(s[0]));
        }
    }
    
    int ans = 0;
    while (!piles[13].empty()) {
        int v = piles[13].front();
        piles[13].pop_front();
        if (v == 13) {
            ans++;
        } else {
            piles[v].push_front(v);
            int cur = piles[v].back();
            piles[v].pop_back();
            while (cur != 13) {
                piles[cur].push_front(cur);
                cur = piles[cur].back();
                piles[cur].pop_back();
            }
            ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}