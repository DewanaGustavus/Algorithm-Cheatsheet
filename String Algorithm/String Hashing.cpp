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

struct DoubleHash{
    vector<vector<long long>> polynom, hash;
    vector<long long> p = {31, 137};
    vector<long long> mod = {(int)1e9+7, (int)1e9+9};
    int polycount = 2;
    int n;
    DoubleHash(string str){
        n = str.size();
        polynom = vector<vector<long long>>(polycount, vector<long long>(n+1));
        hash = vector<vector<long long>>(polycount, vector<long long>(n+1));
        vector<long long> tmphash(polycount, 0);
        vector<long long> tmppoly(polycount, 1);
        for(int j=0;j<polycount;j++){
            for(int i=1;i<=n;i++){
                tmphash[j] += str[i-1] * tmppoly[j];
                tmphash[j] %= mod[j];

                polynom[j][i] = tmppoly[j];
                hash[j][i] = tmphash[j];
                
                tmppoly[j] *= p[j];
                tmppoly[j] %= mod[j];
            }
        }
    }

    vector<long long> hashvalue(int l, int r){
        vector<long long> value(polycount);
        for(int j=0;j<polycount;j++){
            if(l == 0) {
                value[j] = hash[j][r];
            } else {
                value[j] = (hash[j][r] - hash[j][l-1]) * polynom[j][n-r+1];
                value[j] %= mod[j];
                value[j] += mod[j];
                value[j] %= mod[j];
            }
        }
        return value;
    }
};

struct PalindromicHash{
    vector<int> polynom, hash, phash;
    const int p = 31;
    const int mod = 1e9+7;
    string str;
    int n;
    PalindromicHash(string s) {
        str = s;
        n = str.size();
        polynom = vector<int>(n+1);
        hash = vector<int>(n+1);
        phash = vector<int>(n+1);
 
        long long tmphash = 0;
        long long tmphash2 = 0;
        long long tmppoly = 1;
        for(int i=1;i<=n;i++){
            tmphash += 1LL * str[i-1] * tmppoly;
            tmphash %= mod;
 
            tmphash2 += 1LL * str[n-i] * tmppoly;
            tmphash2 %= mod;
 
            polynom[i] = tmppoly;
            hash[i] = tmphash;
            phash[i] = tmphash2;
            
            tmppoly *= p;
            tmppoly %= mod;
        }
    }
 
    int hashvalue(int l, int r, vector<int>& hash){
        if(l == 0)return hash[r];
        long long tmp = 1LL * (hash[r] - hash[l-1]) * polynom[n-r+1];
        tmp %= mod;
        tmp += mod;
        tmp %= mod;
        return tmp;
    }
    
    bool checkpalindrome(int l, int r) {
        int val = hashvalue(l, r, hash);
        int pval = hashvalue(n-r+1, n-l+1, phash);
        return val == pval;
    }
};
