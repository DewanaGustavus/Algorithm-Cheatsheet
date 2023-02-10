#include <bits/stdc++.h>
using namespace std;

const long double PI = atan(1) * 4;
long double to_degree(long double radian){return radian * 180 / PI;}

int perfect_square(long long num){return sqrt(num) == (long long)sqrt(num);}
long long sigma(long long num){return num*(num+1)/2;}
long long sigmaodd(long long num){return sigma(num-1) - (sigma((num-1)/2))*2;}
long long sigmaeven(long long num){return sigma(num/2)*2;}
long long manhattan_dist(long long x1, long long y1, long long x2, long long y2){return abs(x1-x2) + abs(y1-y2);}
long long manhattan_dist(pair<long long, long long> p1, pair<long long, long long> p2){return abs(p1.first-p2.first) + abs(p1.second-p2.second);}
long double euclid_dist(long double x1, long double y1, long double x2, long double y2){return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));}
long double euclid_dist(pair<long double, long double> p1, pair<long double, long double> p2){
    long double dx = p1.first-p2.first, dy = p1.second-p2.second;
    return sqrt((dx)*(dx) + (dy)*(dy));
}

long long reverseint(long long num){
    string temp = to_string(num);
    reverse(temp.begin(),temp.end());
    return stoll(temp);
}

int ispermutation(int a, int b){
    string casta = to_string(a);
    string castb = to_string(b);
    map<char,int> conta;
    map<char,int> contb;
    for(char ch:casta)conta[ch]++;
    for(char ch:castb)contb[ch]++;
    if(conta.size()!=contb.size())return 0;
    for(auto pair:conta)if(pair.second!=contb[pair.first])return 0;
    return 1;
}

long long gcd(long long a, long long b){
    if (a==0)return b;
    return gcd(b%a, a);
}

long long lcm(long long a, long long b){ // need gcd
    return (a*b)/gcd(a,b);
}

long long vector_gcd(vector<long long> container){ // need gcd
    long long tempgcd=container[0];
    for(long long num:container)tempgcd=gcd(num,tempgcd);
    return tempgcd;
}

long long vector_lcm(vector<long long> container){ // need lcm
    long long templcm=container[0];
    for(long long num:container)templcm=lcm(num,templcm);
    return templcm;
}

bool fullAdder(bool b1, bool b2, bool& carry){
    // function for add operation in bit
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

bitset<33> bitsetAdd(bitset<32>& x, bitset<32>& y){ // need fullAdder
    // Function to add two bitsets
    bool carry = false;
    bitset<33> ans;
    for (int i = 0; i < 33; i++) {
        ans[i] = fullAdder(x[i], y[i], carry);
    }
    return ans;
}

set<long long> generatePandigital(vector<long long> temp){
    set<long long> pandigital;
    do{
        int num = 0;
        for(auto tmp : temp){
            num*=10;
            num+=tmp;
        }
        pandigital.insert(num);
    }while(next_permutation(temp.begin(), temp.end()));
    return pandigital;
}

bool prime(long long num){
    // Time Complexity : O(sqrt(n))
    if(num<=1)return false;

    for(long long div=2;div*div<=num;div++)
        if(num%div==0)
            return false;
    
    return true;
}

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

bool check_composite(long long n, long long a, long long d, int s){ // need binpowmod
    // if integer error use int128 or uint64
    long long x = binpowmod(a, d, n);
    if (x == 1 || x == n - 1)return false;
    for (int r = 1; r < s; r++) {
        x = (long long)x * x % n;
        if (x == n - 1)return false;
    }
    return true;
}

bool fastprime(long long num){ // need check composite and binpowmod
    // Time Complexity : O(k (log(n))^3)
    if(num < 2)return false;

    int r = 0;
    long long d = num - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if (num == p)return true;
        if (check_composite(num, p, d, r))return false;
    }
    return true;
}
