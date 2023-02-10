#include <bits/stdc++.h>
using namespace std;
 
// Define Template          Python++
// Math
const int MOD = 1e9+7;
long long INF = 1e18;
#define intlen(num)         to_string(num).size()
// Data Structure and Algorithm
#define all(vec)            (vec).begin(),(vec).end() 
#define arrsize(arr)        sizeof(arr)/sizeof(int)
#define sortarr(arr)        sort(arr,arr+arrsize(arr));
#define sortvec(vec)        sort(all(vec));
#define minarr(arr)         *min_element(arr,arr+arrsize(arr))
#define minvec(vec)         *min_element(all(vec))
#define maxarr(arr)         *max_element(arr,arr+arrsize(arr))
#define maxvec(vec)         *max_element(all(vec))
#define sumarr(arr)         accumulate(arr,arr+arrsize(arr),0LL)
#define sumvec(vec)         accumulate(all(vec),0LL)
#define reversearr(arr)     reverse(arr,arr+arrsize(arr));
#define reversevec(vec)     reverse(all(vec));
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
// Input Output Manage
#ifndef ONLINE_JUDGE
    #define debug(x)    cout<<(#x)<<" : "<<(x)<<endl;
    #define test        cout<<"test"<<endl;
#else
    #define debug
    #define test
#endif
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define floatprecision      cout<<fixed<<setprecision(9);
#define fileread            freopen("input.txt","r",stdin);
#define fileout             freopen("output.txt","w",stdout);
#define query               cin>>QUERY;while(QUERY--)
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define input(var)          int var;cin>>var;
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputs(var)         string var;cin>>var;
#define print(var)          cout<<(var)<<endl;
#define prints(var)         cout<<(var)<<" ";
#define print2(var1,var2)   cout<<(var1)<<" "<<(var2)<<endl;
#define printp(paired)      cout<<(paired.first)<<" "<<(paired.second)<<endl;
#define printyes(cond)      cout<<((cond)?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<" ";};cout<<endl;
#define printmap(hashmap)   for(auto[x,y]:hashmap)cout<<x<<" : "<<y<<endl;
#define endline             cout<<endl;
// Oneliner Function
#define ll long long
ll sigma(ll num){return num*(num+1)/2;}
ll gcd(ll a, ll b){return (a==0?b:gcd(b%a,a));}
ll lcm(ll a, ll b){return (a*b)/gcd(a,b);}
ll binpow(ll a,ll b,ll m=INT64_MAX){ll r=1;a%=m;while(b){if(b&1)r=(r*a)%m;a=(a*a)%m;b>>=1;}return r;}

#define int long long
#define float double
int QUERY;



int32_t main(){
    // from https://codeforces.com/contest/722/problem/C
#ifndef ONLINE_JUDGE
fileread
#endif
    fastIO

    input(n)
    inputarr(arr,n)
    int pref[n+1]={};
    range(i,0,n)pref[i+1] = pref[i]+arr[i];

    set<pair<int,int>> segment; // reversed for lowerbound
    set<int, greater<int>> maximum;
    map<int,int> cnt;
    segment.insert({n,1});
    maximum.insert(0);
    maximum.insert(pref[n]);
    cnt[0]++;
    cnt[pref[n]]++;
    range(i,0,n){
        input(x)
        auto tmp = segment.lower_bound({x,0});
        pair<int,int> delseg = *tmp;
        swap(delseg.first, delseg.second);
        segment.erase(tmp);
        int sum = pref[delseg.second] - pref[delseg.first-1];
        if(--cnt[sum] == 0){
            maximum.erase(sum);  
        }
        
        pair<int,int> left = {delseg.first, x-1};
        pair<int,int> right = {x+1, delseg.second};

        if(left.first <= left.second){
            sum = pref[left.second] - pref[left.first-1];
            swap(left.first, left.second);
            segment.insert(left);
            cnt[sum]++;
            maximum.insert(sum);
        }
        if(right.first <= right.second){
            sum = pref[right.second] - pref[right.first-1];
            swap(right.first, right.second);
            segment.insert(right);
            cnt[sum]++;
            maximum.insert(sum);
        }
        // print(segment.size());
        // fors(temps, segment){printp(temps)}
        // endline
        print(*maximum.begin())

    }


    return 0;
}