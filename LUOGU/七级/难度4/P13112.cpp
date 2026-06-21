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
        int A;
        cin >> A;

        vector<string> programs(A);
        for (int i = 0; i < A; i++) cin >> programs[i];

        string result = "";
        bool possible = true;

        for (int len = 1; len <= 500 && possible; len++) {
            for (char c : {'R', 'P', 'S'}) {
                string candidate = result + c;
                bool beats_all = true;

                for (auto& prog : programs) {
                    bool beats = false;
                    for (int i = 0; i < len; i++) {
                        char my_move = candidate[i % candidate.size()];
                        char their_move = prog[i % prog.size()];

                        if (my_move == 'R' && their_move == 'S') beats = true;
                        else if (my_move == 'P' && their_move == 'R') beats = true;
                        else if (my_move == 'S' && their_move == 'P') beats = true;

                        if (beats) break;
                    }

                    if (!beats) {
                        beats_all = false;
                        break;
                    }
                }

                if (beats_all) {
                    result = candidate;
                    possible = false;
                    break;
                }
            }
        }

        cout << "Case #" << t << ": ";
        if (result.empty()) cout << "IMPOSSIBLE\n";
        else cout << result << "\n";
    }

    return 0;
}
