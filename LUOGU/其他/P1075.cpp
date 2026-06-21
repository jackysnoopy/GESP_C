#include <iostream>
using namespace std;
/**
 * @file P1075 [NOIP 2012 普及组] 质因数分解
 * @brief Brief description of the file
 * @author JackyChen
 * @date 2025-12-02
 */
int main() {
 // Type your code here
 int x,ans;
 cin>>x;
for(int i=2;i*i<=x;i++){
        while(x%i==0){
            cout<<x/i<<endl;
            return 0;
        }
    }
  return 0;
}