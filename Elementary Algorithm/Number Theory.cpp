#include <bits/stdc++.h>
using namespace std;


long long binpowmod(long long base,long long power,long long mod){
    long long ret = 1;
    base%=mod;
    while (power){
        if (power&1)ret=(ret*base)%mod;
        base=(base*base)%mod;
        power>>=1;
    }
    return ret;
}

long long binpow(long long base, long long power){
    // Time Complexity : O(log(n))
    long long ret = 1;
    while (power){
        if (power&1)ret*=base;
        base*=base;
        power>>=1;
    }
    return ret;
}

set<int> sieve_of_eratosthenes(int n){
    // Time Complexity : O(n log(log(n)))
    vector<int> primearr(n+1, 1);

    set<int> primeset;
    for(int p=2;p*p<=n;p++)
        if(primearr[p])
            for(int i=p*p;i<=n;i+=p)
                primearr[i]=0;
        
    for(int p=2;p<=n;p++)
        if(primearr[p])
            primeset.insert(p);

    return primeset;
}

vector<pair<int,int>> primefactor(long long num){
    // Time Complexity : O(sqrt(n))
    vector<pair<int,int>> ret;

    for(int p=2;p*p<=num;p++){ 
        int count = 0;
        while(num%p==0){ 
            count++;
            num/=p;
        }
        if(count>0)ret.push_back({p, count});
    }

    if(num>1)ret.push_back({num,1});
    return ret;
}

int factorcount(long long num){ // need primefactor
    // Time Complexity : O(sqrt(n))
    auto factors = primefactor(num);
    int ans = 1;
    for(auto p:factors)ans *= p.second+1;
    return ans;
}

int factorproduct(long long num){ // need binpow and factorcount
    return binpow(num, factorcount(num)/2);
}

int factorsum(long long num){ // need primefactor and binpow
    // Time Complexity : O(sqrt(n) log(n))
    auto factors = primefactor(num); 
    int ans = 1;
    for(auto p:factors){ 
        int n = p.first, c = p.second; 
        int tmp = (binpow(n,c+1)-1) / (n-1);
        ans *= tmp;
    }
    return ans;
}

set<int> divisors(int num){
    set<int> ans;
    for(int i=1;i*i<=num;i++)
        if(num%i==0){
            ans.insert(i);
            ans.insert(num/i);
        }
    return ans;
}

bool perfectnumber(long long num){ // need factorsum
    return 2*num == factorsum(num);
}

int eulertotient(long long num){
    // calculating how much number from 1 to n that is coprime to the number
    // (IF NUM IS PRIME THE ANSWER IS NUM-1)
    // Time Complexity : O(sqrt(n))
    int count = num;

    for(int p=2;p*p<=num;p++)
        if(num%p==0){
            while(num%p==0)num/=p;
            count -= count/p;
        }
    
    if(num>1)count -= count/num;

    return count;
}

vector<int> rangetotient(int num){
    // Time Complexity : O(n log(log(n))) 
    num++;
    vector<int> phi(num);
    for(int i=0;i<num;i++)phi[i] = i;

    for(int p=2;p<num;p++)
        if(phi[p] == p)
            for(int j=p;j<num;j+=p)
                phi[j] -= phi[j]/p;

    return phi;
}

long long triplepower(int a, int b, int c, int mod){ // need binpowmod and euler totient
    // calculating a^b^c mod p
    // using euler totient a^b^c mod p = a^(b^c mod totient(p)) mod p
    // Time Complexity : O(sqrt(n) + log(n)^2)
    int power = binpowmod(b,c,eulertotient(mod));
    return binpowmod(a,power,mod);
}


