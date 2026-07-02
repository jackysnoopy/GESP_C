#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cow {
    int up, down;
};

bool cmp(const Cow& a, const Cow& b) {
    return a.up > b.up;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Cow> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i].up >> cows[i].down;
    }
    
    sort(cows.begin(), cows.end(), cmp);
    
    int time_fj = 0, time_fd = 0;
    for (int i = 0; i < n; i++) {
        if (time_fj <= time_fd) {
            time_fj += cows[i].up;
            time_fd = max(time_fd, time_fj) + cows[i].down;
        } else {
            time_fd += cows[i].down;
            time_fj = max(time_fj, time_fd) + cows[i].up;
        }
    }
    
    cout << max(time_fj, time_fd) << endl;
    
    return 0;
}
