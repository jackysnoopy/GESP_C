#include <iostream>
#include <vector>
using namespace std;
int N;
vector<int> c;
bool check(int x){
    int g=N-x;
    int cnt=0;
    for(int i=1;i<=g-1;i++){
        if(c[i]>x) cnt++;
        else if(cnt>0) cnt--;
    }
    return cnt==0;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(!(cin>>N)) return 0;
    c.assign(N+1,0);
    for(int i=1;i<=N;i++) cin>>c[i];
    int lo=0,hi=N;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(check(mid)) hi=mid; else lo=mid+1;
    }
    cout<<lo<<"\n";
    return 0;
}
