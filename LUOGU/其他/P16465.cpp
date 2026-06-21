#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        vector<string> names(n);
        cin.ignore();
        for (int i = 0; i < n; i++) {
            getline(cin, names[i]);
        }
        
        int cost = 0;
        string current_max = names[0];
        for (int i = 1; i < n; i++) {
            if (names[i] < current_max) {
                cost++;
            } else {
                current_max = names[i];
            }
        }
        
        cout << "Case #" << t << ": " << cost << endl;
    }
    
    return 0;
}
