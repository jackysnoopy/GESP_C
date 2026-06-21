#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<string> inputs(M);
        vector<int> out(M);
        for (int i = 0; i < M; ++i) {
            cin >> inputs[i] >> out[i];
        }
        bool ok = false;
        for (int b = 0; b < N; ++b) {
            bool can0 = true, can1 = true;
            for (int i = 0; i < M; ++i) {
                if (inputs[i][b] == '0' && out[i] != 0) can0 = false;
                if (inputs[i][b] == '1' && out[i] != 1) can1 = false;
            }
            if (can0 || can1) { ok = true; break; }
        }
        cout << (ok ? "OK" : "LIE") << '\n';
    }
    return 0;
}
