#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    double pDiam, sDiam;
    int pYear, pDay, sYear, sDay;
    
    while (cin >> pDiam >> pYear >> pDay >> sDiam >> sYear >> sDay) {
        if (pDiam == 0) break;
        
        double pPeriod = (double)pYear + (double)pDay / 365.2422;
        double sPeriod = (double)sYear + (double)sDay / 365.2422;
        
        double ratio = pPeriod / sPeriod;
        double pDist = pow(ratio, 2.0/3.0);
        
        double pRadius = pDiam / 2.0;
        double sRadius = sDiam / 2.0;
        
        double pRealRadius = pRadius * pDist;
        double pDiameter = pRealRadius * 2.0;
        
        printf("%.0f\n", pDiameter);
    }
    return 0;
}
