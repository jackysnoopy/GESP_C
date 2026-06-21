#include <iostream>
#include <map>
using namespace std;
/**
 * @file 1157
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-11-27
 */
void explode(int x,map<int,int> &c){
    for(int i=2;i*i<=x;i++){
        while(x%i==0){
            c[i]++;
            x/=i;
        }
    }
    if(x>1){
        c[x]++;
    }
}
 int main() {
 // Type your code here
    int N,m1,m2;
    cin>>N>>m1>>m2;
    map<int,int> sg;
    for(int i=0;i<N;i++){
        int S;
        cin>>S;
        
    }

  return 0;
}