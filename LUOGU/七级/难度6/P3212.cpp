#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
struct Task { int t, a, b; };
vector<Task> tasks;

long long simulate(vector<int>& order3) {
    long long tA = 0, tB = 0;
    vector<int> type1, type2;
    for (int i = 0; i < n; i++) {
        if (tasks[i].t == 1) type1.push_back(i);
        else if (tasks[i].t == 2) type2.push_back(i);
    }
    int i1 = 0, i2 = 0, i3 = 0;
    while (i1 < (int)type1.size() || i2 < (int)type2.size() || i3 < (int)order3.size()) {
        bool done = true;
        if (i1 < (int)type1.size()) {
            int idx = type1[i1];
            tA += tasks[idx].a;
            tB = max(tB, tA) + tasks[idx].b;
            i1++; done = false;
        }
        if (i2 < (int)type2.size()) {
            int idx = type2[i2];
            tB += tasks[idx].b;
            tA = max(tA, tB) + tasks[idx].a;
            i2++; done = false;
        }
        if (i3 < (int)order3.size()) {
            int idx = order3[i3];
            tA += tasks[idx].a;
            tB += tasks[idx].b;
            i3++; done = false;
        }
        if (done) break;
    }
    return max(tA, tB);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    tasks.resize(n);
    for (int i = 0; i < n; i++) cin >> tasks[i].t >> tasks[i].a >> tasks[i].b;
    vector<int> type3;
    for (int i = 0; i < n; i++) if (tasks[i].t == 3) type3.push_back(i);
    long long ans = 1e18;
    do {
        ans = min(ans, simulate(type3));
    } while (next_permutation(type3.begin(), type3.end()));
    cout << ans << "\n";
    return 0;
}
