#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin>>n>>k;
    vector<int> l(n),r(n),p(n);
    for(int i=0;i<n;i++) cin>>l[i]>>r[i]>>p[i];
    vector<int> order(n);
    for(int i=0;i<n;i++) order[i]=i;
    sort(order.begin(),order.end(),[&](int a,int b){
        return r[a]<r[b];
    });
    vector<int> equip_time(k+1,0);
    vector<int> assign(n);
    bool ok=true;
    for(int idx:order){
        int pi=p[idx];
        int t=max(equip_time[pi]+1,l[idx]);
        if(t>r[idx]){
            ok=false;
            break;
        }
        assign[idx]=t;
        equip_time[pi]=t;
    }
    if(!ok){
        cout<<"NIE\n";
    } else {
        int max_t=0;
        for(int i=0;i<n;i++) max_t=max(max_t,assign[i]);
        cout<<max_t<<"\n";
        for(int i=0;i<n;i++) cout<<assign[i]<<"\n";
    }
    return 0;
}
