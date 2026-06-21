#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

// Function to factorize a number into prime factors
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    
    // Factor out 2s
    if (n % 2 == 0) {
        int count = 0;
        while (n % 2 == 0) {
            count++;
            n /= 2;
        }
        factors.push_back({2, count});
    }
    
    // Factor out odd primes
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    
    // If n is still greater than 1, it's a prime
    if (n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

int main() {
    int N;
    cin >> N;
    
    int m1, m2;
    cin >> m1 >> m2;
    
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    
    // Factorize m1 to get prime factors with exponents multiplied by m2
    vector<pair<int, int>> m_factors = primeFactorization(m1);
    for (auto &factor : m_factors) {
        factor.second *= m2;  // Multiply exponent by m2
    }
    
    int min_time = INT_MAX;
    bool found = false;
    
    // For each cell type
    for (int i = 0; i < N; i++) {
        int s = S[i];
        
        // If m1 is 1, then M = 1^m2 = 1, so any cell can be divided immediately
        if (m1 == 1) {
            min_time = 0;
            found = true;
            break;
        }
        
        // Factorize the cell division rate s
        vector<pair<int, int>> s_factors = primeFactorization(s);
        
        // Check if s contains all prime factors of m1
        bool valid = true;
        int max_time_for_cell = 0;
        
        for (const auto &m_factor : m_factors) {
            int prime = m_factor.first;
            int required_exp = m_factor.second;
            
            // Find this prime in s_factors
            int s_exp = 0;
            for (const auto &s_factor : s_factors) {
                if (s_factor.first == prime) {
                    s_exp = s_factor.second;
                    break;
                }
            }
            
            // If s doesn't contain this prime factor at all, it's invalid
            if (s_exp == 0) {
                valid = false;
                break;
            }
            
            // Calculate the minimum time needed for this prime factor
            // We need: s_exp * time >= required_exp
            // So: time >= ceil(required_exp / s_exp)
            int time_for_prime = (required_exp + s_exp - 1) / s_exp;
            max_time_for_cell = max(max_time_for_cell, time_for_prime);
        }
        
        if (valid) {
            min_time = min(min_time, max_time_for_cell);
            found = true;
        }
    }
    
    if (found) {
        cout << min_time << endl;
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}
