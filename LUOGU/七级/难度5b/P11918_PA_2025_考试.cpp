#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,t;
    cin>>n>>t;
    vector<double> p(n);
    for(int i=0;i<n;i++) cin>>p[i];
    vector<int> idx(n);
    for(int i=0;i<n;i++) idx[i]=i;
    sort(idx.begin(),idx.end(),[&](int a,int b){
        return p[a]>p[b];
    });
    double ans=0;
    int m=min(n,t+5);
    vector<double> dp(t+2,0);
    dp[0]=1;
    for(int i=0;i<m;i++){
        int id=idx[i];
        for(int j=t;j>=0;j--){
            dp[j+1]+=dp[j]*p[id];
            dp[j]=dp[j]*(1-p[id]);
        }
    }
    for(int i=t;i<=m;i++) ans+=dp[i];
    cout<<fixed<<setprecision(10)<<ans<<"\n";
    return 0;
}
