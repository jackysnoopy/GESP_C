#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<int> fac(a), mne(b);
    sort(fac.begin(), fac.end());
    sort(mne.begin(), mne.end());

    vector<int> result;
    long long cost = 0;
    int pos = 0;
    int load = 0;

    vector<bool> fUsed(n, false), mUsed(n, false);

    for (int step = 0; step < 2 * n; step++) {
        if (load == 0) {
            int bestIdx = -1;
            for (int i = 0; i < n; i++) {
                if (!fUsed[i]) {
                    if (bestIdx == -1 || fac[i] > fac[bestIdx])
                        bestIdx = i;
                }
            }
            fUsed[bestIdx] = true;
            pos = fac[bestIdx];
            load = 1;
            result.push_back(fac[bestIdx]);
        } else {
            int bestIdx = -1;
            for (int i = 0; i < n; i++) {
                if (!mUsed[i]) {
                    if (bestIdx == -1 || abs(mne[i] - pos) < abs(mne[bestIdx] - pos))
                        bestIdx = i;
                }
            }
            mUsed[bestIdx] = true;
            cost += abs(mne[bestIdx] - pos);
            pos = mne[bestIdx];
            load--;
            result.push_back(mne[bestIdx]);
        }
    }

    cout << cost << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << (i + 1 == (int)result.size() ? '\n' : ' ');
    }

    return 0;
}
