#include <bits/stdc++.h>
using namespace std;
 
// Define Template          Python++
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
#define debug(x)    cout<<(#x)<<" : "<<(x)<<endl;
#define test        cout<<"test"<<endl;
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
#define prints(var)         cout<<(var)<<' ';
#define print2(var1,var2)   cout<<(var1)<<' '<<(var2)<<endl;
#define printp(paired)      cout<<(paired.first)<<' '<<(paired.second)<<endl;
#define printyes(cond)      cout<<((cond)?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<' ';};cout<<endl;
#define printmap(hashmap)   for(auto[x,y]:hashmap)cout<<x<<":"<<y<<endl;
#define endline             cout<<endl;
// Macro
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define mii map<int,int>
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pq priority_queue
#define ms multiset
// Oneliner Function
ll sigma(ll num){return num*(num+1)/2;}
ll gcd(ll a, ll b){return (a==0?b:gcd(b%a,a));}
ll lcm(ll a, ll b){return (a*b)/gcd(a,b);}
ll binpow(ll a,ll b,ll m=INT64_MAX){ll r=1;a%=m;while(b){if(b&1)r=(r*a)%m;a=(a*a)%m;b>>=1;}return r;}
ll invmod(ll a,ll m){return gcd(a,m)==1?binpow(a,m-2,m):0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define float long double
int QUERY;
// Constant
const int MOD = 1e9+7;
const long long INF = 1e18;
const int maxn = 2e5+5;

#define segmentL tuple<int,int,int>
#define segmentI tuple<int,int,int>

int32_t main(){
    // https://codeforces.com/contest/899/problem/E
    fastIO
    
    input(n)
    inputvec(arr,n)
    set<segmentL> ds; // sort by len, {-len, idx, val}
    set<segmentI> ds2; // sort by idx, {idx, val, len}

    int cnt = 1;
    int last = arr[0];
    range(i,1,n){
        if(arr[i] == last){
            cnt++;
        }else{
            ds.insert({-cnt, i-cnt, last});
            ds2.insert({i-cnt, last, cnt});
            cnt = 1;
            last = arr[i];
        }
    }
    ds.insert({-cnt, n-cnt, last});
    ds2.insert({n-cnt, last, cnt});

    int ans = 0;
    while(!ds.empty()){
        ans++;
        segmentL best = *(ds.begin());
        int bidx, bval, blen;
        tie(blen, bidx, bval) = best;
        blen = -blen;
        segmentI besti = make_tuple(bidx, bval, blen);

        auto left = ds2.lower_bound(besti);
        auto right = ds2.lower_bound(besti);
        right++;
        if(left != ds2.begin() && right != ds2.end()){
            left--;
            int vl, vr;
            int idxa, idxb, lena, lenb;
            tie(idxa, vl, lena) = (*left);
            tie(idxb, vr, lenb) = (*right);

            if(vl == vr){
                int nidx = idxa;
                int nlen = lena + lenb;

                segmentL ttmp = {-lena, idxa, vl};
                segmentL ttmp2 = {-lenb, idxb, vl};
                segmentI tmp = (*left);
                segmentI tmp2 = (*right);

                ds.erase(ttmp);
                ds.erase(ttmp2);
                ds2.erase(tmp);
                ds2.erase(tmp2);

                segmentL newsl = make_tuple(-nlen, nidx, vl);
                segmentI newsi = make_tuple(nidx, vl, nlen);

                ds.insert(newsl);
                ds2.insert(newsi);
            }
        }

        ds.erase(best);
        ds2.erase(besti);
    }
    
    print(ans)
    
    return 0;
}
