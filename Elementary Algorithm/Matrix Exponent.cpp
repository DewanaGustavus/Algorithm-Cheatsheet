#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;
typedef vector<vector<int>> matrix;

void multiply(matrix& M1, matrix& M2, matrix& ret){ // O(n ^ 3)
    int m = M1.size();
    for(int i = 0;i < m;i++){
        for(int j = 0 ;j < m;j++){
            int sum = 0;
            for(int k = 0;k < m;k++){
                sum += (M1[i][k] * M2[k][j]) % MOD;
                sum %= MOD;
            }
            ret[i][j] = sum;
        }
    }     
}

matrix matpow(matrix& mat, int power){
    int m = mat.size();
    matrix ret(matrix(m, vector<int>(m))); // at most 100 x 100
    matrix tmp(matrix(m, vector<int>(m)));
    for(int i = 0;i < m;i++)ret[i][i] = 1;
    while(power){ // log (n)
        if(power & 1){
            multiply(ret, mat, tmp);
            swap(ret, tmp);
        }

        multiply(mat, mat, tmp);
        swap(tmp, mat);

        power >>= 1;
    }
    return ret;
}
