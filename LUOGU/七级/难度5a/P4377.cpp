#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long W;
    if(!(cin>>n>>W)) return 0;
    vector<long long> w(n),t(n);
    for(int i=0;i<n;i++) cin>>w[i]>>t[i];
    double lo=0,hi=1000.0;
    auto check=[&](double r)->bool{
        vector<double> dp(W+1,-1e18); dp[0]=0;
        for(int i=0;i<n;i++){
            double val=t[i]-r*(double)w[i];
            for(long long j=W;j>=0;j--){
                if(dp[j]<=-1e17) continue;
                long long nj=min(W,j+w[i]);
                if(dp[nj]<dp[j]+val) dp[nj]=dp[j]+val;
            }
        }
        return dp[W]>=0;
    };
    for(int it=0;it<60;it++){double mid=(lo+hi)/2; if(check(mid)) lo=mid; else hi=mid;}
    cout<<(long long)(lo*1000.0+1e-6)<<"\n";
    return 0;
}
