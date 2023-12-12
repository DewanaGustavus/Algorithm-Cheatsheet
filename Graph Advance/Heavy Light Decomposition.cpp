#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, q;
int val[maxn];


// rooting
const int LOG = 20;
vector<int> adj[maxn];
int subtreesize[maxn];
int lift[maxn][LOG];
int depth[maxn] = {};
int starttime[maxn];
int endtime[maxn];
int timer[2*maxn];
int TIME = 0;
void dfs(int node, int par = 1){
    depth[node] = depth[par] + 1;
    lift[node][0] = par;
    timer[node] = TIME;
    starttime[node] = TIME++;
    subtreesize[node] = 1;
    for(int i=1;i<LOG;i++)
        lift[node][i] = lift[lift[node][i - 1]][i - 1];
    for(auto nxt:adj[node]) {
        if (nxt == par) continue;
        dfs(nxt, node);
        subtreesize[node] += subtreesize[nxt];
    }
    timer[node] = TIME;
    endtime[node] = TIME++;
}
bool isancestor(int a, int b){
    return starttime[a] <= starttime[b] && endtime[a] >= endtime[b];
}
int binlift(int a, int k) {
    for (int i=0;i<LOG;i++) {
        if(k & (1 << i)) {
            a = lift[a][i];
        }
    }
    return a;
}
int lca(int a, int b){
    if(isancestor(a, b))return a;
    if(isancestor(b, a))return b;
    for (int i=LOG-1;i>=0;i--) {
        if(!isancestor(lift[a][i], b)) a = lift[a][i];
    }
    return lift[a][0];
}


// decompose
bool isHeavy[maxn];
int firstChain[maxn]; // first index in this chain
vector<int> chains[maxn];
int idxInChain[maxn];
void dfs2(int node, int prev = 0) {
    isHeavy[node] = (2*subtreesize[node] >= subtreesize[prev]); // use 2* to avoid rounding on division
    firstChain[node] = node;
    if(isHeavy[node]) {
        int fc = firstChain[prev];
        firstChain[node] = fc;
        if(chains[fc].empty()) {
            chains[fc].push_back(prev);
            idxInChain[prev] = 0;
        }
        idxInChain[node] = chains[fc].size();
        chains[fc].push_back(node);
    }
    for(int nxt : adj[node]){
        if(nxt == prev)continue;
        dfs2(nxt, node);
    }
}

struct segtree{
    // segment tree bottom up traversal
    // 0-indexing, left child is 2*i, right child is 2*i+1, parent is floor(i/2)
    // template for max range
    int n;
    vector<int> segment;
    int init = 0; // initialize array value
    int operation(int a, int b){return max(a, b);} // segment tree operation
    segtree(){}
    segtree(vector<int> array){
        n = log2(array.size()-1) + 1;
        n = (1<<n);
        segment = vector<int>(2*n, init);
        for(int i=0;i<array.size();i++){
            set(i, array[i]);
        }
    }
    void set(int idx, int val){
        idx += n;
        segment[idx] = val;
        for(idx/=2;idx>=1;idx/=2){
            segment[idx] = operation(segment[2*idx], segment[2*idx + 1]); 
        }
    }
    int rangemax(int l, int r) {
        l += n;
        r += n;
        int ans = init;
        while (l <= r) {
            if (l%2 == 1) ans = operation(ans, segment[l++]);
            if (r%2 == 0) ans = operation(ans, segment[r--]);
            l /= 2; r /= 2;
        }
        return ans;
    }
};


// real HLD
segtree chainSegtree[maxn];
void HeavyLightDecomposition() {
    int root = 1;
    dfs(root);
    subtreesize[0] = 2 * (n + 1);
    dfs2(root);
    for(int i=1;i<=n;i++) {
        if(!chains[i].empty()) {
            vector<int> tmp;
            for(int x : chains[i]) {
                tmp.push_back(val[x]);
            }
            chainSegtree[i] = segtree(tmp);
        }
    }
}

// template for solving point set update, path max query
int getans(int a, int LCA) {
    if(a == LCA)return 0;
    int prevLCA = binlift(a, depth[a] - depth[LCA] - 1);
    int ans = val[a];
    while(a != prevLCA) {
        if(isHeavy[a]) {
            int nextmove = (firstChain[a] == firstChain[prevLCA]) ? prevLCA : firstChain[a];
            int pathval = chainSegtree[firstChain[a]].rangemax(idxInChain[nextmove], idxInChain[a]);
            ans = max(ans, pathval);
            a = nextmove;
        }else {
            a = lift[a][0];
            ans = max(ans, val[a]);
        }
    }
    return ans;
}

int Query(int a, int b) {
    int LCA = lca(a,b);
    int ansa = getans(a, LCA);
    int ansb = getans(b, LCA);
    int anslca = val[LCA];
    return max({ansa, ansb, anslca});
}

void update(int a, int x) {
    val[a] = x;
    if(!chains[a].empty() || isHeavy[a]) {
        chainSegtree[firstChain[a]].set(idxInChain[a], x);
    }
}
