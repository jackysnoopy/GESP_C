#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    vector<int> stones(m);
    for (int i = 0; i < m; i++) {
        cin >> stones[i];
    }
    
    stones.insert(stones.begin(), 0);
    stones.push_back(n);
    
    int total = m + 2;
    vector<int> order(total);
    for (int i = 0; i < total; i++) {
        order[i] = i;
    }
    
    bool found = false;
    vector<int> result;
    
    do {
        bool valid = true;
        for (int i = 1; i < total; i++) {
            int dist = abs(stones[order[i]] - stones[order[i-1]]);
            if (dist < s) {
                valid = false;
                break;
            }
        }
        if (valid) {
            found = true;
            result = order;
            break;
        }
    } while (next_permutation(order.begin() + 1, order.end() - 1));
    
    if (found) {
        cout << "YES" << endl;
        for (int i = 0; i < total; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}