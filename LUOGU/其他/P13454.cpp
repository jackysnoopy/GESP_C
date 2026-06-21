#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int S;
        cin >> S;
        map<string, int> engineIdx;
        for (int i = 0; i < S; i++) {
            string name;
            cin.ignore();
            getline(cin, name);
            engineIdx[name] = i;
        }
        int Q;
        cin >> Q;
        cin.ignore();
        int cur = -1, switches = 0;
        for (int i = 0; i < Q; i++) {
            string query;
            getline(cin, query);
            int idx = engineIdx[query];
            if (idx == cur) {
                // Can't use this engine
                switches++;
                cur = -1;
            } else {
                cur = idx;
            }
        }
        cout << "Case #" << tc << ": " << switches << "\n";
    }
    return 0;
}
