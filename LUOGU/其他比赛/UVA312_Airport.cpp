#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Flight {
    int arrive, depart;
    int gate;
};

bool cmp(const Flight& a, const Flight& b) {
    return a.arrive < b.arrive;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<Flight> flights(n);
        for (int i = 0; i < n; i++) {
            cin >> flights[i].arrive >> flights[i].depart;
            flights[i].gate = -1;
        }
        sort(flights.begin(), flights.end(), cmp);
        vector<int> gateEnd;
        int maxGates = 0;
        for (int i = 0; i < n; i++) {
            int bestGate = -1;
            for (int g = 0; g < (int)gateEnd.size(); g++) {
                if (gateEnd[g] <= flights[i].arrive) {
                    if (bestGate == -1 || gateEnd[g] > gateEnd[bestGate])
                        bestGate = g;
                }
            }
            if (bestGate == -1) {
                flights[i].gate = gateEnd.size();
                gateEnd.push_back(flights[i].depart);
            } else {
                flights[i].gate = bestGate;
                gateEnd[bestGate] = flights[i].depart;
            }
            maxGates = max(maxGates, (int)gateEnd.size());
        }
        cout << maxGates << "\n";
    }
    return 0;
}
