#include <iostream>
using namespace std;
/**
 * @file 1503
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-11-25
 */

int zf_num(int n){
    int count=0;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            count++;
        }
        while(n%i==0){
            n/=i;
        }
    }
    if(n>1){
        count++;
    }
    return count;
}
int main() {
 // Type your code here
 int n;
 cin>>n;
 for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    zf_num(x)==2?cout<<1<<endl:cout<<0<<endl;
 }

  return 0;
}