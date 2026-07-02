#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int cas = 0;
    while (cin >> n >> m) {
        vector<string> events(n);
        for (int i = 0; i < n; i++) cin >> events[i];

        vector<pair<int, int>> constraints;
        string line;
        getline(cin, line);
        for (int i = 0; i < m; i++) {
            getline(cin, line);
            stringstream ss(line);
            string a, b;
            ss >> a >> b;
            int ai = -1, bi = -1;
            for (int j = 0; j < n; j++) {
                if (events[j] == a) ai = j;
                if (events[j] == b) bi = j;
            }
            if (ai >= 0 && bi >= 0)
                constraints.push_back({ai, bi});
        }

        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;

        int count = 0;
        do {
            bool valid = true;
            for (auto& c : constraints) {
                int pos_a = -1, pos_b = -1;
                for (int i = 0; i < n; i++) {
                    if (order[i] == c.first) pos_a = i;
                    if (order[i] == c.second) pos_b = i;
                }
                if (pos_a > pos_b) { valid = false; break; }
            }
            if (valid) count++;
        } while (next_permutation(order.begin(), order.end()));

        cout << "Case " << ++cas << ": " << count << " valid orderings\n";
    }
    return 0;
}
