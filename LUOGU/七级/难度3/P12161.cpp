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
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i + 1;
    sort(order.begin(), order.end(), greater<int>());
    multiset<int> cards;
    for (int i = 1; i <= n; i++) cards.insert(i);
    long long score = 0;
    for (int d : order) {
        int b = p[d];
        auto it = cards.upper_bound(b);
        if (it != cards.end()) {
            score += d;
            cards.erase(it);
        } else {
            auto bit = cards.find(b);
            if (bit != cards.end()) {
                cards.erase(bit);
            } else {
                score -= d;
                cards.erase(cards.begin());
            }
        }
    }
    cout << score << "\n";
    return 0;
}
