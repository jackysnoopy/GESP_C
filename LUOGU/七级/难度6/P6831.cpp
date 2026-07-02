#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;

extern "C" void allocate_tickets(vector<vector<int>> s);

long long find_maximum(int k, vector<vector<int>> x) {
    int n = x.size();
    int m = x[0].size();
    long long ans = 0;
    
    vector<vector<int>> assign(n, vector<int>(m, -1));
    
    for (int r = 0; r < k; r++) {
        vector<int> picks(n);
        for (int i = 0; i < n; i++) {
            picks[i] = x[i][r];
        }
        
        sort(picks.begin(), picks.end());
        int b = picks[n / 2];
        
        long long reward = 0;
        for (int i = 0; i < n; i++)
            reward += abs((long long)picks[i] - b);
        ans += reward;
        
        for (int i = 0; i < n; i++) {
            assign[i][r] = r;
        }
    }
    
    allocate_tickets(assign);
    
    return ans;
}

extern "C" void allocate_tickets(vector<vector<int>> s) {
    (void)s;
}

#ifndef ONLINE_JUDGE
int main() {
    return 0;
}
#endif
