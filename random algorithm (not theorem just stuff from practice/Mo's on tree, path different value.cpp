#include <bits/stdc++.h>
using namespace std;
 
#define range(i,s,e)        for(int i=s;i<e;i++)
#define fors(var,arr)       for(auto &var:arr)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define print(var)          cout<<(var)<<endl;


const int maxn = 5e4;
const int sqrtn = sqrt(maxn) + 2;
const int LOG = log2(maxn) + 2;
vector<int> adj[maxn];
int lift[maxn][LOG];
int depth[maxn] = {};
int starttime[maxn];
int endtime[maxn];
int timer[2*maxn];
int TIME;
int val[maxn];

void dfs(int node, int par = 1){
    depth[node] = depth[par] + 1;
    lift[node][0] = par;
    timer[TIME] = node;
    starttime[node] = TIME++;
    for(int i=1;i<LOG;i++)
        lift[node][i] = lift[lift[node][i - 1]][i - 1];
    for(auto nxt:adj[node]) {
        if (nxt == par) continue;
        dfs(nxt, node);
    }
    timer[TIME] = node;
    endtime[node] = TIME++;
}

bool isancestor(int node, int v){
    return starttime[node] <= starttime[v] && endtime[node] >= endtime[v];
}

int lca(int node, int v){
    if(isancestor(node, v))return node;
    if(isancestor(v, node))return v;
    for (int i=LOG-1;i>=0;i--) {
        if(!isancestor(lift[node][i], v)) node = lift[node][i];
    }
    return lift[node][0];
}

int s[maxn] = {};
int vis[maxn] = {};
int cnt = 0;

struct querytype{
    int l, r, idx;
    querytype(int tl, int tr, int tidx){
        if(starttime[tl] > starttime[tr])swap(tl, tr);
        if(lca(tl, tr) == tl){
            l = starttime[tl];
            r = starttime[tr];
        }else{
            l = endtime[tl];
            r = starttime[tr];
        }
        idx = tidx;
    }
    bool operator < (querytype x)const{
        pair<int,int> p1 = {l/sqrtn, r};
        pair<int,int> p2 = {x.l/sqrtn, x.r};
        return p1 < p2;
    }
};

void inserts(int num){
    if(s[num]++ == 0)cnt++;
}

void dels(int num){
    if(s[num]-- == 1)cnt--;
}

void insert(int num){
    if(vis[num]++ == 1)dels(val[num]);
    else inserts(val[num]);
}

void del(int num){
    if(vis[num]-- == 1)dels(val[num]);
    else inserts(val[num]);
}

int getans(int l, int r){
    if(lca(l, r) == l)return cnt;
    else{
        insert(lca(l,r));
        int tmp = cnt;
        del(lca(l,r));
        return tmp;
    }
}

struct IndexCompression{
    vector<int> idxcomp;
    int n;
    IndexCompression(vector<int> value){
        n = value.size();
        idxcomp = vector<int>(n);
        for(int i=0;i<n;i++)
            idxcomp[i] = value[i];
        sort(idxcomp.begin(), idxcomp.end());
    }

    int idx(int x){
        int index = lower_bound(idxcomp.begin(), idxcomp.end(), x) - idxcomp.begin();
        if(index == n || idxcomp[index] != x)return -1;
        return index;
    }
};

// https://codeforces.com/blog/entry/43230
// https://www.spoj.com/problems/COT2/
int32_t main(){
    fastIO
    
    input2(n,q)
    inputvec(v, n)
    IndexCompression compress(v);
    range(i,0,n){
        val[i+1] = compress.idx(v[i]);
    }
    
    range(i,0,n-1){
        input2(a,b)
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1);
    
    vector<querytype> querys;
    
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        querytype qi(l,r,i);
        querys.push_back(qi);
    }

    sort(querys.begin(), querys.end());
    
    int ans[q];
    int l=0,r=-1;
    for(auto quer : querys){
        while(l > quer.l)insert(timer[--l]);
        while(r < quer.r)insert(timer[++r]);
        while(l < quer.l)del(timer[l++]);
        while(r > quer.r)del(timer[r--]);
        ans[quer.idx] = getans(timer[quer.l], timer[quer.r]);
    }
    
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }


    
    return 0;
}
