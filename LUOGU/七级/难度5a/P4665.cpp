#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<vector<int>> g;
vector<int> leaves;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    g.assign(n+1,{});
    for(int i=0;i<n-1;i++){int a,b;cin>>a>>b;g[a].push_back(b);g[b].push_back(a);}
    if(n==2){ cout<<1<<"\n"<<1<<" "<<2<<"\n"; return 0; }
    for(int i=1;i<=n;i++) if((int)g[i].size()==1) leaves.push_back(i);
    int L=leaves.size();
    cout<<(L+1)/2<<"\n";
    for(int i=0;i<L/2;i++) cout<<leaves[i]<<" "<<leaves[i+L/2]<<"\n";
    if(L&1) cout<<leaves[0]<<" "<<leaves[L-1]<<"\n";
    return 0;
}
