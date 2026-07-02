#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m,k; ll a;
vector<pair<int,int>> iv;
vector<ll> A;
bool check(ll X){
    vector<ll> diff(n+2,0);
    priority_queue<int> pq;
    int ptr=0; ll cur=0; int used=0;
    for(int i=1;i<=n;i++){
        cur+=diff[i];
        while(ptr<m && iv[ptr].first<=i){ if(iv[ptr].second>=i) pq.push(iv[ptr].second); ptr++; }
        while(!pq.empty() && pq.top()<i) pq.pop();
        while(A[i-1]+cur<X){
            if(pq.empty()) return false;
            int r=pq.top(); pq.pop();
            diff[i]+=a; if(r+1<=n) diff[r+1]-=a; cur+=a; used++;
            if(used>k) return false;
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin>>T;
    while(T--){
        cin>>n>>m>>k>>a;
        A.assign(n,0); ll mn=1e18;
        for(int i=0;i<n;i++){ cin>>A[i]; if(A[i]<mn) mn=A[i]; }
        iv.assign(m,{});
        for(int i=0;i<m;i++) cin>>iv[i].first>>iv[i].second;
        sort(iv.begin(),iv.end());
        ll lo=mn, hi=mn+(ll)k*a, ans=mn;
        while(lo<=hi){
            ll mid=(lo+hi)/2;
            if(check(mid)){ ans=mid; lo=mid+1; }
            else hi=mid-1;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
