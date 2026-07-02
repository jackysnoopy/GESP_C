#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<pair<ll,ll>> d(n);
    for(int i=0;i<n;i++) cin>>d[i].first>>d[i].second;
    ll H; cin>>H;
    sort(d.begin(),d.end(),[](const pair<ll,ll>&x,const pair<ll,ll>&y){return x.first+x.second<y.first+y.second;});
    ll sum=0; for(auto&e:d) sum+=e.first;
    int ans=0;
    for(auto&e:d){
        if(sum+e.second>=H){ ans++; sum-=e.first; }
    }
    cout<<ans<<"\n";
    return 0;
}
