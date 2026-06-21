#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<int> a(N);
    vector<int> cnt(N + 2, 0);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (a[i] <= N) cnt[a[i]]++;
    }
    int extra = 0;
    for (int i = 0; i <= N; i++) {
        if (i > 0) {
            if (cnt[i - 1] == 0) extra++;
        }
        int need = 0;
        for (int j = 0; j < i; j++) {
            if (cnt[j] == 0) need++;
        }
        int remove = 0;
        for (int j = 0; j < i; j++) {
            if (cnt[j] > 1) remove += cnt[j] - 1;
        }
        cout << max(need, remove) << "\n";
    }
    return 0;
}
