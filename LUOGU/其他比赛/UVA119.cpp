#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) cout << "\n";
        first = false;
        
        vector<string> names(n);
        map<string, int> name2id;
        for (int i = 0; i < n; i++) {
            cin >> names[i];
            name2id[names[i]] = i;
        }
        
        vector<int> money(n, 0);
        
        for (int i = 0; i < n; i++) {
            string giver;
            int total, k;
            cin >> giver >> total >> k;
            int gId = name2id[giver];
            
            if (k > 0) {
                int each = total / k;
                money[gId] -= each * k;
                for (int j = 0; j < k; j++) {
                    string recv;
                    cin >> recv;
                    int rId = name2id[recv];
                    money[rId] += each;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            cout << names[i] << " " << money[i] << "\n";
        }
    }
    return 0;
}
