#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long z;
    if(!(cin>>n>>z)) return 0;
    vector<array<long long,3>> good,bad;
    for(int i=1;i<=n;i++){
        long long d,a; cin>>d>>a;
        if(a>=d) good.push_back({d,a,i});
        else bad.push_back({d,a,i});
    }
    sort(good.begin(),good.end(),[](const array<long long,3>&x,const array<long long,3>&y){return x[0]<y[0];});
    sort(bad.begin(),bad.end(),[](const array<long long,3>&x,const array<long long,3>&y){return x[1]>y[1];});
    vector<int> ord; long long cur=z;
    for(auto&e:good){ if(cur<=e[0]){cout<<"NIE\n";return 0;} cur-=e[0]; cur+=e[1]; ord.push_back((int)e[2]); }
    for(auto&e:bad){ if(cur<=e[0]){cout<<"NIE\n";return 0;} cur-=e[0]; cur+=e[1]; ord.push_back((int)e[2]); }
    cout<<"TAK\n";
    for(size_t i=0;i<ord.size();i++) cout<<ord[i]<<(i+1<ord.size()?' ':'\n');
    return 0;
}
