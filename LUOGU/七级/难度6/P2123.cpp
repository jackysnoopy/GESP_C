#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Minister {
    long long a, b;
};

bool compare(const Minister& x, const Minister& y) {
    if (x.a * x.b != y.a * y.b) {
        return x.a * x.b < y.a * y.b;
    }
    return x.a < y.a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<Minister> ministers(n);
        for (int i = 0; i < n; i++) {
            cin >> ministers[i].a >> ministers[i].b;
        }
        
        // Sort by a * b
        sort(ministers.begin(), ministers.end(), compare);
        
        // Calculate minimum maximum reward
        long long sum_a = 0;
        long long prev_reward = 0;
        long long max_reward = 0;
        
        for (int i = 0; i < n; i++) {
            sum_a += ministers[i].a;
            long long reward = max(prev_reward, sum_a) + ministers[i].b;
            max_reward = max(max_reward, reward);
            prev_reward = reward;
        }
        
        cout << max_reward << "\n";
    }
    
    return 0;
}
