#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        vector<stack<int>> piles(n);
        for (int i = 0; i < n; i++) {
            int m;
            cin >> m;
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;
                piles[i].push(x);
            }
        }

        vector<int> result;
        bool valid = true;

        for (int target = 1; target <= n; target++) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                if (!piles[i].empty() && piles[i].top() == target) {
                    piles[i].pop();
                    result.push_back(target);
                    found = true;
                    break;
                }
            }
            if (!found) {
                valid = false;
                break;
            }
        }

        if (valid) {
            for (int i = 0; i < (int)result.size(); i++) {
                if (i) cout << " ";
                cout << result[i];
            }
            cout << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
