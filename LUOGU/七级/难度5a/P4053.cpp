#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<pair<ll,ll>> b(n);
    for(int i=0;i<n;i++) cin>>b[i].first>>b[i].second;
    sort(b.begin(),b.end(),[](const pair<ll,ll>&x,const pair<ll,ll>&y){return x.second<y.second;});
    priority_queue<ll> pq; ll tim=0;
    for(auto&e:b){
        tim+=e.first; pq.push(e.first);
        if(tim>e.second){ tim-=pq.top(); pq.pop(); }
    }
    cout<<pq.size()<<"\n";
    return 0;
}
