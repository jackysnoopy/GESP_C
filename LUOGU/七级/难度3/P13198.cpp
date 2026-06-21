#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    array<long long,3> cnt;
    string s;
};

int main(){
    const int MAXN = 12;
    // table[d][w]: depth d bracket whose overall winner is w (0=R,1=P,2=S)
    vector<vector<Node>> table(MAXN+1, vector<Node>(3));
    const char* ch = "RPS";
    for(int w=0; w<3; ++w){
        table[0][w].cnt = {0,0,0};
        table[0][w].cnt[w] = 1;
        table[0][w].s = string(1, ch[w]);
    }
    // w beats L; to make w win the final, the other half must produce L
    for(int d=1; d<=MAXN; ++d){
        for(int w=0; w<3; ++w){
            int L = (w+2)%3;            // the type that w beats
            Node &a = table[d-1][w];    // half producing w
            Node &b = table[d-1][L];    // half producing L
            for(int k=0; k<3; ++k) table[d][w].cnt[k] = a.cnt[k] + b.cnt[k];
            string s1 = a.s + b.s;
            string s2 = b.s + a.s;
            table[d][w].s = min(s1, s2);
        }
    }
    int T; cin >> T;
    for(int t=1; t<=T; ++t){
        int N; long long R, P, S;
        cin >> N >> R >> P >> S;
        string best;
        bool found = false;
        for(int w=0; w<3; ++w){
            if(table[N][w].cnt[0]==R && table[N][w].cnt[1]==P && table[N][w].cnt[2]==S){
                if(!found || table[N][w].s < best){
                    best = table[N][w].s;
                    found = true;
                }
            }
        }
        cout << "Case #" << t << ": " << (found ? best : string("IMPOSSIBLE")) << "\n";
    }
    return 0;
}
