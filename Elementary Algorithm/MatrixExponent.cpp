#include <bits/stdc++.h>
using namespace std;

struct Matrix{
    typedef vector<vector<long long>> matrix;
    int dimension;
    long long mod = 1e9+7;
    matrix Mat;

    Matrix(matrix M){
        dimension = M.size();
        Mat = M;
    }

    matrix multiply(matrix M1, matrix M2){
        matrix ret(dimension, vector<long long>(dimension));
        for(int i = 0;i < dimension;i++){
            for(int j = 0 ;j < dimension;j++){
                long long sum = 0;
                for(int k = 0;k < dimension;k++){
                    sum += (M1[i][k] * M2[k][j]) % mod;
                    sum %= mod;
                }
                ret[i][j] = sum;
            }
        }     
        return ret;
    }

    matrix power(matrix base, long long power){ // binpow
        matrix ret(matrix(dimension, vector<long long>(dimension)));
        for(int i=0;i<dimension;i++){
            ret[i][i] = 1;
        }
        while(power){
            if(power&1)ret = multiply(ret, base);

            base = multiply(base, base);
            power >>= 1;
        }        
        return ret;
    }
};
