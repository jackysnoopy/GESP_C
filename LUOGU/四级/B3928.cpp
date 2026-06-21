#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    multiset<int> myHorses;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        myHorses.insert(x);
    }
    vector<int> tian(N);
    for (int i = 0; i < N; i++) cin >> tian[i];
    
    int win = 0;
    for (int v : tian) {
        auto it = myHorses.upper_bound(v);
        if (it != myHorses.end()) {
            win++;
            myHorses.erase(it);
        } else {
            myHorses.erase(myHorses.begin());
        }
    }
    cout << win << "\n";
    return 0;
}
