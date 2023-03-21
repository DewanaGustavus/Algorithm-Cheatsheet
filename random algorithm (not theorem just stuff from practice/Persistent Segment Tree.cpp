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
int n,q;
int arr[maxn];
 
struct node{
    int l, r;
    int val = 0;
    node *tl = nullptr, *tr = nullptr;
    node(int a, int b){
        l = a;
        r = b;
    }
    int sum(int ql, int qr){
        if(ql > r || qr < l)return 0;
        if(ql <= l && r <= qr)return val;
        int ans = 0;
        if(tl)ans += tl->sum(ql, qr);
        if(tr)ans += tr->sum(ql, qr);
        return ans;
    }
};

void build(node* root){
    int l = root->l;
    int r = root->r;
    if(l == r){
        root->val = arr[l];
        return;
    }
    int mid = (l + r)/2;
    root->tl = new node(l, mid);
    root->tr = new node(mid+1, r);
    build(root->tl);
    build(root->tr);
    root->val = root->tl->val + root->tr->val;
}
 
node* add_persistent(int idx, int val, node* root){
    int l = root->l;
    int r = root->r;
    node* new_node = new node(l, r);
    int mid = (l+r)/2;
    if(l == idx && r == idx){
        new_node->val = val;
        return new_node;
    }else if(l <= idx && idx <= mid){
        new_node->tr = root->tr;
        new_node->tl = add_persistent(idx, val, root->tl);
        new_node->val = new_node->tl->val + new_node->tr->val;
    }else{
        new_node->tl = root->tl;
        new_node->tr = add_persistent(idx, val, root->tr);
        new_node->val = new_node->tl->val + new_node->tr->val;
    }
    return new_node;
}
 
node* get_persistent(node* root){
    node* new_node = new node(0,n-1);
    new_node->tl = root->tl;
    new_node->tr = root->tr;
    new_node->val = root->val;
    return new_node;
}
 
// https://cses.fi/problemset/task/1737
vector<node*> roots;
int32_t main(){
    fastIO
    
    cin>>n>>q;
    range(i,0,n)cin>>arr[i];
    node* initial = new node(0, n-1);
    build(initial);
    roots.pb(initial);
 
    range(i,0,q){
        int t, k, a, x;
        cin>>t;
        if(t == 1){
            cin>>k>>a>>x;
            k--;a--;
            node* new_node = add_persistent(a, x, roots[k]);
            roots[k] = new_node;
        }else if(t == 2){
            cin>>k>>a>>x;
            k--;a--;x--;
            print(roots[k]->sum(a,x));
        }else{
            cin>>k;
            node* new_node = get_persistent(roots[k-1]);
            roots.pb(new_node);
        }
    }
 
    return 0;
}