#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<char> type(N);
        vector<int> id(N);
        
        for (int i = 0; i < N; i++) {
            cin >> type[i] >> id[i];
        }
        
        // 简化：模拟过程
        vector<int> inside;
        int unknown_in = 0;
        bool impossible = false;
        
        for (int i = 0; i < N; i++) {
            if (type[i] == 'E') {
                if (id[i] == 0) {
                    unknown_in++;
                } else {
                    inside.push_back(id[i]);
                }
            } else {
                if (id[i] == 0) {
                    if (!inside.empty()) {
                        inside.pop_back();
                    } else if (unknown_in > 0) {
                        unknown_in--;
                    } else {
                        impossible = true;
                        break;
                    }
                } else {
                    bool found = false;
                    for (int j = 0; j < inside.size(); j++) {
                        if (inside[j] == id[i]) {
                            inside.erase(inside.begin() + j);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        impossible = true;
                        break;
                    }
                }
            }
        }
        
        if (impossible) {
            cout << "Case #" << t << ": CRIME TIME" << endl;
        } else {
            cout << "Case #" << t << ": " << inside.size() + unknown_in << endl;
        }
    }
    
    return 0;
}
