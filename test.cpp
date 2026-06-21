#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigInt {
    vector<int> digits;
    
public:
    BigInt(const string &s) {
        for (int i = s.length() - 1; i >= 0; i--)
            digits.push_back(s[i] - '0');
    }
    
    BigInt operator+(const BigInt &other) const {
        BigInt result("");
        int carry = 0;
        int max_len = max(digits.size(), other.digits.size());
        
        for (int i = 0; i < max_len || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        
        return result;
    }
    
    string toString() const {
        string s;
        for (int i = digits.size() - 1; i >= 0; i--)
            s += to_string(digits[i]);
        return s;
    }
};

BigInt fibonacci(int n) {
    if (n <= 1) return BigInt(to_string(n));
    
    BigInt a("0"), b("1"), c("0");
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {

    int n ;
    cin>>n;
    BigInt fib = fibonacci(n);
    cout << "Fibonacci(" << n << ") = " << fib.toString() << endl;
    return 0;
}
