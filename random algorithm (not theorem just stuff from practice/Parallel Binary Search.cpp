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

struct DSU{
    vector<int> link, size;
    int n, component;
    DSU(){}
    DSU(int length){
        n = length;
        component = length;
        link = vector<int>(n+1);
        size = vector<int>(n+1, 1);
        iota(link.begin(), link.end(), 0);
    }
    
    int find(int x){ // O(log(n))
        if(x != link[x])link[x] = find(link[x]);
        return link[x];
    }

    void unite(int a,int b){ // O(log(n))
        a=find(a); 
        b=find(b);
        if(a==b)return; 
        if(size[a]<size[b])swap(a,b); 
        size[a]+=size[b]; 
        link[b]=a; 
        component--;
    }

    void reset() {
        component = n;
        fill(all(size), 1);
        iota(link.begin(), link.end(), 0);
    }
};

int n,m;
tuple<int,int,int> edges[maxn]; // {w,a,b}
vi is_first_mst(maxn);
DSU container;

void kruskalmst1(){
    // Time Complexity : O(m log(m)) sort + O(m log(n)) run
    container.reset();

    for(int i=0;i<m;i++){
        int start, end, weight;
        tie(weight, start, end) = edges[i];
        if(container.find(start) != container.find(end)){ 
            container.unite(start, end);
            is_first_mst[i] = 1;
        }
    }
}

bool kruskalmst2(){
    // Time Complexity : O(m log(m)) sort + O(m log(n)) run
    container.reset();

    for(int i=0;i<m;i++){
        if(is_first_mst[i])continue;
        int start, end, weight;
        tie(weight, start, end) = edges[i];
        if(container.find(start) != container.find(end)){ 
            container.unite(start, end); 
        }
    }

    return container.component == 1;
}

int l[maxn], r[maxn];
vi binserqueue[maxn];
int ans = 0;
void binser() { // paralel binser
    int mid1 = m / 2;
    range(idx,0,m) {
        if(is_first_mst[idx]) {
            binserqueue[mid1].push_back(idx);
            l[idx] = 0;
            r[idx] = m - 1;
        }
    }

    int processamount = n - 1;
    while(processamount > 0) { // at most LOG(M) by binser
        // range(i,0,m) {
        //     prints(l[i])
        // }
        // endline
        // range(i,0,m) {
        //     prints(r[i])
        // }
        // endline
        // range(i,0,m) {
        //     prints(i)
        //     prints("|")
        //     printarr(binserqueue[i])
        // }
        // endline

        container.reset();
        range(mid,0,m) { // MST
            int start, end, weight;
            if(!is_first_mst[mid]){
                tie(weight, start, end) = edges[mid];
                if(container.find(start) != container.find(end)){ 
                    container.unite(start, end); 
                }
            }

            while(!binserqueue[mid].empty()) {
                int idx = binserqueue[mid].back();
                binserqueue[mid].pop_back();

                tie(weight, start, end) = edges[idx];
                if(l[idx] >= r[idx]) { // edges[idx] is replaced by edges[mid]
                    int mididx = l[idx] + is_first_mst[l[idx]];
                    int midweight;
                    tie(midweight, start, end) = edges[mididx];
                    ans += midweight - weight + 1;
                    processamount--;
                }else{
                    if(container.find(start) == container.find(end)){
                        r[idx] = mid;
                    }else {
                        l[idx] = mid + 1;
                    }
                    int newmid = (l[idx] + r[idx]) / 2;
                    binserqueue[newmid].push_back(idx);
                }
            }
        }
    }
}

// https://tlx.toki.id/problems/icpc-jakarta-2022/L
int32_t main(){
   fastIO
   
    cin>>n>>m;
    range(i,0,m){
        int a,b,x;
        cin>>a>>b>>x;
        edges[i] = {x,a,b};
    }
    sort(edges, edges+m); 
    container = DSU(n);
    kruskalmst1();
    
    if(kruskalmst2()){
        binser();
        print(ans)
    }else{
        print(-1)
    }
    
    
    return 0;
}
