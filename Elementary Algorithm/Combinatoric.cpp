#include <bits/stdc++.h>
using namespace std;


long long factorial(long long num){
    long long ret=1;
    while(num)ret*=num--;
    return ret;
}

long long factorialmod(long long num, long long mod){
    // Time Complexity : O(p + logp(n))
    long long fact[mod];
    fact[0] = 1;
    for(int i=1;i<mod;i++)fact[i]=(fact[i-1]*i)%mod;
    
    long long ret = 1;
    while(num>1){
        if(num/mod & 1)ret=mod-ret;
        ret = (ret * fact[num%mod]) % mod;
        num /= mod;
    }
    return ret;
}

long long combinatoric(long long n,long long k){
    long long res=1;
    for(long long num=n-k+1;num<=n;num++)res*=num;
    for(long long num=2;num<=k;num++)res/=num;
    return res;
}

long long floatcombinatoric(long long n, long long k) {
    // MAY HAVE FLOATING POINT ERROR
    long double res = 1;
    for (long long i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (long long)(res + 0.01);
}

vector<vector<int>> pascaltriangle(long long maxn, long long mod=INT64_MAX){
    // Time Complexity : O(n^2)
    vector<vector<int>> C(maxn, vector<int>(maxn));
    C[0][0] = 1;
    for (int n = 1; n < maxn; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k)
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) %mod;
    }
    return C;
}

long long binpowmod(long long base,long long power,long long mod) {
    long long ret = 1;
    base%=mod;
    while (power){
        if (power&1)ret=(ret*base)%mod;
        base=(base*base)%mod;
        power>>=1;
    }
    return ret;
}

long long gcd(long long a, long long b){
    if (a==0)return b;
    return gcd(b%a, a);
}

long long inverse_modulo(long long num, long long mod){ // need gcd and binpowmod
    // Time Complexity : O(log(m))
    if (gcd(num,mod)!=1)return 0;
    return binpowmod(num, mod-2, mod);
}

long long combinatoric_modulo(long long n, long long k, long long mod){ // need inverse_modulo
    // Time Complexity : O(n) factorial precompute + O(log(m))
    if(n<k)return 0;
    if(k==0)return 1;
    long long fac[n+1]; // precompute this
    fac[0] = 1;
    for(int i=1;i<=n;i++)fac[i] = (fac[i-1]*i) % mod;
    long long ret = fac[n];
    ret = (ret * inverse_modulo(fac[k], mod)) % mod;
    ret = (ret * inverse_modulo(fac[n-k], mod)) % mod;
    return ret;
}

int fact_pow (int n, int k) {
    // computing greatest power for k^x such that n! is divisible by k^x
    // Time Complexity : O(logk(n))
    int res = 0;
    while(n){
        n /= k;
        res += n;
    }
    return res;
}

void iterating_subset(){
    // just a template
    for(int bit=0;bit<(1<<n);bit++){
        vector<int> subset;
        for(int i=0;i<n;i++)
            if(bit & (1<<i))
                subset.push_back(i);
    }
}
