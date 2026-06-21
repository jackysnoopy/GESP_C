#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;

        vector<int> cards(N);
        for (int i = 0; i < N; i++) cin >> cards[i];

        sort(cards.begin(), cards.end());

        int ans = 0;
        int i = 0;

        while (i < N) {
            int j = i;
            while (j < N && cards[j] == cards[i] + (j - i)) j++;
            ans = max(ans, j - i);
            i = j;
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
