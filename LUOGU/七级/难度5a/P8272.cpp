#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; if(!(cin>>N)) return 0;
    struct Ev{ ll a,b; int type; ll cnt; };
    vector<Ev> evs;
    for(int i=0;i<N;i++){
        int q; ll t,x,n; cin>>q>>t>>x>>n;
        ll a=t-x, b=t+x;
        evs.push_back({a,b,q,n}); // q:1 cow, q:2 apple
    }
    sort(evs.begin(),evs.end(),[](const Ev&p,const Ev&q){
        if(p.a!=q.a) return p.a<q.a;
        return p.type<q.type; // cows(type1) before apples(type2) at same a
    });
    map<ll,ll> pool; // cow b -> count
    ll ans=0;
    for(auto&e:evs){
        if(e.type==1){ pool[e.b]+=e.cnt; }
        else{
            ll need=e.cnt;
            while(need>0 && !pool.empty()){
                auto it=pool.upper_bound(e.b);
                if(it==pool.begin()) break;
                --it;
                ll take=min(need, it->second);
                ans+=take; need-=take; it->second-=take;
                if(it->second==0) pool.erase(it);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
