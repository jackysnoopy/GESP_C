#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    int n=s.size();
    map<char,vector<int>> pos;
    for(int i=0;i<n;i++) pos[s[i]].push_back(i);
    int odd=0;
    for(auto&kv:pos) if(kv.second.size()&1) odd++;
    if(odd>1){ cout<<-1<<"\n"; return 0; }
    map<char,pair<int,int>> idx;
    for(auto&kv:pos) idx[kv.first]={0,(int)kv.second.size()-1};
    vector<int> P(n);
    int lp=0, middle=-1;
    for(int i=0;i<n;i++){
        char c=s[i]; auto&pr=idx[c];
        if(pr.first>pr.second) continue;
        if(pos[c][pr.first]!=i) continue;
        pr.first++;
        if(pr.first<=pr.second){ int j=pos[c][pr.second]; pr.second--; P[lp]=i; P[n-1-lp]=j; lp++; }
        else middle=i;
    }
    if(n&1) P[n/2]=middle;
    // inversions of P via Fenwick
    vector<int> bit(n+2,0);
    auto add=[&](int x){for(x++;x<=n+1;x+=x&-x)bit[x]++;};
    auto qry=[&](int x){int r=0;for(x++;x>0;x-=x&-x)r+=bit[x];return r;};
    ll ans=0;
    for(int t=0;t<n;t++){ ans+=(ll)(t-qry(P[t])); add(P[t]); }
    cout<<ans<<"\n";
    return 0;
}
