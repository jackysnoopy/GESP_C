#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<pair<string,int>> events(N);
        for (int i = 0; i < N; i++) {
            cin >> events[i].first >> events[i].second;
        }
        
        cout << "Case #" << t << ": ";
        
        // Track known persons inside, mask persons
        map<int, int> inside; // id -> count of known entries not yet matched
        int inside_count = 0;
        int min_people = 0;
        bool possible = true;
        
        for (int i = 0; i < N && possible; i++) {
            string type = events[i].first;
            int id = events[i].second;
            
            if (type == "E") {
                if (id == 0) {
                    // Mask person enters: could be anyone
                    // To minimize final count, assume it's someone already inside
                    if (inside_count > 0) {
                        inside_count--;
                    } else {
                        // New person
                        min_people++;
                    }
                } else {
                    inside[id]++;
                    inside_count++;
                }
            } else { // "L"
                if (id == 0) {
                    // Mask person leaves
                    // To minimize final count, assume it's someone known inside
                    if (inside_count > 0) {
                        inside_count--;
                    } else {
                        // Must be someone who entered via mask earlier
                        min_people--;
                        if (min_people < 0) {
                            possible = false;
                        }
                    }
                } else {
                    if (inside[id] > 0) {
                        inside[id]--;
                        inside_count--;
                    } else {
                        possible = false;
                    }
                }
            }
        }
        
        if (!possible) {
            cout << "CRIME TIME\n";
        } else {
            // Count remaining known people
            int remaining = 0;
            for (auto& p : inside) remaining += p.second;
            cout << remaining << "\n";
        }
    }
    
    return 0;
}