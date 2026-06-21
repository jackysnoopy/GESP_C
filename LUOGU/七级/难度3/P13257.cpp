#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct BIT {
    int n;
    vector<int> t;
    BIT(int n=0):n(n),t(n+1,0){}
    void add(int i,int v){ for(++i; i<=n; i+=i&(-i)) t[i]+=v; }
    int sum(int i){ int s=0; for(++i; i>0; i-=i&(-i)) s+=t[i]; return s; }
};

int main(){
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){
        int N; cin >> N;
        vector<long long> A(N);
        for(int i=0;i<N;++i) cin >> A[i];
        vector<pair<long long,int>> v(N);
        for(int i=0;i<N;++i) v[i] = {A[i], i};
        sort(v.begin(), v.end());           // increasing value

        BIT bit(N);
        const long long INF = LLONG_MAX/4;
        vector<long long> dp(N+1, INF), ndp(N+1, INF);
        dp[0] = 0;
        for(int i=0;i<N;++i){
            int p = v[i].second;            // original index of i-th smallest
            int placed_left = (p==0) ? 0 : bit.sum(p-1);
            long long unplaced_total = N - i;          // including current
            long long unplaced_left  = (long long)p - placed_left;
            long long unplaced_right = (unplaced_total - 1) - unplaced_left;
            for(int j=0;j<=N;++j) ndp[j] = INF;
            for(int j=0;j<=i;++j){
                if(dp[j] >= INF) continue;
                // place on the increasing (left) side
                if(dp[j] + unplaced_left < ndp[j+1]) ndp[j+1] = dp[j] + unplaced_left;
                // place on the decreasing (right) side
                if(dp[j] + unplaced_right < ndp[j]) ndp[j] = dp[j] + unplaced_right;
            }
            swap(dp, ndp);
            bit.add(p, 1);
        }
        long long ans = *min_element(dp.begin(), dp.end());
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
