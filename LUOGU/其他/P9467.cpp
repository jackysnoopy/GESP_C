#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<int> pos(N);
    pos[0] = 0;
    for (int i = 1; i < N; ++i) {
        vector<int> r(i);
        for (int j = 0; j < i; ++j) cin >> r[j];
        int target = (i + 1) / 2;
        pos[i] = r[target];
    }
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << pos[i];
    }
    cout << '\n';
    return 0;
}
