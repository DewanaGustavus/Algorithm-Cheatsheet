#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
vector<int> adj[maxn];
bool vis[maxn];
int subtreesize[maxn];
int eulertouridx[maxn];
int eulerarray[maxn];
int idx = 0;

void dfs(int node){
    vis[node] = 1;
    eulerarray[idx] = node;
    eulertouridx[node] = idx++;
    subtreesize[node] = 1;
    for(int nxt : adj[node]){
        if(vis[nxt])continue;
        dfs(nxt);
        subtreesize[node] += subtreesize[nxt];
    }
}

// DFS time in out
const int maxn = 2e5 + 5;
vector<int> adj[maxn];
bool vis[maxn];
int starttime[maxn];
int endtime[maxn];
int timer[2*maxn];
int TIME = 0;

void timedfs(int node){
    vis[node] = 1;
    timer[TIME] = node;
    starttime[node] = TIME++;
    for(int nxt : adj[node]){
        if(vis[nxt])continue;
        timedfs(nxt);
    }
    timer[TIME] = node;
    endtime[node] = TIME++;
}

// time DFS process LCA
const int maxn = 2e5 + 5;
const int LOG = log2(maxn) + 2;
vector<int> adj[maxn];
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
    for(int i=1;i<LOG;i++)
        lift[node][i] = lift[lift[node][i - 1]][i - 1];
    for(auto nxt:adj[node]) {
        if (nxt == par) continue;
        dfs(nxt, node);
    }
    timer[node] = TIME;
    endtime[node] = TIME++;
}

bool isancestor(int a, int b){
    return starttime[a] <= starttime[b] && endtime[a] >= endtime[b];
}

int lca(int a, int b){
    if(isancestor(a, b))return a;
    if(isancestor(b, a))return b;
    for (int i=LOG-1;i>=0;i--) {
        if(!isancestor(lift[a][i], b)) a = lift[a][i];
    }
    return lift[a][0];
}
