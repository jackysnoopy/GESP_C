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
        long long E, R;
        int N;
        cin >> E >> R >> N;

        vector<long long> v(N);
        for (int i = 0; i < N; i++) cin >> v[i];

        long long ans = 0;
        long long energy = E;

        for (int i = 0; i < N; i++) {
            long long spend = energy;
            for (int j = i + 1; j < N; j++) {
                if (v[j] > v[i]) {
                    long long needed = max(0LL, E - R * (j - i));
                    spend = min(spend, energy - needed);
                }
            }
            spend = max(spend, 0LL);
            ans += spend * v[i];
            energy = min(E, energy - spend + R);
        }

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
