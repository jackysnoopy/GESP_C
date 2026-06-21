#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, K;
    cin >> n >> K;
    vector<int> C(n), d(n);
    for (int i = 0; i < n; i++) cin >> C[i] >> d[i];
    vector<bool> have(K + 1, false);
    for (int i = 0; i < n; i++) {
        if (d[i] == 1) have[C[i]] = true;
    }
    int maxNew = 0, bestPrice = 0;
    for (int price = 1; price < K; price++) {
        int change = K - price;
        vector<int> coins;
        int rem = change;
        for (int i = n - 1; i >= 0 && rem > 0; i--) {
            int cnt = rem / C[i];
            if (cnt > 0) {
                rem -= cnt * C[i];
                for (int j = 0; j < cnt; j++) coins.push_back(C[i]);
            }
        }
        int newCount = 0;
        for (int c : coins) {
            if (!have[c]) newCount++;
        }
        if (newCount > maxNew || (newCount == maxNew && price > bestPrice)) {
            maxNew = newCount;
            bestPrice = price;
        }
    }
    cout << maxNew << "\n" << bestPrice << "\n";
    return 0;
}
