#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const int MAXN = 200005;

int n, K, L;
ll a[MAXN], b[MAXN];
int typ[MAXN]; // 0=O, 1=S, 2=A, 3=B

struct DHeap {
    priority_queue<pli> q, d;
    void push(pli x) { q.push(x); }
    void del(pli x) { d.push(x); }
    void fix() { while(!d.empty()&&!q.empty()&&q.top()==d.top()) q.pop(), d.pop(); }
    pli top() { fix(); return q.top(); }
    bool empty() { fix(); return q.empty(); }
    void pop() { fix(); if(!q.empty()) q.pop(); }
};

DHeap h1,h2,h3,h4,h5,h6,h7;
// h1: O, a+b降序    h2: A, b降序    h3: B, a降序
// h4: O, a降序      h5: O, b降序    h6: A, a升序(存-a)   h7: B, b升序(存-b)

void rem(int i) {
    if(typ[i]==0) { h1.del({a[i]+b[i],i}); h4.del({a[i],i}); h5.del({b[i],i}); }
    else if(typ[i]==2) { h2.del({b[i],i}); h6.del({-a[i],i}); }
    else if(typ[i]==3) { h3.del({a[i],i}); h7.del({-b[i],i}); }
}
void ad(int i) {
    if(typ[i]==0) { h1.push({a[i]+b[i],i}); h4.push({a[i],i}); h5.push({b[i],i}); }
    else if(typ[i]==2) { h2.push({b[i],i}); h6.push({-a[i],i}); }
    else if(typ[i]==3) { h3.push({a[i],i}); h7.push({-b[i],i}); }
}

void clr() {
    for(auto* h: {&h1,&h2,&h3,&h4,&h5,&h6,&h7}) {
        while(!h->q.empty()) h->q.pop();
        while(!h->d.empty()) h->d.pop();
    }
}

pli gettop(DHeap& h, set<int>& excl) {
    while(!h.empty()) {
        auto t = h.top();
        if(excl.count(t.second)) { h.pop(); continue; }
        return t;
    }
    return {LLONG_MIN/2, -1};
}

void solve() {
    cin >> n >> K >> L;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    clr();
    
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[](int x,int y){return a[x]>a[y];});
    vector<int> sa(n+1,0);
    for(int i=0;i<K;i++) sa[ord[i]]=1;
    sort(ord.begin(),ord.end(),[](int x,int y){return b[x]>b[y];});
    vector<int> sb(n+1,0);
    for(int i=0;i<K;i++) sb[ord[i]]=1;
    
    ll ans=0; int cntS=0;
    for(int i=1;i<=n;i++){
        if(sa[i]&&sb[i]){typ[i]=1;cntS++;ans+=a[i]+b[i];}
        else if(sa[i]){typ[i]=2;ans+=a[i];}
        else if(sb[i]){typ[i]=3;ans+=b[i];}
        else typ[i]=0;
        ad(i);
    }
    
    while(cntS<L){
        ll best=LLONG_MIN; int op=0;
        // Op1: O→S, A→O, B→O
        if(!h1.empty()&&!h6.empty()&&!h7.empty()){
            ll v=h1.top().first+h6.top().first+h7.top().first;
            if(v>best){best=v;op=1;}
        }
        // Op2: A→S, B→O
        if(!h2.empty()&&!h7.empty()){
            ll v=h2.top().first+h7.top().first;
            if(v>best){best=v;op=2;}
        }
        // Op3: B→S, A→O
        if(!h3.empty()&&!h6.empty()){
            ll v=h3.top().first+h6.top().first;
            if(v>best){best=v;op=3;}
        }
        // Op4: A1→S, B1→O, O→A, A2→O
        if(!h2.empty()&&!h7.empty()&&!h4.empty()&&!h6.empty()){
            set<int> ex;
            pli t2=gettop(h2,ex); ex.insert(t2.second);
            pli t7=gettop(h7,ex); ex.insert(t7.second);
            pli t4=gettop(h4,ex); ex.insert(t4.second);
            pli t6=gettop(h6,ex); ex.insert(t6.second);
            if(t2.second>=0&&t7.second>=0&&t4.second>=0&&t6.second>=0){
                ll v=t2.first+t7.first+t4.first+t6.first;
                if(v>best){best=v;op=4;}
            }
        }
        // Op5: B1→S, A1→O, O→B, B2→O
        if(!h3.empty()&&!h6.empty()&&!h5.empty()&&!h7.empty()){
            set<int> ex;
            pli t3=gettop(h3,ex); ex.insert(t3.second);
            pli t6=gettop(h6,ex); ex.insert(t6.second);
            pli t5=gettop(h5,ex); ex.insert(t5.second);
            pli t7=gettop(h7,ex); ex.insert(t7.second);
            if(t3.second>=0&&t6.second>=0&&t5.second>=0&&t7.second>=0){
                ll v=t3.first+t6.first+t5.first+t7.first;
                if(v>best){best=v;op=5;}
            }
        }
        
        ans+=best; cntS++;
        if(op==1){
            int p1=h1.top().second,p2=h6.top().second,p3=h7.top().second;
            rem(p1);rem(p2);rem(p3);
            typ[p1]=1;typ[p2]=0;typ[p3]=0;
            ad(p1);ad(p2);ad(p3);
        }else if(op==2){
            int p2=h2.top().second,p3=h7.top().second;
            rem(p2);rem(p3);
            typ[p2]=1;typ[p3]=0;
            ad(p2);ad(p3);
        }else if(op==3){
            int p3=h3.top().second,p2=h6.top().second;
            rem(p3);rem(p2);
            typ[p3]=1;typ[p2]=0;
            ad(p3);ad(p2);
        }else if(op==4){
            set<int> ex;
            int a1=gettop(h2,ex).second; ex.insert(a1);
            int b1=gettop(h7,ex).second; ex.insert(b1);
            int o1=gettop(h4,ex).second; ex.insert(o1);
            int a2=gettop(h6,ex).second; ex.insert(a2);
            rem(a1);rem(b1);rem(o1);rem(a2);
            typ[a1]=1;typ[b1]=0;typ[o1]=2;typ[a2]=0;
            ad(a1);ad(b1);ad(o1);ad(a2);
        }else{
            set<int> ex;
            int b1=gettop(h3,ex).second; ex.insert(b1);
            int a1=gettop(h6,ex).second; ex.insert(a1);
            int o1=gettop(h5,ex).second; ex.insert(o1);
            int b2=gettop(h7,ex).second; ex.insert(b2);
            rem(b1);rem(a1);rem(o1);rem(b2);
            typ[b1]=1;typ[a1]=0;typ[o1]=3;typ[b2]=0;
            ad(b1);ad(a1);ad(o1);ad(b2);
        }
    }
    cout<<ans<<"\n";
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;cin>>T;while(T--)solve();
}
