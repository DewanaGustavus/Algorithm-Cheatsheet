#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

void FFT(vector<cd>& P, bool inverse) {
    // FFT = coef to value
    // IFFT/DFT = value to coef
    int n = P.size();
    if (n == 1)
        return;

    vector<cd> Pe(n / 2), Po(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        Pe[i] = P[2*i];
        Po[i] = P[2*i+1];
    }

    FFT(Pe, inverse);
    FFT(Po, inverse);

    double angle = 2 * PI / n; // FFT w = e^(2*pi*i/n) 
    if(inverse) angle *= -1; // DFT w = e^(-2*pi*i/n)/n

    cd w(1), wn(cos(angle), sin(angle));
    
    for (int j = 0; 2 * j < n; j++) {
        P[j] = Pe[j] + w * Po[j];
        P[j + n/2] = Pe[j] - w * Po[j];
        if (inverse) {
            P[j] /= 2;
            P[j + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size())n <<= 1;

    fa.resize(n);
    fb.resize(n);

    // coef to value
    FFT(fa, false);
    FFT(fb, false);
    
    // value multiply
    for (int i = 0; i < n; i++) fa[i] *= fb[i];

    // value to coef
    FFT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());

    return result;
}
