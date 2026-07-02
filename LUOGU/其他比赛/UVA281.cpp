#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Trip {
    int depart, arrive, id;
};

bool cmp(const Trip& a, const Trip& b) {
    return a.depart < b.depart;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Trip> trips(n);
        for (int i = 0; i < n; i++) {
            cin >> trips[i].depart >> trips[i].arrive;
            trips[i].id = i + 1;
        }
        sort(trips.begin(), trips.end(), cmp);
        
        vector<int> platforms;
        vector<int> assign(n);
        
        for (int i = 0; i < n; i++) {
            bool placed = false;
            for (int j = 0; j < platforms.size(); j++) {
                if (trips[platforms[j]].arrive <= trips[i].depart) {
                    platforms[j] = i;
                    assign[trips[i].id - 1] = j + 1;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                assign[trips[i].id - 1] = platforms.size() + 1;
                platforms.push_back(i);
            }
        }
        
        cout << platforms.size() << endl;
        for (int i = 0; i < n; i++) {
            cout << assign[i] << (i == n - 1 ? "\n" : " ");
        }
    }
    return 0;
}
