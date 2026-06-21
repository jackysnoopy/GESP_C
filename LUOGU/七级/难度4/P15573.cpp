#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    cin >> N >> H;

    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    int k;
    cin >> k;

    vector<int> win(k);
    for (int i = 0; i < k; i++) cin >> win[i];

    int Q;
    cin >> Q;

    while (Q--) {
        long long t;
        cin >> t;

        long long elixir = 0;
        int win_count = 0;
        int hand = 0;

        for (long long time = 1; time <= t && hand < N; time++) {
            elixir++;

            bool has_win = false;
            for (int i = 0; i < k; i++) {
                if (win[i] >= hand + 1 && win[i] <= hand + H) {
                    has_win = true;
                    break;
                }
            }

            if (has_win) {
                for (int i = 0; i < k; i++) {
                    if (win[i] >= hand + 1 && win[i] <= hand + H) {
                        if (elixir >= a[win[i] - 1]) {
                            elixir -= a[win[i] - 1];
                            win_count++;
                            hand++;
                            break;
                        }
                    }
                }
            } else {
                if (elixir >= a[hand]) {
                    elixir -= a[hand];
                    hand++;
                }
            }
        }

        cout << win_count << "\n";
    }

    return 0;
}
