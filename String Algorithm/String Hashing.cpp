#include <bits/stdc++.h>
using namespace std;
// Rabin-Karp pattern matching

struct StringHash{
    vector<long long> polynom, hash;
    const long long p = 31;
    const long long mod = 1e9+7;
    int n;
    StringHash(string str){
        n = str.size();
        polynom = vector<long long>(n+1);
        hash = vector<long long>(n+1);
        long long tmphash = 0;
        long long tmppoly = 1;
        for(int i=1;i<=n;i++){
            tmphash += str[i-1] * tmppoly;
            tmphash %= mod;

            polynom[i] = tmppoly;
            hash[i] = tmphash;
            
            tmppoly *= p;
            tmppoly %= mod;
        }
    }

    long long hashvalue(int l, int r){
        if(l == 0)return hash[r];
        long long tmp = (hash[r] - hash[l-1]) * polynom[n-r+1];
        tmp %= mod;
        tmp += mod;
        tmp %= mod;
        return tmp;
    }
    
    long long patternmatching(string str){
        long long hashval = 0;
        long long m = str.size();
        for(int i=1;i<=m;i++){
            hashval += str[i-1] * polynom[i];
            hashval %= mod;
        }
        hashval *= polynom[n-m+1];
        hashval %= mod;
        long long count = 0;
        for(int i=1;i<=n;i++)
            if(hashvalue(i, i+m-1) == hashval)
                count++;
        
        return count;
    }
};
