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
        int N, C, M;
        cin >> N >> C >> M;

        vector<vector<int>> tickets(C + 1);
        for (int i = 0; i < M; i++) {
            int p, b;
            cin >> p >> b;
            tickets[b].push_back(p);
        }

        int max_tickets = 0;
        for (int i = 1; i <= C; i++) {
            max_tickets = max(max_tickets, (int)tickets[i].size());
        }

        int rides = max_tickets;
        int promotions = 0;

        for (int i = 1; i <= C; i++) {
            if (tickets[i].size() > 1) {
                sort(tickets[i].begin(), tickets[i].end());
                for (int j = 1; j < (int)tickets[i].size(); j++) {
                    if (tickets[i][j] <= j) {
                        promotions++;
                    }
                }
            }
        }

        cout << "Case #" << t << ": " << rides << " " << promotions << "\n";
    }

    return 0;
}
