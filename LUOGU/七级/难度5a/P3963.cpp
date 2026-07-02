#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n,c,f;
    if(!(cin>>n>>c>>f)) return 0;
    int k=(int)((n-1)/2);
    vector<pair<ll,ll>> s(c);
    for(int i=0;i<c;i++) cin>>s[i].first>>s[i].second;
    sort(s.begin(),s.end());
    if(c<n){ cout<<-1<<"\n"; return 0; }
    vector<ll> pre(c,-1), suf(c,-1);
    {
        priority_queue<ll> pq; ll sum=0;
        for(int i=0;i<c;i++){
            pq.push(s[i].second); sum+=s[i].second;
            if((int)pq.size()>k){ sum-=pq.top(); pq.pop(); }
            if((int)pq.size()==k) pre[i]=sum;
        }
    }
    {
        priority_queue<ll> pq; ll sum=0;
        for(int i=c-1;i>=0;i--){
            pq.push(s[i].second); sum+=s[i].second;
            if((int)pq.size()>k){ sum-=pq.top(); pq.pop(); }
            if((int)pq.size()==k) suf[i]=sum;
        }
    }
    ll ans=-1;
    for(int i=k;i<c-k;i++){
        if(pre[i-1]==-1||suf[i+1]==-1) continue;
        ll cost=pre[i-1]+s[i].second+suf[i+1];
        if(cost<=f) ans=max(ans,s[i].first);
    }
    cout<<ans<<"\n";
    return 0;
}
